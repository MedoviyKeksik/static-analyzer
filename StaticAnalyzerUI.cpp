//
// Created by Slonik on 08.12.2020.
//

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <CommCtrl.h>
#include <iostream>
#include "lexer.h"
#include "WShingling.h"
#include "EditorialDistanceCompare.h"
#include <string>
#include <fstream>

#define IDC_CALCULATEBUTTON 42
#define IDC_OPENDIALOGBUTTON1 43
#define IDC_OPENDIALOGBUTTON2 44
#define IDC_EDIT1 45
#define IDC_EDIT2 46

#define BUTTON_CLASS L"Button"
#define EDIT_CLASS L"Edit"

#define WSIZE 640

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

OPENFILENAME ofn1, ofn2;
TCHAR szFile1[260] = {0}, szFile2[260] = {0};
HWND hwndEdit1 = 0, hwndEdit2 = 0, oLabel;

INT WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    // Register the window class.
    const wchar_t CLASS_NAME[]  = L"StaticAnalyzerUI";

    WNDCLASS wc = { };

    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.
    HWND hwnd = CreateWindowEx(
            0,                              // Optional window styles.
            CLASS_NAME,                     // Window class
            L"StaticAnalyzerUI",            // Window text
            (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX) | WS_VISIBLE,            // Window style

            // Size and position
//            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
            CW_USEDEFAULT, CW_USEDEFAULT, WSIZE, 260,

            NULL,       // Parent window
            NULL,       // Menu
            hInstance,  // Instance handle
            NULL        // Additional application dataJ[
    );

    ZeroMemory(&ofn1, sizeof(ofn1));
    ZeroMemory(&ofn2, sizeof(ofn2));

    ofn1.lStructSize = sizeof(ofn1);
    ofn1.hwndOwner = hwnd;
    ofn1.lpstrFile = szFile1;
    ofn1.nMaxFile = sizeof(szFile1);
    ofn1.lpstrFilter = L"All\0*.*\0Cpp\0*.cpp\0";
    ofn1.nFilterIndex = 2;
    ofn1.lpstrFileTitle = NULL;
    ofn1.nMaxFileTitle = 0;
    ofn1.lpstrInitialDir = NULL;
    ofn1.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;


    ofn2.lStructSize = sizeof(ofn2);
    ofn2.hwndOwner = hwnd;
    ofn2.lpstrFile = szFile2;
    ofn2.nMaxFile = sizeof(szFile2);
    ofn2.lpstrFilter = L"All\0*.*\0cpp\0*.cpp\0";
    ofn2.nFilterIndex = 2;
    ofn2.lpstrFileTitle = NULL;
    ofn2.nMaxFileTitle = 0;
    ofn2.lpstrInitialDir = NULL;
    ofn2.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (hwnd == NULL) {
        return 0;
    }

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

typedef std::vector<std::string> Text;
typedef std::vector<Token> Tokens;

// Reads all lines from file and places them into std::vector<std::string>
// Param 1: filename - the name of file
Text getText(std::string filename, HWND hwnd) {
    std::ifstream fin(filename);
    std::vector<std::string> code;
    if (!fin.is_open()) {
        MessageBox(hwnd, L"File does not exists.", L"Error", MB_OK | MB_ICONWARNING);
        return code;
    }
    std::string tmp;
    while (std::getline(fin, tmp)) {
        code.push_back(tmp + '\n');
    }
    return code;
}

// Transform vector of strings (program code) into vector of tokens
// Param 1: code - the program code to proceed
Tokens getTokens(const Text &code) {
    std::vector<Token> res;
    Lexer lexer(code);
    while (!lexer.eof()) {
        res.push_back(lexer.get_token());
    }
    return res;
}

// Get string in which every character is a digital representation of token kinds
// Param 1: tokens - the vector of tokens to proceed
std::string prepare(Tokens &tokens) {
    std::string res;
    for (Token now : tokens) {
        if (now.kind() != Token::Kind::Blank && now.kind() != Token::Kind::Comment)
            res += (char)now.kind();
    }
    return res;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE: {
        LRESULT lRes = DefWindowProc(hwnd, uMsg, wParam, lParam);

        CreateWindowEx(WS_EX_TRANSPARENT, L"Static", L"Select the files:", WS_CHILD | WS_VISIBLE, 10, 10, WSIZE - 30, 20, hwnd, 0, 0, 0);
        hwndEdit1 = CreateWindowEx(WS_EX_CLIENTEDGE, EDIT_CLASS, NULL, WS_CHILD | WS_VISIBLE, 10, 30, WSIZE - 140, 30, hwnd, (HMENU)(IDC_EDIT1), 0, 0);
        hwndEdit2 = CreateWindowEx(WS_EX_CLIENTEDGE, EDIT_CLASS, NULL, WS_CHILD | WS_VISIBLE, 10, 70, WSIZE - 140, 30, hwnd, (HMENU)(IDC_EDIT2), 0, 0);
        CreateWindowEx(WS_EX_CLIENTEDGE, BUTTON_CLASS, L"Select", WS_CHILD | WS_VISIBLE | BS_CENTER | BS_PUSHBUTTON,
                       20 + WSIZE - 140, 30, 100, 30, hwnd, (HMENU)(IDC_OPENDIALOGBUTTON1), 0, 0);
        CreateWindowEx(WS_EX_CLIENTEDGE, BUTTON_CLASS, L"Select", WS_CHILD | WS_VISIBLE | BS_CENTER | BS_PUSHBUTTON,
                       20 + WSIZE - 140, 70, 100, 30, hwnd, (HMENU)(IDC_OPENDIALOGBUTTON2), 0, 0);
        CreateWindowEx(WS_EX_CLIENTEDGE, BUTTON_CLASS, L"Calculate", WS_CHILD | WS_VISIBLE | BS_CENTER | BS_DEFPUSHBUTTON,
                       10, 110, WSIZE - 30, 30, hwnd, (HMENU)(IDC_CALCULATEBUTTON), 0, 0);
        oLabel = CreateWindowExA(WS_EX_CLIENTEDGE, "Static", "", WS_CHILD | WS_VISIBLE, 10, 150, WSIZE - 32, 50, hwnd, 0, 0,0 );
        return lRes;
    }
    case WM_COMMAND: {
        if (BN_CLICKED == HIWORD(wParam)) {
            switch (LOWORD(wParam)) {
                case IDC_OPENDIALOGBUTTON1:
                    if (GetOpenFileName(&ofn1)) {
                        SetWindowText(hwndEdit1, ofn1.lpstrFile);
                    }
                    break;
                case IDC_OPENDIALOGBUTTON2:
                    if (GetOpenFileName(&ofn2)) {
                        SetWindowText(hwndEdit2, ofn2.lpstrFile);
                    }
                    break;
                case IDC_CALCULATEBUTTON:
                    int sizeFileName1 = GetWindowTextLength(hwndEdit1);
                    int sizeFileName2 = GetWindowTextLength(hwndEdit2);
                    TCHAR buffer[260] = {0};
                    char bufferMultiByte[512] = {0};

                    GetWindowText(hwndEdit1, (LPWSTR)(buffer), sizeof(buffer));
                    WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, (LPCWCH)buffer, sizeFileName1, bufferMultiByte, sizeof(bufferMultiByte), NULL, NULL);
                    std::string filename1(bufferMultiByte);

                    GetWindowText(hwndEdit2, (LPWSTR)(buffer), sizeof(buffer));
                    WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, (LPCWCH)buffer, sizeFileName2, bufferMultiByte, sizeof(bufferMultiByte), NULL, NULL);
                    std::string filename2(bufferMultiByte);

                    Text sourceCode = getText(filename1, hwnd);
                    if (sourceCode.empty()) break;
                    Tokens sourceTokens = getTokens(sourceCode);
                    Text comparedCode = getText(filename2, hwnd);
                    if (comparedCode.empty()) break;
                    Tokens comparedTokens = getTokens(comparedCode);

                    ShingleCompare cmp(10);
                    std::string str1 = prepare(sourceTokens);
                    std::string str2 = prepare(comparedTokens);
                    float res = cmp.count(str1, str2);
                    std::string out = "ShingleCompare: " + std::to_string(res * 100) + "%\n";
                    EditorialDistanceCompare cmp1;
                    res = cmp1.count(str1, str2);
                    out += "EditorialCompare: " + std::to_string(res * 100) + "%\n";
                    SetWindowTextA(oLabel, out.c_str());
                    break;
            }
        }
        break;
    }
    case WM_DESTROY: {
        PostQuitMessage(0);
        return 0;
    }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}