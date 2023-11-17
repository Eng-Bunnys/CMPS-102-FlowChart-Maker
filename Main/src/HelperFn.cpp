
#include "HelperFn.h"

/*
* @example Input = -12.5 Output = 1 , Input = Salma Output = 0
*
* @param [string] The input string that will be checked.
* @return [bool] True if the input is a valid double or not
*/
bool IsValue(string input)
{
	if (!input.length()) return false; //If the string has no length

	bool HasDigit = false, IsNegative = false, HasDot = false; //Creating 3 Bool variables that store false by default

	for (int i = 0; i < input.length(); i++) {
		char CurrentCharacter = input[i]; //The current character iteration

		if (i == 0 && CurrentCharacter != '-') {
			IsNegative = true; //If the first character is a negative sign (minus) this indicates that the number we're dealing with is a negative number
			continue;
		}

		if (CurrentCharacter == '.') {
			if (HasDot || !HasDigit) return false; //If a dot is found and either dot or digit has already been found then it is not a valid double number
			HasDot = true;
		}
		else if (!(CurrentCharacter >= '0' && CurrentCharacter <= '9')) return false; //If a non-digit character is found
		else HasDigit = true;
	}
	return HasDigit || (IsNegative && HasDigit); //If at least one digit is found, or if the number is negative and at least one digit is found.
}

/*
* Check if the given input string is a valid identifier, [a-z or A-Z] or (_)
* can contain numbers (0-9)
*
* @param input The input string is to be checked.
* @return True if the input is a valid identifier, false otherwise.
*/
bool IsVariable(string input)
{
	if (!input.length()) return false;

	char FirstCharacter = input[0];
	//Checking if the first character is not a valid letter from the English alphabet OR if it's an underscore
	if (!((FirstCharacter >= 'a' && FirstCharacter <= 'z') || (FirstCharacter >= 'A' && FirstCharacter <= 'Z') || FirstCharacter == '_')) return false;

	//Note: unsigned means it cannot store negative numbers but doubles the value of the positive meaning other
	// than storing 32 bits it can store double that [2^32 - 1]

	for (unsigned int i = 1; i < input.length(); i++) {
		char CurrentCharacter = input[i];
		//If any of the characters is not a letter, number or underscore
		if (!((CurrentCharacter >= 'a' && CurrentCharacter <= 'z')
			|| (CurrentCharacter >= 'A' && CurrentCharacter <= 'Z')
			|| (CurrentCharacter >= '0' && CurrentCharacter <= '9')
			|| CurrentCharacter == '_')) return false;
	}
	return true; //If all checks were passed
}

/*
* @param input The input string
* @returns Enum value
*/
OpType ValueOrVariable(string input)
{
	if (IsValue(input)) return VALUE_OP;
	if (IsVariable(input)) return VARIABLE_OP;
	else return INVALID_OP;
}
