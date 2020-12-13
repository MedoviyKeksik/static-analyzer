//
// Created by Slonik on 02.12.2020.
//

#include "WShingling.h"
#include "CRC32.h"
#include <set>
#include <iostream>
#include <algorithm>

WShingling::WShingling(const unsigned int shingle_size) {
    this->shingleSize = shingle_size;
}

WShingling::~WShingling() {
    this->shingles.clear();
}

void WShingling::setShingleSize(const unsigned int shingleSize) {
    this->shingleSize = shingleSize;
}

unsigned int WShingling::get_shingle_size() {
    return shingleSize;
}

std::vector<shingle> &WShingling::getShingles() {
    return shingles;
}

void WShingling::count(const std::vector<std::string> &data) {
    shingles.clear();
    std::string payload;
    if (data.size() == 0) return;
    for (int i = 0; i < data.size() - shingleSize + 1; i++) {
        payload = "";
        for (int j = 0; j < shingleSize; j++) {
            payload += data[i + j];
        }
        shingles.push_back(CRC32(payload.c_str(), payload.size()));
    }
}

WShingling::WShingling() {
}

void WShingling::count(const std::string &str) {
    shingles.clear();
    for (int i = 0; i < str.size() - shingleSize + 1; i++) {
        shingles.push_back(CRC32(str.substr(i, shingleSize).c_str(), shingleSize));
    }
}

ShingleCompare::ShingleCompare(unsigned int shingle_size) {
    left.setShingleSize(shingle_size);
    right.setShingleSize(shingle_size);
}

float ShingleCompare::getAns(const std::vector<shingle> &a, const std::vector<shingle> &b) {
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
    return getAns(left.getShingles(), right.getShingles());
}

float ShingleCompare::count(const std::string &str1, const std::string &str2) {
    left.count(str1);
    right.count(str2);
    return getAns(left.getShingles(), right.getShingles());
}
