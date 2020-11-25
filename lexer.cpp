//
// Created by Slonik on 11.11.2020.
//

#include "lexer.h"
#include "dictionary.h"
#include <stdexcept>

Token::Token(Token::Kind kind, std::string lexeme) {
    _kind = kind;
    _lexeme = lexeme;
}

Token::~Token() {

}

Token::Kind Token::kind() {
    return _kind;
}

std::string Token::lexeme() {
    return _lexeme;
}

bool Token::is(Token::Kind kind) {
    return kind == _kind;
}

Lexer::Lexer(const std::vector<std::string> &code) {
    buffer = code;
    ind = 0;
    if (!buffer.empty()) {
        current = buffer[ind].begin();
        _eof = false;
    } else _eof = true;
}

std::string to_string(char c) {
    std::string res;
    res.push_back(c);
    return res;
}

Token Lexer::get_token() {
    char c = peek();
    if (is_blank(c)) return Token(Token::Kind::Blank, get_blank());
    if (is_digit(c)) return Token(Token::Kind::DigitConst, get_digit());
    if ((c == 'L' && at(1) == '\'') || c == '\'') return Token(Token::Kind::CharConst, get_char());
    if ((c == 'L' && at(1) == '\"') || c == '\"') return Token(Token::Kind::StringConst, get_string());
    if (c == '(') return Token(Token::Kind::LeftRound, to_string(get()));
    if (c == ')') return Token(Token::Kind::RightRound, to_string(get()));
    if (c == '{') return Token(Token::Kind::LeftCurly, to_string(get()));
    if (c == '}') return Token(Token::Kind::RightCurly, to_string(get()));
    if (c == '#') return Token(Token::Kind::Hash, to_string(get()));
    if (c == ',') return Token(Token::Kind::Comma, to_string(get()));
    if (c == '.') return Token(Token::Kind::Dot, to_string(get()));
    if (c == ';') return Token(Token::Kind::Semicolon, to_string(get()));
    if (c == '/' && (at(1) == '/' || at(1) == '*')) return Token(Token::Kind::Comment, get_comment());
    if (is_letter(c)) {
        std::string tmp = get_identifier();
        if (is_reserved(tmp)) return Token(Token::Kind::Reserved, tmp);
        return Token(Token::Kind::Identifier, tmp);
    }
    return Token(Token::Kind::Operator, get_operator());
}

char Lexer::get() {
    if (_eof) return 0;
    while (current == buffer[ind].end()) {
        ind++;
        if (ind < buffer.size()) {
            current = buffer[ind].begin();
        } else {
            _eof = true;
            return 0;
        }
    }
    return *current++;
}

char Lexer::peek() {
    if (_eof) return 0;
    while (current == buffer[ind].end()) {
        ind++;
        if (ind < buffer.size()) {
            current = buffer[ind].begin();
        } else {
            _eof = true;
            return 0;
        }
    }
    return *current;
}

std::string Lexer::get_blank() {
    std::string res;
    while (is_blank(peek())) res.push_back(get());
    return res;
}

std::string Lexer::get_comment() {
    std::string res;
    res.push_back(get());
    res.push_back(get());
    if (res == "/*") {
        while (res[res.size() - 1] != '/' && res[res.size() - 2] != '*') res.push_back(get());
    } else if (res == "//") {
        while (current != buffer[ind].end()) res.push_back(get());
    }
    return res;
}

char Lexer::at(int shift) {
    int i = ind;
    while (i < buffer.size() && shift > buffer[i].end() - current) {
        i++;
        shift -= buffer[i].end() - current;
        current = buffer[i].begin();
    }
    if (i < buffer.size()) return *(current + shift);
    return 0;
}

std::string Lexer::get_operator() {
    std::string res;
    res.push_back(get());
    switch (res[0]) {
        case '+':
            if (peek() == '+' || peek() == '=') {
                res.push_back(get());
            }
            break;
        case '-':
            if (peek() == '-' || peek() == '=') {
                res.push_back(get());
            }
            break;
        case '>':
            if (peek() == '>' || peek() == '=') {
                res.push_back(get());
                if (res.back() == '>' && peek() == '=')
                    res.push_back(get());
            }
            break;
        case '<':
            if (peek() == '<' || peek() == '=') {
                res.push_back(get());
                if (res.back() == '<' && peek() == '=')
                    res.push_back(get());
            }
            break;
        case '*':
        case '/':
        case '&':
        case '|':
        case '^':
        case '=':
            if (peek() == '=') {
                res.push_back(get());
            }
            break;
        case '[':
        case ']':
            break;
        case ':':
            if (peek() == ':') {
                res.push_back(get());
            }
            break;
    }
    return res;
}

std::string Lexer::get_digit() {
    std::string res;
    int a = 0X1;
    while (is_digit(peek())) res.push_back(get());
    if (res == "0" && (peek() == 'x') || (peek() == 'X') && is_digit(at(1))) res.push_back(get());
    while (is_digit(peek())) res.push_back(get());
    return res;
}

std::string Lexer::get_string() {
    std::string res;
    int cnt = 0;
    while (!_eof && cnt < 2) {
        if (peek() == '\"') cnt++;
        res.push_back(get());
    }
    if (cnt != 2) throw std::out_of_range("String Literal Error");
    return res;
}

std::string Lexer::get_char() {
    std::string res;
    int cnt = 0;
    while (!_eof && cnt < 2) {
        if (peek() == '\'') cnt++;
        res.push_back(get());
    }
    if (cnt != 2) throw std::out_of_range("Char Literal Error");
    return res;
}

bool Lexer::eof() {
    return _eof;
}

std::string Lexer::get_identifier() {
    std::string res;
    if (is_letter(peek())) {
        res.push_back(get());
        while (is_identifier_char(peek())) res.push_back(get());
    }
    return res;
}
