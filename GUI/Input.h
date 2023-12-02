#ifndef INPUT_H
#define INPUT_H

#include "..\DEFS.h"
#include "UI_Info.h"
#include "..\HelperFn.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"

class Output;   //Class forward declaration
class Input		//The application manager should have a pointer to this class
{
private:
	window *pWind;	//Pointer to the Graphics Window
public:
	Input(window *pW);		//Consturctor
	void GetPointClicked(Point &P) const;//Gets coordinate where user clicks
	
	//TODO: Complete the implementation of the following function
	double GetValue(Output* pO) const;	// Reads a double value from the user 

	string GetString(Output* pO) const ; //Returns a string entered by the user

	//TODO: Add the function Input::GetVariable 
	// to read a “variable name” from the user (from the keyboard). 
	// It does not return before taking a valid variable name.

	//TODO: Add the function Input::GetArithOperator 
	// to read an arithmetic operator (+, -, * or /) from the user. 
	// It does not return before taking a valid arithmetic operator.

	//TODO: Add the function Input::GetCompOperator
	// similar to the previous function but for comparison operators (==, !=, <, <=, > or >=).

	//TODO: Complete the implementation of the following function
	ActionType GetUserAction() const; //Reads the user click and maps it to an action

	~Input();
};

#endif