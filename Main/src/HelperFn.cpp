
#include "HelperFn.h"
#include <iostream>
#include <sstream>
#include <cctype>

bool IsValue(string input)
{
	std::istringstream iss(input);
	double value;
	iss >> value;
	return !iss.fail() && iss.eof();
}

bool IsVariable(string input)
{
	if (input.empty()) return false;

	for (char c : input) {
		if (!isalnum(c) && c != '_') return false;
	}

	return true;
}

OpType ValueOrVariable(string input)
{
	if (IsValue(input)) return VALUE_OP;
	else if (IsVariable(input)) return VARIABLE_OP;
	return INVALID_OP;
}
