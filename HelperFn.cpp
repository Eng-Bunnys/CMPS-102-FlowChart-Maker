#include <iostream>
#include "Helper.h"
#include <vector>
#include <algorithm>
using namespace std;
void removeSpaces(string& input) {
	input.erase(remove(input.begin(), input.end(), ' '), input.end());
}
bool IsValue(string input) {
	if (input.length() == 0) {
		return false;
	} removeSpaces(input);
	bool hasadot = false, hasadigit = false, hasanegative = false;
	for (int i = 0; i < input.length(); i++) {
		char currentcharacter = input[i];
		if (currentcharacter == '-' && i != 0) {
			return false;
		}
		else if (currentcharacter == '-' && i == 0) {
			hasanegative = true;
		}
		else if (currentcharacter == '.' && hasanegative == true && i == 1) {
			return false;
		}
		else if (currentcharacter == '.' && i == 0) {
			return false;
		}
		else if (currentcharacter == '.') {
			if (hasadot == true) {
				return false;
			}
			hasadot = true;
		}
		else if (!((currentcharacter >= '0' && currentcharacter <= '9') || currentcharacter == 'e' || currentcharacter == '-' || currentcharacter == ' ')) {
			return false;
		}
		else {
			hasadigit = true;
		}
	} return hasadigit;
}
bool isCppKeyword(const string& input) {
	// List of C++ keywords (you can expand this list as needed)
	vector<string> keywords = {
		"auto", "break", "case", "char", "const", "continue", "default", "do", "double",
		"else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",
		"return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef",
		"union", "unsigned", "void", "volatile", "while"
		// Add more keywords if needed
	};

	// Convert the input string to lowercase for case-insensitive comparison
	string lowercaseInput = input;
	transform(lowercaseInput.begin(), lowercaseInput.end(), lowercaseInput.begin(), ::tolower);

	// Check if the lowercase input is in the list of keywords
	return find(keywords.begin(), keywords.end(), lowercaseInput) != keywords.end();
}
bool IsVariable(string input) {
	if (input.length() == 0) {
		return false;
	}
	if (isCppKeyword(input)) {
		return false;
	}
	char first = input[0];
	if (!((first >= 'a' && first <= 'z') || (first >= 'A' && first <= 'Z') || first == '_')) {
		return false;
	}
	for (int i = 0; i < input.length(); i++) {
		char currentcharacter = input[i];
		if (currentcharacter == ' ') {
			return false;
		}
		if (!(currentcharacter == '_' || (currentcharacter >= '0' && currentcharacter <= '9') || (currentcharacter >= 'a' && currentcharacter <= 'z') || (currentcharacter >= 'A' && currentcharacter <= 'Z'))) {
			return false;
		}
	} return true;
}
OpType ValueOrVariable(string input)
{
	if (IsValue(input)) return VALUE_OP;
	if (IsVariable(input)) return VARIABLE_OP;
	else return INVALID_OP;
}
