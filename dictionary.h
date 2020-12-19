//
// Created by Slonik on 11.11.2020.
//

#ifndef STATIC_ANALYZER_DICTIONARY_H
#define STATIC_ANALYZER_DICTIONARY_H

// Function that checks if character is a blank charackter (tab, space, ...)
// Param 1: c - characker to check
bool isBlank(char c);

// Function that checks if character is a digit
// Param 1: c - characker to check
bool isDigit(char c);

// Function that checks if character is a letter
// Param 1: c - characker to check
bool isLetter(char c);

// Function that checks if character can be used to name identifier
// Param 1: c - characker to check
bool isIdentifierChar(char c);

// Function that checks if string is a reserved keyword
// Param 1: s - the string to check
bool isReserved(std::string s);

#endif //STATIC_ANALYZER_DICTIONARY_H
