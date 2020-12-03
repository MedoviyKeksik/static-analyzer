#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstring>
#include <stdexcept>
#include "lexer.h"
#include "WShingling.h"

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

Text get_code(std::string filename) {
    std::ifstream fin(filename);
    if (!fin.is_open()) throw std::runtime_error("Can not open file");
    std::vector<std::string> code;
    std::string tmp;
    while (std::getline(fin, tmp)) {
        code.push_back(tmp + '\n');
    }
    return code;
}

Text get_lexemes_kind(const Text &code) {
    Text res;
    Lexer lexer(code);
    while (!lexer.eof()) {
        Token now = lexer.get_token();
        res.push_back(TokenKindNames[(int)now.kind()]);
    }
    return res;
}

int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-w")) {
            int shingle_len = atoi(argv[i + 1]);
            Text code1 = get_code(argv[i + 2]);
            Text code2 = get_code(argv[i + 3]);
            i += 3;

            ShingleCompare cmp(shingle_len);
            float ans = cmp.count(get_lexemes_kind(code1), get_lexemes_kind(code2));
            std::cout << ans << std::endl;
        }
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
