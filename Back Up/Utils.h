#ifndef UTILS_H
#define UTILS_H
#include <string>
using std::string;
// GBF Utils
// If you're interested about what GBF is, it's my own personal project that I've been working on since 2021
// GBF Src: https://github.com/GBF-Nexus/Discord-Bot-Commands-and-Handler/tree/main , I just re-wrote the functions from there in C++

class Utils
{
public:
     static int randomRange(int min, int max);
     static bool isCppKeyword(const string &userInput);
     static string removeSpaces(const string &str);
     static double Utils::StringToDouble(const string &str);
     static string toLowerCase(const string& string);
};

#endif // UTILS_H