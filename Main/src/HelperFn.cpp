#include "HelperFn.h"

/**
 * Written by Youssef Mohamed Hamdy
 * Check if the given input string is a valid number (including negative numbers).
 * Numbers can be: 12.5, -12.5, -23, -23. , -23.0 ...etc.
 *
 * @param input The input string to be checked.
 * @return True if the input is a valid number, false otherwise.
 */
bool IsValue(string input) {
	if (input.length() == 0) return false; // If the input length is zero, it is not a valid number

	bool HasDot = false; // Var to track if a dot is found
	bool HasDigit = false; // Var to track if a digit is found
	bool IsNegative = false; // Var to track if the number is negative

	for (int i = 0; i < input.length(); i++) {
		char c = input[i];
		if (i == 0 && c == '-') {
			IsNegative = true; // If the first character is a minus sign, set the negative var to true
			continue;
		}

		if (c == '.') {
			if (HasDot || !HasDigit) return false; // If a dot is found and either dot or digit has already been found, it is not a valid number
			HasDot = true; // Set the HasDot var to true
		}
		else if (!(c >= '0' && c <= '9')) return false; // If a non-digit character is found, it is not a valid number
		else HasDigit = true; // Set the HasDigit var to true
	}

	// If at least one digit is found, or if the number is negative and at least one digit is found, it is a valid number
	return HasDigit || (IsNegative && HasDigit);
}

bool IsVariable(string input)
{
	// checks if the input string is a variable name
	// return true if it can be a variable name, false otherwise

	// Variable names must start with an alphabetic letter (small or capital) or an underscore (_). 
	// After the first initial letter, variable names can contain letters, numbers and underscores.  
	// No spaces or special characters, however, are allowed.

	//TODO: complete this function

	return false;
}

OpType ValueOrVariable(string input)
{
	// checks if the input string is a double value or a variable name
	// chand returns enum "OpType" (the enum is declared in the .h)

	//TODO: complete this function

	return INVALID_OP;
}
