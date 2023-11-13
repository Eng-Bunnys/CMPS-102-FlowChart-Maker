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


/**
* Written by Youssef Mohamed Hamdy
* Check if the given input string is a valid identifier.
* An identifier should start with a letter (a-z or A-Z) or underscore (_),
* and can contain letters, numbers (0-9), or underscore (_).
*
* @param input The input string to be checked.
* @return True if the input is a valid identifier, false otherwise.
*/
bool IsVariable(string input)
{
	// If the input length is zero, it is not a valid identifier
	if (input.empty()) return false;

	char FirstCharacter = input[0];
	if (!((FirstCharacter >= 'a' && FirstCharacter <= 'z') || (FirstCharacter >= 'A' && FirstCharacter <= 'Z') || FirstCharacter == '_'))
		return false; // If the first character is not a letter or underscore, it is not a valid identifier

	for (unsigned int i = 1; i < input.length(); ++i)
	{
		char CurrentCharacter = input[i];
		if (!((CurrentCharacter >= 'a' && CurrentCharacter <= 'z')
			|| (CurrentCharacter >= 'A' && CurrentCharacter <= 'Z')
			|| (CurrentCharacter >= '0' && CurrentCharacter <= '9')
			|| CurrentCharacter == '_'))
			return false; // If any of the characters is not a letter, number, or underscore, it is not a valid identifier
	}

	return true; // If all characters pass the checks, it is a valid identifier
}

OpType ValueOrVariable(string input)
{
	// checks if the input string is a double value or a variable name
	// chand returns enum "OpType" (the enum is declared in the .h)

	//TODO: complete this function

	return INVALID_OP;
}
