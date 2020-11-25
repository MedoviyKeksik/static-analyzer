#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "lexer.h"

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

int main(int argc, char *argv[]) {
    std::vector<std::string> code;
    if (argc == 2) {
        std::ifstream fin(argv[1]);
        bool kek = fin.is_open();
        std::string tmp = argv[1];
        while (std::getline(fin, tmp)) {
            code.push_back(tmp + '\n');
        }
    }
    Lexer lexer(code);
    while (!lexer.eof()) {
        Token now = lexer.get_token();
        std::cout << '<' << TokenKindNames[(int)now.kind()] << ", " << now.lexeme() << ">\n";
    }
    return 0;
}
