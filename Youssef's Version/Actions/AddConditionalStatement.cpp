#include "AddConditionalStatement.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "../Statements/ConditionalStatement.h"

 // Constructor
AddConditionalStatement::AddConditionalStatement(ApplicationManager* pAppManager) : Action(pAppManager) {}

/**
 * @brief Reads the parameters for the conditional statement from user input.
 */
void AddConditionalStatement::ReadActionParameters() {
    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();

    // Prompt user to click on the flowchart to place the statement
    pOut->PrintMessage("Click to place the conditional statement.");
    pIn->GetPointClicked(Position);

    // Get the LHS of the conditional statement from user input
    pOut->PrintMessage("Enter the LHS:");
    while (true) {
        LHS = pIn->GetString(pOut);
        if (ValueOrVariable(LHS) != INVALID_OP) break;  // Validate LHS
        pOut->PrintMessage("Invalid LHS. Enter a valid value or variable.");
    }

    // Get the comparison operator from user input
    CompOperator = pIn->GetCompOperator(pOut);

    // Get the RHS of the conditional statement from user input
    pOut->PrintMessage("Enter the RHS:");
    while (true) {
        RHS = pIn->GetString(pOut);
        if (ValueOrVariable(RHS) != INVALID_OP) break;  // Validate RHS
        pOut->PrintMessage("Invalid RHS. Enter a valid value or variable.");
    }
}

/**
 * @brief Executes the action of adding the conditional statement to the flowchart.
 */
void AddConditionalStatement::Execute() {
    ReadActionParameters();  // Get parameters for the conditional statement

    // Calculate the top-left corner of the statement's bounding box
    Point Corner(Position.x - UI.COND_WDTH / 2, Position.y);

    // Create a new conditional statement object
    ConditionalStatement* pCondStmt = new ConditionalStatement(Corner, LHS, CompOperator, RHS);

    // Add the statement to the application manager's list of statements
    pManager->AddStatement(pCondStmt);
}