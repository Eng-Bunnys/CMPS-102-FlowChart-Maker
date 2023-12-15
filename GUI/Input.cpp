
#include "Input.h"
#include "Output.h"
#include "../Utils.h"

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

///This function is now useless, I will keep it in-case one day it will not be
//char Input::GetChar(Output* pO) const
//{
//    char Key;
//    while (1)
//    {
//        pWind->WaitKeyPress(Key);
//        if (Key == 27)	//ESCAPE key is pressed
//            return '\0';	//Returns null character as the user has canceled input, I prefer returning null rather than an empty string
//        if ((Key == 8) || (Key == 13))	//BackSpace or ENTER key is pressed
//            return Key;
//        if (pO)
//        {
//            string str(1, Key); //Convert the char to a string
//            pO->PrintMessage(str);
//        }
//    }
//}


double Input::GetValue(Output* pO) const // Reads a double value from the user 
{
    double D = 0;
    string UserInput;

    pO->PrintMessage("Please enter a value");

    while (true) {
        UserInput = GetString(pO);

        if (IsValue(UserInput)) {
            D = Utils::StringToDouble(UserInput);
            break;
        }
        else pO->PrintMessage("Invalid Input, Enter a valid double: ");
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

string Input::GetArithOperator(Output* pO) const {
    string Operator;

    pO->PrintMessage("Enter an arithmetic operator: ");

    while (true) {
        Operator = GetString(pO);

        // Check if the entered operator is one of the valid arithmetic operators (+, -, *, /)
        if (Operator == "+" || Operator == "-" || Operator == "*" || Operator == "/") break; // Exit the loop if a valid operator is entered
        else pO->PrintMessage("Invalid Input, Enter a valid arithmetic operator: ");
    }

    return Operator;
}

string Input::GetCompOperator(Output* pO) const {
    string Operator;

    pO->PrintMessage("Enter a comparison operator: ");

    while (true) {
        Operator = GetString(pO);

        // Check if the entered operator is one of the valid comparison operators (==, !, <, >)
        if (Operator == "==" || Operator == "!" || Operator == "<" || Operator == ">" || Operator == ">=" || Operator == "<=" || Operator == "!=") break;  // Exit the loop if a valid operator is entered
        else pO->PrintMessage("Invalid Input, Enter a valid comparison operator: ");
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
        //[1] If user clicks on the Design Toolbar
        if (y >= 0 && y < UI.ToolBarHeight)
        {
            // Check which Design Menu item was clicked
            int ClickedItem = (x / UI.MenuItemWidth);
            switch (ClickedItem)
            {
            case ITM_SELECT:
                return SELECT;
            case ITM_EDIT:
                return EDIT_STAT;
            case ITM_SAVE:
                return SAVE;
            case ITM_LOAD:
                return LOAD;
            case ITM_READ:
                return ADD_READ;
            case ITM_WRITE:
                return ADD_WRITE;
            case ITM_VALUE_ASSIGN:
                return ADD_VALUE_ASSIGN;
            case ITM_VAR_ASSIGN:
                return ADD_VAR_ASSIGN;
            case ITM_OP_ASSIGN:
                return ADD_OPER_ASSIGN;
            case ITM_COND:
                return ADD_CONDITION;
            case ITM_START:
                return ADD_START;
            case ITM_END:
                return ADD_END;
            case ITM_CONNECTOR:
                return ADD_CONNECTOR;
            case ITM_PASTE:
                return PASTE;
            case ITM_COPY:
                return COPY;
            case ITM_DELETE:
                return DEL;
            case ITM_INPUT_OUTPUT:
                return ADD_INPUT_OUTPUT;
            case ITM_CHANGE_TO_SIM:
                return SWITCH_SIM_MODE;
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
    else // Application is in Simulation mode [Similar Logic]
    {
        //[1] If user clicks on the Simulation Toolbar
        if (y >= 0 && y < UI.ToolBarHeight)
        {
            // Check which Simulation Menu item was clicked
            int ClickedItem = (x / UI.MenuItemWidth);
            switch (ClickedItem)
            {
            case ITM_SELECT_SIM:
                return SELECT;
            case ITM_EDIT_SIM:
                return EDIT_STAT;
            case ITM_SAVE_SIM:
                return SAVE;
            case ITM_LOAD_SIM:
                return LOAD;
            case ITM_VALIDATE:
                return SIM_VALIDATE;
            case ITM_RUN:
                return SIM_RUN;
            case ITM_CHANGE_TO_DSN_SIM:
                return SWITCH_DSN_MODE;
            case ITM_EXIT_SIM:
                return EXIT;
            }
        }

        return SWITCH_DSN_MODE;
    }
}

Input::~Input()
{
}
