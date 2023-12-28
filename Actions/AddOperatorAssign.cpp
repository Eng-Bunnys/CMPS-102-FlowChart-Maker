#include "AddOperatorAssign.h"
#include "../ApplicationManager.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"
#include <sstream>

/**
 * @brief Constructor for AddOperatorAssign class.
 * @param pAppManager Pointer to the ApplicationManager.
 */
AddOperatorAssign::AddOperatorAssign(ApplicationManager* pAppManager) : Action(pAppManager) {}

/**
 * @brief Reads parameters for adding an Operator Assignment statement from user input.
 *        Prompts the user to click on the flowchart to place the statement and enter relevant information.
 */
void AddOperatorAssign::ReadActionParameters() {
    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();

    // Prompt user to click on the flowchart to place the Operator Assignment statement
    pOut->PrintMessage("Click to place Operator Assignment Statement on the flowchart.");
    pIn->GetPointClicked(Position);
    pOut->ClearStatusBar();

    // Get the left-hand side (LHS) variable from user input
    pOut->PrintMessage("Enter the left-hand side (LHS) variable: ");
    LHS = pIn->GetVariable(pOut);

    // Get the first operand from user input
    while (true) {
        pOut->PrintMessage("Enter the first operand: ");
        RHSFirst = pIn->GetString(pOut);

        if (ValueOrVariable(RHSFirst) != INVALID_OP) break;
        else  pOut->PrintMessage("Invalid input for the first operand. Please enter a valid value or variable.");
    }

    // Get the arithmetic operator from user input
    Operator = pIn->GetArithOperator(pOut);

    // Get the second operand from user input
    while (true) {
        pOut->PrintMessage("Enter the second operand: ");
        RHSSecond = pIn->GetString(pOut);

        if (ValueOrVariable(RHSSecond) != INVALID_OP)   break;
        else pOut->PrintMessage("Invalid input for the second operand. Please enter a valid value or variable.");
    }
        
    pOut->ClearStatusBar();
}

/**
 * @brief Executes the action of adding an Operator Assignment statement to the flowchart.
 *        Creates a new OperatorAssign statement at the specified position and adds it to the list of statements.
 */
void AddOperatorAssign::Execute() {
    ReadActionParameters();

    // Calculate the top-left corner of the OperatorAssign statement block
    Point Corner;
    Corner.x = Position.x - UI.ASSGN_WDTH / 2;
    Corner.y = Position.y;

    // Create a new OperatorAssign statement
    OperatorAssign* pAssign = new OperatorAssign(Corner, LHS, RHSFirst, Operator, RHSSecond);

    // Add the created statement to the application manager's statement list
    pManager->AddStatement(pAssign);
}