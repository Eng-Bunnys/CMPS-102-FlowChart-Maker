#include "AddVariableAssign.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "../Statements/ConditionalStatement.h"

/**
 * @brief Constructor for the AddVariableAssign class.
 * @param pAppManager Pointer to the ApplicationManager.
 */
AddVariableAssign::AddVariableAssign(ApplicationManager* pAppManager) : Action(pAppManager) {}

/**
 * @brief Read input parameters for the Variable Assignment statement.
 *
 * Prompts the user to click on the flowchart to place the statement,
 * and then prompts the user to enter the left-hand side (LHS) and
 * right-hand side (RHS) of the assignment statement.
 */
void AddVariableAssign::ReadActionParameters()
{
    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();

    // Prompt user to click on the flowchart to place the Variable Assignment statement
    pOut->PrintMessage("Variable Assignment Statement: Click to add the statement");
    pIn->GetPointClicked(Position);
    pOut->ClearStatusBar();

    // Prompt the user in the status bar to enter the LHS and set the data member
    pOut->PrintMessage("Enter the left-hand side (LHS) of the assignment statement:");
    LHS = pIn->GetVariable(pOut);

    // Prompt the user in the status bar to enter the RHS and set the data member
    pOut->PrintMessage("Enter the right-hand side (RHS) of the assignment statement:");
    RHS = pIn->GetVariable(pOut);
    pOut->ClearStatusBar();
}

/**
 * @brief Execute the action (add Variable Assignment statement).
 *
 * Reads action parameters, calculates the left corner of the assignment
 * statement block, creates a new VariableAssign statement, and adds it
 * to the application manager's statement list.
 */
void AddVariableAssign::Execute()
{
    ReadActionParameters();

    // Calculating the left corner of the assignment statement block
    if (Position.x > 0 && Position.x <= UI.DrawingAreaWidth &&
        Position.y >= UI.ToolBarHeight && Position.y <= UI.height - 50) {
        Point Corner;
        Corner.x = Position.x - UI.ASSGN_WDTH / 2;
        Corner.y = Position.y;

        // Create a new VariableAssign statement
        VariableAssign* pAssign = new VariableAssign(Corner, LHS, RHS);

        // Add the created statement to the application manager's statement list
        pManager->AddStatement(pAssign);
    }
    else {
        Output* pOut = pManager->GetOutput();
        pOut->PrintMessage("Can't Draw Outside Drawing Area");
    }
}