//
// Created by Slonik on 02.12.2020.
//

#include "WShingling.h"
#include "CRC32.h"
#include <set>
#include <iostream>
#include <algorithm>

WShingling::WShingling(const unsigned int shingle_size) {
    this->shingle_size = shingle_size;
}

WShingling::~WShingling() {
    this->shingles.clear();
}

void WShingling::set_shingle_size(const unsigned int shingle_size) {
    this->shingle_size = shingle_size;
}

unsigned int WShingling::get_shingle_size() {
    return shingle_size;
}

std::vector<shingle> &WShingling::get_shingles() {
    return shingles;
}

void WShingling::count(const std::vector<std::string> &data) {
    shingles.clear();
    std::string payload;
    if (data.size() == 0) return;
    for (int i = 0; i < data.size() - shingle_size + 1; i++) {
        payload = "";
        for (int j = 0; j < shingle_size; j++) {
            payload += data[i + j];
        }
        shingles.push_back(CRC32(payload.c_str(), payload.size()));
    }
}

WShingling::WShingling() {
}

ShingleCompare::ShingleCompare(unsigned int shingle_size) {
    left.set_shingle_size(shingle_size);
    right.set_shingle_size(shingle_size);
}

float ShingleCompare::get_ans(const std::vector<shingle> &a, const std::vector<shingle> &b) {
    std::set<shingle> tmp;
    for (const shingle &now : a) {
        tmp.insert(now);
    }
    std::set<shingle> tmp1;
    for (const shingle &now : b) {
        tmp1.insert(now);
    }
    unsigned int res = 0;
    for (const shingle &now : tmp) {
        if (tmp1.find(now) != tmp1.end()) {
            res++;
        }
    }
    if (tmp.size() + tmp1.size() == 0) return 0.0;
    return (float) res / (tmp.size() + tmp1.size() - res);
}

float ShingleCompare::count(const std::vector<std::string> &text1, const std::vector<std::string> &text2) {
    left.count(text1);
    right.count(text2);
    return get_ans(left.get_shingles(), right.get_shingles());
}
