#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include <cstring>
#include <stdexcept>
#include "lexer.h"
#include "WShingling.h"
#include "EditorialDistanceCompare.h"

#define SHINGLE_ARG "-w"
#define EDITORIAL_ARG "-e"
#define HELP_ARG "--help"
#define VERBOSE_ARG "-v"

std::string TokenKindNames[] = {
        "Blank",
        "Comment",
        "hash",
        "LeftRound",
        "RightRound",
        "LeftCurly",
        "RightCurly",
        "Operator",
        "DigitConst",
        "StringConst",
        "CharConst",
        "Identifier",
        "Reserved",
        "Dot",
        "Comma",
        "Semicolon"
};

typedef std::vector<std::string> Text;
typedef std::vector<Token> Tokens;

// Reads all lines from file and places them into std::vector<std::string>
// Param 1: filename - the name of file
Text getText(std::string filename) {
    std::ifstream fin(filename);
    if (!fin.is_open()) throw std::runtime_error("Can not open file");
    std::vector<std::string> code;
    std::string tmp;
    while (std::getline(fin, tmp)) {
        code.push_back(tmp + '\n');
    }
    return code;
}

// Transforms program code into vector of string representation of token Kinds
// Param 1: code - the program code to proceed
Text getLexemesKind(const Text &code) {
    Text res;
    Lexer lexer(code);
    while (!lexer.eof()) {
        Token now = lexer.get_token();
        res.push_back(TokenKindNames[(int)now.kind()]);
    }
    return res;
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

int main(int argc, char *argv[]) {
    bool doShingleCompare = false;
    int shingleSize = 0;
    bool doEditorialDistanceCompare = false;
    bool verboseOutput = false;
    bool printHelp = false;

    // Arguments list processing
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], SHINGLE_ARG)) {
            doShingleCompare = true;
            i++;
            if (i >= argc) {
                printHelp = true;
                break;
            }
            for (char *c = argv[i]; *c != '\0'; c++)
                if (!isdigit(*c)) {
                    printHelp = true;
                    break;
                }
            shingleSize = atoi(argv[i]);
        } else if (!strcmp(argv[i], EDITORIAL_ARG)) {
            doEditorialDistanceCompare = true;
        } else if (!strcmp(argv[i], HELP_ARG)) {
            printHelp = true;
        } else if (!strcmp(argv[i], VERBOSE_ARG)) {
            verboseOutput = true;
        }
    }

    // Check for a correct list of arguments
    if (!(doShingleCompare | doEditorialDistanceCompare)
        || (argc < doShingleCompare + doEditorialDistanceCompare + verboseOutput + 2)) {
        printHelp = true;
    }

    if (printHelp) {
        std::cout << "Use: static_analyzer.exe [-w <shingle_size>] [-e] [--help] [-v] filename1 filename2\n";
        std::cout << "Parameters:\n";
        std::cout << " -w <shingle_size> \t Make shingle compare.\n";
        std::cout << " -e                \t Make editorial distance compare.\n";
        std::cout << " -v                \t Verbose output.\n";
        std::cout << " --help            \t Write this help.\n";
        return 0;
    }

    Text sourceCode = getText(argv[argc - 1]);
    Tokens sourceTokens = getTokens(sourceCode);
    Text comparedCode = getText(argv[argc - 2]);
    Tokens comparedTokens = getTokens(comparedCode);

    if (doShingleCompare) {
        ShingleCompare cmp(shingleSize);
        std::string str1 = prepare(sourceTokens);
        std::string str2 = prepare(comparedTokens);
        float res = cmp.count(str1, str2);
        if (verboseOutput)
            std::cout << "ShingleCompare: " << std::fixed << std::setprecision(2) << res * 100 << "%\n";
        else
            std::cout << std::fixed << std::setprecision(10) << res << "\n";
    }
    if (doEditorialDistanceCompare) {
        EditorialDistanceCompare cmp;
        std::string str1 = prepare(sourceTokens);
        std::string str2 = prepare(comparedTokens);
        float res = cmp.count(str1, str2);
        if (verboseOutput)
            std::cout << "EditorialDistanceCompare: " << std::fixed << std::setprecision(2) << res * 100 << "%\n";
        else
            std::cout << std::fixed << std::setprecision(10) << res << "\n";
    }
    return 0;
}
