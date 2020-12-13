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

Text getLexemesKind(const Text &code) {
    Text res;
    Lexer lexer(code);
    while (!lexer.eof()) {
        Token now = lexer.get_token();
        res.push_back(TokenKindNames[(int)now.kind()]);
    }
    return res;
}

Tokens getTokens(const Text &code) {
    std::vector<Token> res;
    Lexer lexer(code);
    while (!lexer.eof()) {
        res.push_back(lexer.get_token());
    }
    return res;
}

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

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], SHINGLE_ARG)) {
            doShingleCompare = true;
            i++;
            shingleSize = atoi(argv[i]);
        } else if (!strcmp(argv[i], EDITORIAL_ARG)) {
            doEditorialDistanceCompare = true;
        }
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
        std::cout << "ShingleCompare: " << std::fixed << std::setprecision(2) << res * 100 << "%\n";
    }
    if (doEditorialDistanceCompare) {
        EditorialDistanceCompare cmp;
        std::string str1 = prepare(sourceTokens);
        std::string str2 = prepare(comparedTokens);
        float res = cmp.count(str1, str2);
        std::cout << "EditorialDistanceCompare: " << std::fixed << std::setprecision(2) << res * 100 << "%\n";
    }


//    std::vector<std::string> code;
//    if (argc == 2) {
//        std::ifstream fin(argv[1]);
//        bool kek = fin.is_open();
//        std::string tmp = argv[1];
//        while (std::getline(fin, tmp)) {
//            code.push_back(tmp + '\n');
//        }
//    }
//    Lexer lexer(code);
//    while (!lexer.eof()) {
//        Token now = lexer.get_token();
//        std::cout << '<' << TokenKindNames[(int)now.kind()] << ", " << now.lexeme() << ">\n";
//    }
    return 0;
}
