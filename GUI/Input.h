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

	char GetChar(Output* pO) const; // Returns a character entered by the user

	string GetVariable(Output* pO) const; // Reads a variable name from the user

	char GetArithOperator(Output* pO) const; // Reads an arithmetic operator from the user

	char GetCompOperator(Output* pO) const; // Reads a comparison operator from the user

	ActionType GetUserAction() const; //Reads the user click and maps it to an action

	~Input();
};

#endif
