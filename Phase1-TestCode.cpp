
#include "HelperFn.h"
#include "GUI\\Input.h"
#include "GUI\\Output.h"
#include <iostream>

int main()
{
	Point P;

	Output* pOut = new Output();
	Input* pIn = pOut->CreateInput();

	///Testing Helper Functions

	pOut->PrintMessage("TEST0: Testing the helper functions");
	pOut->PrintMessage("Enter a double string");
	string DoubleInputString = pIn->GetString(pOut);

	if (IsValue(DoubleInputString)) pOut->PrintMessage("The string entered is a double, click anywhere to continue.");
	else pOut->PrintMessage("The string entered is not a double, click anywhere to continue.");

	pIn->GetPointClicked(P);

	pOut->PrintMessage("Enter a variable name");
	string VariableInputString = pIn->GetString(pOut);

	if (IsVariable(VariableInputString)) pOut->PrintMessage("The entered string is a variable, click anywhere to continue.");
	else pOut->PrintMessage("The entered string is not a variable, click anywhere to continue.");

	pIn->GetPointClicked(P);

	pOut->PrintMessage("Enter a string");
	string ValueOrVariableInputString = pIn->GetString(pOut);

	OpType OutputResult = ValueOrVariable(ValueOrVariableInputString);

	if (OutputResult == VALUE_OP)
		pOut->PrintMessage("The entered string is a value, click anywhere to continue.");
	if (OutputResult == VARIABLE_OP)
		pOut->PrintMessage("The entered string is a variable, click anywhere to continue.");
	if (OutputResult == INVALID_OP)
		pOut->PrintMessage("The entered string is neither a value nor a variable, click anywhere to continue.");

	pIn->GetPointClicked(P);

	pOut->PrintMessage("This demo is to test input and output classes, Click anywhere to start the test");
	pIn->GetPointClicked(P);

	pOut->PrintMessage("TEST1: Drawing Tool bar and Status bar, Click anywhere to continue");
	pIn->GetPointClicked(P); // Wait for any click

	pOut->PrintMessage("TEST2: Now we will show that Output class can draw any statement in any status, Click anywhere to continue");
	pIn->GetPointClicked(P); // Wait for any click

	/// 2.1- Assignment statement test
	pOut->PrintMessage("Drawing Simple Assignment statements in ALL STATES, Click to continue");

	// Drawing (normal) (empty) assignment statement --> STATE 1
	P.x = 100;
	P.y = 100;
	pOut->DrawAssign(P, UI.ASSGN_WDTH, UI.ASSGN_HI, " = ");

	// Drawing (highlighted) (empty) assignment statement --> STATE 2
	P.x = 300;
	P.y = 100;
	pOut->DrawAssign(P, UI.ASSGN_WDTH, UI.ASSGN_HI, " = ", true);

	// Drawing a resized empty assignment statement
	P.x = 100;
	P.y = 200;
	pOut->DrawAssign(P, 80, UI.ASSGN_HI, " = ");

	// Drawing edited (normal) (non-empty) assignment statement --> STATE 3
	P.x = 100;
	P.y = 300;
	pOut->DrawAssign(P, UI.ASSGN_WDTH, UI.ASSGN_HI, "Salary = 3000");

	// Drawing (highlighted) (non-empty) assignment statement --> STATE 4
	P.x = 300;
	P.y = 300;
	pOut->DrawAssign(P, UI.ASSGN_WDTH, UI.ASSGN_HI, "Salary = 3000", true);

	pIn->GetPointClicked(P); // Wait for any click
	pOut->ClearDrawArea();

	/// 2.2- Variable assignment & single operator assignment
	pOut->PrintMessage("Drawing other Assignment statements in ALL STATES, Click to continue");

	// Drawing (normal) (empty) variable assignment statement --> STATE 1
	P.x = 100;
	P.y = 100;
	pOut->DrawAssign(P, UI.ASSGN_WDTH, UI.ASSGN_HI, "x = ");

	// Drawing (highlighted) (empty) variable assignment statement --> STATE 2
	P.x = 300;
	P.y = 100;
	pOut->DrawAssign(P, UI.ASSGN_WDTH, UI.ASSGN_HI, "x = ", true);

	// Drawing a resized empty variable assignment statement
	P.x = 100;
	P.y = 200;
	pOut->DrawAssign(P, 80, UI.ASSGN_HI, "y = ");

	// Drawing edited (normal) (non-empty) variable assignment statement --> STATE 3
	P.x = 100;
	P.y = 300;
	pOut->DrawAssign(P, UI.ASSGN_WDTH, UI.ASSGN_HI, "total = 100");

	// Drawing (highlighted) (non-empty) variable assignment statement --> STATE 4
	P.x = 300;
	P.y = 300;
	pOut->DrawAssign(P, UI.ASSGN_WDTH, UI.ASSGN_HI, "total = 100", true);

	// Drawing (normal) (empty) single operator assignment statement --> STATE 5
	P.x = 100;
	P.y = 400;
	pOut->DrawAssign(P, UI.ASSGN_WDTH, UI.ASSGN_HI, "= 42");

	// Drawing (highlighted) (empty) single operator assignment statement --> STATE 6
	P.x = 300;
	P.y = 400;
	pOut->DrawAssign(P, UI.ASSGN_WDTH, UI.ASSGN_HI, "= 42", true);

	// Drawing a resized empty single operator assignment statement
	P.x = 500;
	P.y = 100;
	pOut->DrawAssign(P, 80, UI.ASSGN_HI, "= 42");

	// Drawing edited (normal) (non-empty) single operator assignment statement --> STATE 7
	P.x = 500;
	P.y = 200;
	pOut->DrawAssign(P, UI.ASSGN_WDTH, UI.ASSGN_HI, "Grade = 46");

	// Drawing (highlighted) (non-empty) single operator assignment statement --> STATE 8
	P.x = 700;
	P.y = 100;
	pOut->DrawAssign(P, UI.ASSGN_WDTH, UI.ASSGN_HI, "Grade = 46", true);

	pIn->GetPointClicked(P); // Wait for any click
	pOut->ClearDrawArea();

	/// 2.3- Conditional statement test
	pOut->PrintMessage("Drawing Conditional Statement in ALL STATES, Click to continue");

	// Drawing Conditional statement (normal) --> STATE 1
	P.x = 100;
	P.y = 200;
	pOut->DrawConditionalStat(P, UI.ASSGN_WDTH, UI.ASSGN_HI, "If x > y");

	// Drawing Conditional statement (highlighted) --> STATE 2
	P.x = 300;
	P.y = 200;
	pOut->DrawConditionalStat(P, UI.ASSGN_WDTH, UI.ASSGN_HI, "If x > y", true);

	// Drawing resized Conditional statement (empty) --> STATE 3
	P.x = 100;
	P.y = 300;
	pOut->DrawConditionalStat(P, 120, UI.ASSGN_HI, "");

	// Drawing resized Conditional statement (non-empty) --> STATE 4
	P.x = 300;
	P.y = 300;
	pOut->DrawConditionalStat(P, 120, UI.ASSGN_HI, "If x < y");

	pIn->GetPointClicked(P); // Wait for any click
	pOut->ClearDrawArea();

	/// 2.4- Read statement test
	pOut->PrintMessage("Drawing Read Statement in ALL STATES, Click to continue");

	// Drawing Read statement (normal) --> STATE 1
	P.x = 100;
	P.y = 200;
	pOut->DrawRead(P, UI.ASSGN_WDTH, UI.ASSGN_HI, "Read x");

	// Drawing Read statement (highlighted) --> STATE 2
	P.x = 300;
	P.y = 200;
	pOut->DrawRead(P, UI.ASSGN_WDTH, UI.ASSGN_HI, "Read x", true);

	// Drawing resized Read statement (empty) --> STATE 3
	P.x = 100;
	P.y = 300;
	pOut->DrawRead(P, 120, UI.ASSGN_HI, "");

	// Drawing resized Read statement (non-empty) --> STATE 4
	P.x = 300;
	P.y = 300;
	pOut->DrawRead(P, 120, UI.ASSGN_HI, "Read y");

	pIn->GetPointClicked(P); // Wait for any click
	pOut->ClearDrawArea();

	/// 2.5- Write statement test
	pOut->PrintMessage("Drawing Write Statement in ALL STATES, Click to continue");

	// Drawing Write statement (normal) --> STATE 1
	P.x = 100;
	P.y = 200;
	pOut->DrawWrite(P, UI.ASSGN_WDTH, UI.ASSGN_HI, "Write x");

	// Drawing Write statement (highlighted) --> STATE 2
	P.x = 300;
	P.y = 200;
	pOut->DrawWrite(P, UI.ASSGN_WDTH, UI.ASSGN_HI, "Write x", true);

	// Drawing resized Write statement (empty) --> STATE 3
	P.x = 100;
	P.y = 300;
	pOut->DrawWrite(P, 120, UI.ASSGN_HI, "");

	// Drawing resized Write statement (non-empty) --> STATE 4
	P.x = 300;
	P.y = 300;
	pOut->DrawWrite(P, 120, UI.ASSGN_HI, "Write y");

	pIn->GetPointClicked(P); // Wait for any click
	pOut->ClearDrawArea();

	/// 2.6- Start & End statements test
	pOut->PrintMessage("Drawing Start & End Statements in ALL STATES, Click to continue");

	// Drawing Start statement (normal) --> STATE 1
	P.x = 100;
	P.y = 200;
	pOut->DrawStart(P, UI.ASSGN_WDTH, UI.ASSGN_HI, "Start");

	// Drawing Start statement (highlighted) --> STATE 2
	P.x = 300;
	P.y = 200;
	pOut->DrawStart(P, UI.ASSGN_WDTH, UI.ASSGN_HI, "Start", true);

	// Drawing resized Start statement (empty) --> STATE 3
	P.x = 100;
	P.y = 300;
	pOut->DrawStart(P, 120, UI.ASSGN_HI, "");

	// Drawing resized Start statement (non-empty) --> STATE 4
	P.x = 300;
	P.y = 300;
	pOut->DrawStart(P, 120, UI.ASSGN_HI, "Start");

	// Drawing End statement (normal) --> STATE 5
	P.x = 500;
	P.y = 200;
	pOut->DrawEnd(P, UI.ASSGN_WDTH, UI.ASSGN_HI, "End");

	// Drawing End statement (highlighted) --> STATE 6
	P.x = 700;
	P.y = 200;
	pOut->DrawEnd(P, UI.ASSGN_WDTH, UI.ASSGN_HI, "End", true);

	// Drawing resized End statement (empty) --> STATE 7
	P.x = 500;
	P.y = 300;
	pOut->DrawEnd(P, 120, UI.ASSGN_HI, "");

	// Drawing resized End statement (non-empty) --> STATE 8
	P.x = 700;
	P.y = 300;
	pOut->DrawEnd(P, 120, UI.ASSGN_HI, "End");

	pIn->GetPointClicked(P); // Wait for any click
	pOut->ClearDrawArea();

	/// 2.7- Connector test
	// Drawing Connector in all possible states
	pOut->PrintMessage("Drawing Connector in Normal and Highlighted STATES, Click to continue");

	// Drawing Connector (normal)
	Point StartPointNormal;
	StartPointNormal.x = 100;
	StartPointNormal.y = 200;

	Point EndPointNormal;
	EndPointNormal.x = 300; // Choose the x-coordinate for the second point
	EndPointNormal.y = 200; // Choose the y-coordinate for the second point

	pOut->DrawConnector(StartPointNormal, EndPointNormal);

	// Drawing Connector (highlighted)
	Point StartPointHighlighted;
	StartPointHighlighted.x = 300;
	StartPointHighlighted.y = 300;

	Point EndPointHighlighted;
	EndPointHighlighted.x = 350; // Choose the x-coordinate for the second point
	EndPointHighlighted.y = 300; // Choose the y-coordinate for the second point

	pOut->DrawConnector(StartPointHighlighted, EndPointHighlighted, true);

	pIn->GetPointClicked(P); // Wait for any click
	pOut->ClearDrawArea();

	/// 2.8- Draw String TEST
	// Drawing a String in a specific location
	pOut->PrintMessage("Drawing A String, Click to continue");

	// Getting a String from the user
	pOut->PrintMessage("Enter a string");
	string userString = pIn->GetString(pOut);

	// Drawing that string in location (400, 200)
	pOut->DrawString(400, 200, userString);

	pIn->GetPointClicked(P); // Wait for any click
	pOut->ClearDrawArea();

	///////////////////////////////////////////////////////////////////////////////////
	// TEST 3: Read strings and a value from the user
	///////////////////////////////////////////////////////////////////////////////////
	pOut->PrintMessage("TEST3: Now Time to test class Input, Click anywhere to continue");
	// Test 3: Read strings and a value from the user
	pIn->GetPointClicked(P); // Wait for any click

	// Clear previous messages
	pOut->ClearStatusBar();

	// Test GetValue
	double value = pIn->GetValue(pOut);
	pOut->PrintMessage("You entered value: " + std::to_string(value));

	// Wait for another click
	pIn->GetPointClicked(P);

	// Clear previous messages
	pOut->ClearStatusBar();

	// Test GetVariable
	string variable = pIn->GetVariable(pOut);
	pOut->PrintMessage("You entered variable: " + variable);
	pIn->GetPointClicked(P); // Wait for any click

	pOut->PrintMessage("Testing Input ability to read strings, values, variables and operators");

	// Test reading an arithmetic operator
	pOut->PrintMessage("TEST: Enter an arithmetic operator (+, -, *, /)");
	std::string arithmeticOperator = pIn->GetArithOperator(pOut);
	pOut->PrintMessage("Entered arithmetic operator: " + arithmeticOperator);
	pOut->ClearDrawArea();
	pIn->GetPointClicked(P); // Wait for any click

	// Test reading a comparison operator
	pOut->PrintMessage("TEST: Enter a comparison operator (=, !, <, >)");
	std::string comparisonOperator = pIn->GetCompOperator(pOut);
	pOut->PrintMessage("Entered comparison operator: " + comparisonOperator);
	pOut->ClearDrawArea();
	pIn->GetPointClicked(P); // Wait for any click

	///////////////////////////////////////////////////////////////////////////////////
	// TEST 4: Check for the user action
	///////////////////////////////////////////////////////////////////////////////////
	pOut->PrintMessage("TEST4: Testing Input ability to detect User Action, click anywhere");

	ActionType ActType;

	////////////
	// TODO:  You must add a case for EACH action in the following (switch case)
	////////////
	////COMPLETE THE SWITCH CASE WITH ALL THE ACTIONS

	do
	{
		ActType = pIn->GetUserAction();

		switch (ActType)
		{
		case ADD_VALUE_ASSIGN:
			pOut->PrintMessage("Action: add value assignment statement, Click anywhere");
			// TODO: Add additional testing or assertions for this action
			break;

		case ADD_CONDITION:
			pOut->PrintMessage("Action: add conditional statement, Click anywhere");
			// TODO: Add additional testing or assertions for this action
			break;

		case ADD_CONNECTOR:
			pOut->PrintMessage("Action: add a connector, Click anywhere");
			// TODO: Add additional testing or assertions for this action
			break;

		case SELECT:
			pOut->PrintMessage("Action: select action, Click anywhere");
			// TODO: Add additional testing or assertions for this action
			break;

		case STATUS:
			pOut->PrintMessage("Action: a click on the Status Bar, Click anywhere");
			// TODO: Add additional testing or assertions for this action
			break;

		case DSN_TOOL:
			pOut->PrintMessage("Action: a click on the Design Tool Bar, Click anywhere");
			// TODO: Add additional testing or assertions for this action
			break;

		case SWITCH_SIM_MODE:
			pOut->PrintMessage("Action: Switch to Simulation Mode, creating simulation tool bar");
			// TODO: Add additional testing or assertions for this action
			pOut->CreateSimulationToolBar(); // THIS TESTS Output::CreateSimulationToolBar() function //////
			break;

		case SWITCH_DSN_MODE:
			pOut->PrintMessage("Action: Switch to Design Mode, creating Design tool bar");
			// TODO: Add additional testing or assertions for this action
			pOut->CreateDesignToolBar();
			break;

		case EXIT:
			break;
		}
	} while (ActType != EXIT);

	/// Exiting
	pOut->PrintMessage("Action: EXIT, test is finished, click anywhere to exit");
	pIn->GetPointClicked(P);

	delete pIn;
	delete pOut;
	return 0;
}
