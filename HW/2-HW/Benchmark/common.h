#ifndef COMMON_H
#define COMMON_H

#include <string>
using std::string;
enum class DataType { INTEGER, DECIMAL, STRING };
static const string INTEGERS_CSV = "./CSV_Data/integers.csv";
static const string STRINGS_CSV = "./CSV_Data/strings.csv";
static const string DECIMALS_CSV = "./CSV_Data/decimals.csv";


inline bool DoesFileExist(const std::string& filepath) {
    return std::filesystem::exists(filepath);
}


inline std::vector<int> readIntegers(const std::string& filepath) {
    std::ifstream file(filepath); 
    std::vector<int> data;
    int value;
    while (file >> value) {
        data.push_back(value);
    }
    return data;
}

inline std::vector<double> readDecimals(const std::string& filepath) {
    std::ifstream file(filepath);
        std::vector<double> data;
        double value;
        while (file >> value) {
            data.push_back(value);
        }
        return data;
}

inline std::vector<std::string> readStrings(const std::string& filepath) {
    std::ifstream file(filepath);
    std::vector<std::string> data;
    std::string value;
    while (file >> value) {
        data.push_back(value);
    }
    return data;
}


#endif // COMMON_H