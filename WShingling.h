//
// Created by Slonik on 02.12.2020.
//

#ifndef STATIC_ANALYZER_WSHINGLING_H
#define STATIC_ANALYZER_WSHINGLING_H

#include <vector>
#include <string>
#include <cstdint>

typedef uint32_t shingle;

// Class that counts shingles on some text
class WShingling {
public:
    WShingling();
    WShingling(unsigned int shingle_size);
    ~WShingling();

    void setShingleSize(unsigned int);
    unsigned int get_shingle_size();
    void count(const std::vector<std::string> &data);
    void count(const std::string &str);
    std::vector<shingle> &getShingles();
private:
    unsigned int shingleSize;
    std::vector<shingle> shingles;
};

// Class that compares two sets of shingles
class ShingleCompare {
public:
    ShingleCompare(unsigned int shingle_size);
    float count(const std::vector<std::string> &text1, const std::vector<std::string> &text2);
    float count(const std::string &str1, const std::string &str2);
private:
    WShingling left, right;
    float getAns(const std::vector<shingle> &a, const std::vector<shingle> &b);
};

#undef DEFAULT_SHINGLE_SIZE
#endif //STATIC_ANALYZER_WSHINGLING_H
