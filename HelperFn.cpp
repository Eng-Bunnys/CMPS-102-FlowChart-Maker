#include <iostream>
#include "Helper.h"
using namespace std; //7atetha just in case but it worked perfectly fine without it in the visual studio.
bool IsValue(string input) {
	if (input.length() == 0) {
		return false;
	}
	for (int i = 0; i < input.length(); i++) {
		bool hasadot = false;
		char currentcharacter = input[i];
		if (!(currentcharacter == '.' || (currentcharacter >= '0' && currentcharacter <= '9'|| currentcharacter=='-'))) {
			return false;
		}

		if (currentcharacter == '-') {
			if (i != 0) {
				return false;
			}
		}
		if (currentcharacter == '.') {
			if (i == 0) {
				return false;
			}
			else hasadot = true;
		} 
	} return true;
bool IsVariable(string input) {
	if (input.length() == 0) {
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
