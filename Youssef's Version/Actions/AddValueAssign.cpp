#include "AddValueAssign.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

// Constructor: set the ApplicationManager pointer inside this action
AddValueAssign::AddValueAssign(ApplicationManager *pAppManager) : Action(pAppManager) {}

void AddValueAssign::ReadActionParameters()
{
    Input *pIn = pManager->GetInput();
    Output *pOut = pManager->GetOutput();

    // Read the (Position) parameter
    pOut->PrintMessage("Value Assignment Statement: Click to add the statement");

    pIn->GetPointClicked(Position);
    pOut->ClearStatusBar();

    // Ask the user in the status bar to enter the LHS and set the data member
    pOut->PrintMessage("Enter the left-hand side (LHS) of the assignment statement:");
    LHS = pIn->GetVariable(pOut);

    // Ask the user in the status bar to enter the RHS and set the data member
    pOut->PrintMessage("Enter the right-hand side (RHS) of the assignment statement:");
    RHS = pIn->GetValue(pOut);
}

void AddValueAssign::Execute()
{
    ReadActionParameters();

    // Calculating the left corner of the assignment statement block
    Point Corner;
    Corner.x = Position.x - UI.ASSGN_WDTH / 2;
    Corner.y = Position.y;

    // Create a new ValueAssign statement
    ValueAssign *pAssign = new ValueAssign(Corner, LHS, RHS);

    pManager->AddStatement(pAssign); // Adds the created statement to the application manager's statement list
}
