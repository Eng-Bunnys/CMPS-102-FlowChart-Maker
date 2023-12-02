
#include "Input.h"
#include "Output.h"

Input::Input(window* pW)
{
	pWind = pW; //point to the passed window
}

void Input::GetPointClicked(Point& P) const
{
	pWind->WaitMouseClick(P.x, P.y); //Wait for mouse click
}

string Input::GetString(Output* pO) const
{
	string Label;
	char Key;
	while (1)
	{
		pWind->WaitKeyPress(Key);
		if (Key == 27)	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if (Key == 13)	//ENTER key is pressed
			return Label;
		if ((Key == 8) && (Label.size() >= 1))	//BackSpace is pressed
			Label.resize(Label.size() - 1);
		else
			Label += Key;
		if (pO)
			pO->PrintMessage(Label);
	}
}

char Input::GetChar(Output* pO) const
{
	char Key;
	while (1)
	{
		pWind->WaitKeyPress(Key);
		if (Key == 27)	//ESCAPE key is pressed
			return '\0';	//Returns null character as the user has canceled input, I prefer returning null rather than an empty string
		if ((Key == 8) || (Key == 13))	//BackSpace or ENTER key is pressed
			return Key;
		if (pO)
		{
			string str(1, Key); //Convert the char to a string
			pO->PrintMessage(str);
		}
	}
}


double Input::GetValue(Output* pO) const // Reads a double value from the user 
{
	double D = 0;
	string UserInput;

	pO->PrintMessage("Please enter a value");

	while (true) {
		UserInput = GetString(pO);

		if (IsValue(UserInput)) {
			D = IsValue(UserInput);
			break;
		}
		else pO->PrintMessage("Enter a valid double value: ");
	}

	return D;
}

string Input::GetVariable(Output* pO) const {
	string VariableName;

	pO->PrintMessage("Enter the variable name: ");

	while (true) {
		VariableName = GetString(pO);

		if (IsVariable(VariableName)) break;
		else {
			pO->PrintMessage("Invalid Input, Enter a valid variable name: ");
		}
	}
	return VariableName;
}

char Input::GetArithOperator(Output* pO) const {
    char Operator;

    pO->PrintMessage("Enter an arithmetic operator: ");

    while (true) {
        Operator = GetChar(pO);
        
        // Check if the entered operator is one of the valid arithmetic operators (+, -, *, /)
        if (Operator == '+' || Operator == '-' || Operator == '*' || Operator == '/') break; // Exit the loop if a valid operator is entered
        else {
            pO->PrintMessage("Invalid Input, Enter a valid arithmetic operator: ");
        }
    }

    return Operator;
}
//These 2 functions are very similar, therefore they're very close to each other
char Input::GetCompOperator(Output* pO) const {
	char Operator;

	pO->PrintMessage("Enter a comparison operator: ");

	while (true) {
		Operator = GetChar(pO);

		// Check if the entered operator is one of the valid comparison operators (=, !, <, >)
		if (Operator == '=' || Operator == '!' || Operator == '<' || Operator == '>') break;  // Exit the loop if a valid operator is entered
		else {
			pO->PrintMessage("Invalid Input, Enter a valid comparison operator: ");
		}
	}

	return Operator;
}

ActionType Input::GetUserAction() const
{
    // This function reads the position where the user clicks to determine the desired action

    int x, y;
    pWind->WaitMouseClick(x, y); // Get the coordinates of the user click

    if (UI.AppMode == DESIGN) // Application is in design mode
    {
        //[1] If user clicks on the Toolbar
        if (y >= 0 && y < UI.ToolBarHeight)
        {
            // Check which Menu item was clicked
            // This assumes that menu items are lined up horizontally
            // This can be adjusted based on the actual layout of your toolbar
            int ClickedItem = (x / UI.MenuItemWidth);
            // Divide x coord of the point clicked by the menu item width (int division)
            // if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on
            switch (ClickedItem)
            {
            case ITM_VALUE_ASSIGN:
                return ADD_VALUE_ASSIGN;
            case ITM_COND:
                return ADD_CONDITION;
            case ITM_EXIT:
                return EXIT;
            default:
                return DSN_TOOL;
            }
        }

        //[2] User clicks on the drawing area
        if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
        {
            if (x <= UI.DrawingAreaWidth)
                return DRAWING_AREA;
            else
                return OUTPUT_AREA;
        }

        //[3] User clicks on the status bar
        return STATUS;
    }
    else // Application is in Simulation mode
    {
        // TODO: Adjust this based on the actual layout of your simulation bar
        // This is just a placeholder
        if (y >= 0 && y < UI.ToolBarHeight)
        {
            // Check which simulation item was clicked
            int ClickedItem = (x / UI.MenuItemWidth);
            // Divide x coord of the point clicked by the menu item width (int division)
            // if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on
            switch (ClickedItem)
            {
                // TODO: Add cases for simulation mode items
            default:
                return SWITCH_DSN_MODE;
            }
        }
        return SWITCH_DSN_MODE; // Placeholder, change it based on your actual simulation bar layout
    }
}


Input::~Input()
{
}
