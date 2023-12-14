#include "Utils.h"
#include "HelperFn.h"
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <algorithm>

/*
    Generate a random integer within the specified range [min, max].

    @param min: The minimum value of the range.
    @param max: The maximum value of the range.
    @return: A random integer within the specified range.
*/
int Utils::randomRange(int min, int max) {
    return rand() % (max - min + 1) + min;
}

/*
    Check if the given user input is a C++ keyword.

    @param userInput: The user input to check.
    @return: True if the user input is a C++ keyword, false otherwise.
*/
bool Utils::isCppKeyword(const std::string& userInput) {
    const std::string keywords[] = {
        "alignas", "alignof", "and", "and_eq", "asm", "auto", "bitand", "bitor",
        "bool", "break", "case", "catch", "char", "char8_t", "char16_t", "char32_t",
        "class", "compl", "concept", "const", "consteval", "constexpr", "const_cast",
        "continue", "co_await", "co_return", "co_yield", "decltype", "default", "delete",
        "do", "double", "dynamic_cast", "else", "enum", "explicit", "export", "extern",
        "false", "float", "for", "friend", "goto", "if", "inline", "int", "long",
        "mutable", "namespace", "new", "noexcept", "not", "not_eq", "nullptr",
        "operator", "or", "or_eq", "private", "protected", "public", "register",
        "reinterpret_cast", "requires", "return", "short", "signed", "sizeof", "static",
        "static_assert", "static_cast", "struct", "switch", "synchronized", "template",
        "this", "thread_local", "throw", "true", "try", "typedef", "typeid", "typename",
        "union", "unsigned", "using", "virtual", "void", "volatile", "wchar_t", "while",
        "xor", "xor_eq"
    };

    std::string userInputLower = userInput;
    std::transform(userInputLower.begin(), userInputLower.end(), userInputLower.begin(), ::tolower);

    return std::binary_search(std::begin(keywords), std::end(keywords), userInputLower);
}

/*
    Remove leading spaces from the given string and return the modified string.

    @param str: The input string.
    @return: The modified string with leading spaces removed.
*/

std::string Utils::removeSpaces(const std::string& InputString) {
    int index = 0;
    while (index < InputString.length() && InputString[index] == ' ') index++;

    return InputString.substr(index);
}

/**
 * Converts a string to a double value.
 * 
 * @param {string} str - The string value to convert.
 * @return {number} - The converted double value.
 */
double Utils::StringToDouble(const std::string& InputString) {
    if (InputString.empty()) {
        throw std::invalid_argument("Empty string provided");
    }

    double Result = 0.0;
    int Sign = 1;
    int DecimalIndex = -1;
    //If you're interested on what size_t is: https://stackoverflow.com/questions/502856/whats-the-difference-between-size-t-and-int-in-c
    for (size_t i = 0; i < InputString.length(); ++i) {
        char CurrentCharacter = InputString[i];

        if (CurrentCharacter == '-') {
            if (i != 0) {
                throw std::invalid_argument("Invalid input: " + InputString);
            }
            Sign = -1;
        }
        else if (CurrentCharacter == '.') {
            if (DecimalIndex != -1) {
                throw std::invalid_argument("Invalid input: " + InputString);
            }
            DecimalIndex = i;
        }
        else if (CurrentCharacter >= '0' && CurrentCharacter <= '9') {
            Result = Result * 10 + (CurrentCharacter - '0');
        }
        else {
            throw std::invalid_argument("Invalid character in the string: " + InputString);
        }
    }

    // Adjust result based on the position of the decimal point
    if (DecimalIndex != -1) {
        Result /= std::pow(10, InputString.length() - DecimalIndex - 1);

        // Remove trailing zeros by erasing from the end [This will not work for some reason]
        size_t length = InputString.length();
        while (length > DecimalIndex + 1 && InputString[length - 1] == '0') {
            --length;
        }
        InputString.substr(0, length);
    }

    return Result * Sign;
}
