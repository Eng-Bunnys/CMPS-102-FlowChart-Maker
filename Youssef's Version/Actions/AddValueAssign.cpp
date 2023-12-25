#include "AddValueAssign.h"
#include "../ApplicationManager.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"
#include <sstream>

/**
 * @brief Constructor for AddValueAssign class.
 * @param pAppManager Pointer to the ApplicationManager.
 */
AddValueAssign::AddValueAssign(ApplicationManager* pAppManager) : Action(pAppManager) {}

/**
 * @brief Reads parameters for adding a Value Assignment statement from user input.
 *        Prompts the user to click on the flowchart to place the statement and enter relevant information.
 */
void AddValueAssign::ReadActionParameters()
{
    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();

    // Prompt user to click on the flowchart to place the Value Assignment statement
    pOut->PrintMessage("Value Assignment Statement: Click to add the statement");
    pIn->GetPointClicked(Position);
    pOut->ClearStatusBar();

    // Prompt the user in the status bar to enter the LHS and set the data member
    pOut->PrintMessage("Enter the left-hand side (LHS) of the assignment statement:");
    LHS = pIn->GetVariable(pOut);

    // Prompt the user in the status bar to enter the RHS and set the data member
    pOut->PrintMessage("Enter the right-hand side (RHS) of the assignment statement:");
    RHS = pIn->GetValue(pOut);
    pOut->ClearStatusBar();
}

/**
 * @brief Executes the action of adding a Value Assignment statement to the flowchart.
 *        Creates a new ValueAssign statement at the specified position and adds it to the list of statements.
 */
void AddValueAssign::Execute()
{
    ReadActionParameters();

    // Calculate the top-left corner of the assignment statement block
    Point Corner;
    Corner.x = Position.x - UI.ASSGN_WDTH / 2;
    Corner.y = Position.y;

    // Create a new ValueAssign statement
    ValueAssign* pAssign = new ValueAssign(Corner, LHS, RHS);

    // Add the created statement to the application manager's statement list
    pManager->AddStatement(pAssign);
}