//
// Created by Slonik on 06.12.2020.
//

#include "EditorialDistanceCompare.h"


int EditorialDistanceCompare::getDistance(const std::vector<std::string> &text1, const std::vector<std::string> &text2) {
    std::vector<int> dp[2];
    dp[1].resize(text1.size()); dp[0].resize(text1.size());
    dp[0][0] = 0;
    for (int i = 1; i < (int) text1.size(); i++) {
        dp[0][i] = dp[0][i - 1] + insertCost;
    }
    for (int i = 1; i < (int) text2.size(); i++) {
        dp[i & 1][0] = dp[i & 1 ^ 1][0] + deleteCost;
        for (int j = 0; j < (int) text1.size(); j++) {
            if (text1[j] != text2[i])
                dp[i & 1][j] = std::min(dp[i & 1 ^ 1][j] + deleteCost,
                                    std::min(dp[i & 1][j - 1] + insertCost,
                                             dp[i & 1 ^ 1][j - 1] + replaceCost));
            else dp[i & 1][j] = dp[i & 1 ^ 1][j - 1];
        }
    }
    return dp[text2.size() & 1 ^ 1][text1.size() - 1];
}


int EditorialDistanceCompare::getDistance(const std::string &str1, const std::string &str2) {
    std::vector<int> dp[2];
    dp[1].resize(str1.size()); dp[0].resize(str2.size());
    dp[0][0] = 0;
    for (int i = 1; i < (int) str1.size(); i++) {
        dp[0][i] = dp[0][i - 1] + insertCost;
    }
    for (int i = 1; i < (int) str2.size(); i++) {
        dp[i & 1][0] = dp[i & 1 ^ 1][0] + deleteCost;
        for (int j = 0; j < (int) str1.size(); j++) {
            if (str1[j] != str2[i])
                dp[i & 1][j] = std::min(dp[i & 1 ^ 1][j] + deleteCost,
                                        std::min(dp[i & 1][j - 1] + insertCost,
                                                 dp[i & 1 ^ 1][j - 1] + replaceCost));
            else dp[i & 1][j] = dp[i & 1 ^ 1][j - 1];
        }
    }
    return dp[str2.size() & 1 ^ 1][str1.size() - 1];
}


float EditorialDistanceCompare::count(const std::vector<std::string> &text1, const std::vector<std::string> &text2) {
    return 1.0 - 1.0 * getDistance(text1, text2) / std::max(text1.size(), text2.size());
}

float EditorialDistanceCompare::count(const std::string &str1, const std::string &str2) {
    return 1.0 - 1.0 * getDistance(str1, str2) / std::max(str1.size(), str2.size());
}

