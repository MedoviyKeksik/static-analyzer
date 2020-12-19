//
// Created by Slonik on 11.11.2020.
//

#include <string>
#include <vector>
#ifndef STATIC_ANALYZER_LEXER_H
#define STATIC_ANALYZER_LEXER_H

// Class that describes a token
class Token {
public:
    enum class Kind {
        Blank,
        Comment,
        Hash,
        LeftRound,
        RightRound,
        LeftCurly,
        RightCurly,
        Operator,
        DigitConst,
        StringConst,
        CharConst,
        Identifier,
        Reserved,
        Dot,
        Comma,
        Semicolon
    };
private:
    Kind _kind;
    std::string _lexeme;
public:
    Token(Kind kind, std::string lexeme);
    ~Token();
    Kind kind();
    std::string lexeme();
    bool is(Kind kind);
};

// Class that translates program code into lexemes
class Lexer {
private:
    std::vector<std::string> buffer;
    std::string::iterator current;
    size_t ind;
    bool _eof;

    char get();
    char peek();
    char at(int shift);

    std::string get_blank();
    std::string get_comment();
    std::string get_operator();
    std::string get_digit();
    std::string get_string();
    std::string get_char();
    std::string get_identifier();
public:
    Lexer(const std::vector<std::string> &code);
    Token get_token();
    bool eof();
};

#endif //STATIC_ANALYZER_LEXER_H
