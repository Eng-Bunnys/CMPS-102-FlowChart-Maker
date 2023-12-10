#ifndef UTILS_H
#define UTILS_H
#include <string>
// GBF Utils
//If you're interested about what GBF is, it's my own personal project that I've been working on since 2021
//GBF Src: https://github.com/GBF-Nexus/Discord-Bot-Commands-and-Handler/tree/main , I just re-wrote the functions from there in C++

class Utils {
public:
    static int randomRange(int min, int max);
    static bool isCppKeyword(const std::string& userInput);
    static std::string removeSpaces(const std::string& str);
    static double Utils::StringToDouble(const std::string& str);
};

#endif // UTILS_H