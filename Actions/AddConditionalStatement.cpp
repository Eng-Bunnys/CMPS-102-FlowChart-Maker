#include "AddConditionalStatement.h"
#include "../ApplicationManager.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"

#include <sstream>
using namespace std;

/**
 * @brief Constructor for AddConditional class.
 * @param pAppManager Pointer to the ApplicationManager.
 */
AddConditional::AddConditional(ApplicationManager* pAppManager) : Action(pAppManager)
{}

/**
 * @brief Reads parameters for the conditional statement from the user.
 */
void AddConditional::ReadActionParameters() {
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
    ComparisonOperator = pIn->GetCompOperator(pOut);

    // Get the RHS of the conditional statement from user input
    pOut->PrintMessage("Enter the RHS:");
    while (true) {
        RHS = pIn->GetString(pOut);
        if (ValueOrVariable(RHS) != INVALID_OP) break;  // Validate RHS
        pOut->PrintMessage("Invalid RHS. Enter a valid value or variable.");
    }
}

/**
 * @brief Executes the action to add a conditional statement.
 */
void AddConditional::Execute() {
    ReadActionParameters();
    if (Position.x > 0 && Position.x <= UI.DrawingAreaWidth && Position.y >= UI.ToolBarHeight && Position.y <= UI.height - 50) {
        // Calculate left corner of assignment statement block
        Point Corner;
        Corner.x = Position.x - UI.COND_WDTH / 2;
        Corner.y = Position.y + UI.COND_HI / 2;

        // Create a new Conditional statement
        Conditional* pAssign = new Conditional(Corner, LHS, ComparisonOperator, RHS);

        // Add the statement to the application manager
        pManager->AddStatement(pAssign);
    }
    else {
        Output* pOut = pManager->GetOutput();
        pOut->PrintMessage("Can't Draw Outside Drawing Area");
    }
}