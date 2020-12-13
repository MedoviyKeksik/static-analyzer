//
// Created by Slonik on 06.12.2020.
//

#ifndef STATIC_ANALYZER_EDITORIALDISTANCECOMPARE_H
#define STATIC_ANALYZER_EDITORIALDISTANCECOMPARE_H

#include <vector>
#include <string>

class EditorialDistanceCompare {
public:
    float count(const std::string &str1, const std::string &str2);
    float count(const std::vector<std::string> &text1, const std::vector<std::string> &text2);
private:
    static const int insertCost = 1;
    static const int deleteCost = 1;
    static const int replaceCost = 2;
    int getDistance(const std::string &str1, const std::string &str2);
    int getDistance(const std::vector<std::string> &text1, const std::vector<std::string> &text2);
};


#endif //STATIC_ANALYZER_EDITORIALDISTANCECOMPARE_H
