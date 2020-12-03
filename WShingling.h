//
// Created by Slonik on 02.12.2020.
//

#ifndef STATIC_ANALYZER_WSHINGLING_H
#define STATIC_ANALYZER_WSHINGLING_H

#include <vector>
#include <string>
#include <cstdint>

typedef uint32_t shingle;

class WShingling {
public:
    WShingling();
    WShingling(unsigned int shingle_size);
    ~WShingling();

    void set_shingle_size(unsigned int);
    unsigned int get_shingle_size();
    void count(const std::vector<std::string> &data);
    std::vector<shingle> &get_shingles();
private:
    unsigned int shingle_size;
    std::vector<shingle> shingles;
};

class ShingleCompare {
public:
    ShingleCompare(unsigned int shingle_size);
    float count(const std::vector<std::string> &text1, const std::vector<std::string> &text2);
private:
    WShingling left, right;
    float get_ans(const std::vector<shingle> &a, const std::vector<shingle> &b);
};

#undef DEFAULT_SHINGLE_SIZE
#endif //STATIC_ANALYZER_WSHINGLING_H
