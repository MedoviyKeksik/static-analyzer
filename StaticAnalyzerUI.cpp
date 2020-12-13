//
// Created by Slonik on 08.12.2020.
//

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <CommCtrl.h>
#include <richedit.h>
#include <iostream>

#define IDC_CALCULATEBUTTON 42
#define IDC_OPENDIALOGBUTTON1 43
#define IDC_OPENDIALOGBUTTON2 44
#define BUTTON_CLASS L"Button"


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

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
            WS_OVERLAPPEDWINDOW | WS_VISIBLE,            // Window style

            // Size and position
//            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
            CW_USEDEFAULT, CW_USEDEFAULT, 640, 480,

            NULL,       // Parent window
            NULL,       // Menu
            hInstance,  // Instance handle
            NULL        // Additional application dataJ[
    );

    if (hwnd == NULL) {
        return 0;
    }

    LoadLibrary(TEXT("Riched20.dll"));

    CreateWindowEx(WS_EX_CLIENTEDGE, RICHEDIT_CLASS, L"SomeText", ES_MULTILINE | WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP | ES_READONLY,
                   10, 10, 300, 370, hwnd, 0, hInstance, 0);
    CreateWindowEx(WS_EX_CLIENTEDGE, BUTTON_CLASS, L"Open", WS_CHILD | WS_VISIBLE | BS_CENTER | BS_PUSHBUTTON,
                  10, 385, 100, 30, hwnd, (HMENU)(IDC_OPENDIALOGBUTTON1), 0, 0);


    CreateWindowEx(WS_EX_CLIENTEDGE, RICHEDIT_CLASS, L"SomeText", ES_MULTILINE | WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP | ES_READONLY,
                   315, 10, 300, 370, hwnd, 0, hInstance, 0);
    CreateWindowEx(WS_EX_CLIENTEDGE, BUTTON_CLASS, L"Open", WS_CHILD | WS_VISIBLE | BS_CENTER | BS_PUSHBUTTON,
                  315, 385, 100, 30, hwnd, (HMENU)(IDC_OPENDIALOGBUTTON2), 0, 0);

    CreateWindowEx(WS_EX_CLIENTEDGE, BUTTON_CLASS, L"Calculate", WS_CHILD | WS_VISIBLE | BS_CENTER | BS_DEFPUSHBUTTON,
                   500, 385, 100, 30, hwnd, (HMENU)(IDC_CALCULATEBUTTON), 0, 0);


    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {

        case WM_COMMAND:
        if (BN_CLICKED == HIWORD(wParam)) {
            switch (LOWORD(wParam)) {
                case IDC_OPENDIALOGBUTTON1:
                case IDC_OPENDIALOGBUTTON2:

                    break;
                case IDC_CALCULATEBUTTON:
                    MessageBox(hwnd, L"Button clicked", L"Attention!", MB_OK);
                    break;
            }
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}