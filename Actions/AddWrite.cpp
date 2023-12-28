#include "AddWrite.h"

#include "../ApplicationManager.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"

/**
 * @brief Constructs an AddWrite object with the given ApplicationManager.
 *
 * @param pAppManager Pointer to the ApplicationManager.
 */
AddWrite::AddWrite(ApplicationManager* pAppManager) : Action(pAppManager)
{}

/**
 * @brief Reads parameters required for adding a Write statement.
 *
 * This function prompts the user to click on the drawing area to
 * add the Write statement, asks for the variable or message to be written,
 * and validates the input.
 */
void AddWrite::ReadActionParameters()
{
    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();

    // Read the (Position) parameter
    pOut->PrintMessage("Write Statement: Click to add the statement");
    pIn->GetPointClicked(Position);
    pOut->ClearStatusBar();

    // Ask the user to enter the variable or message to be written
    pOut->PrintMessage("Please enter the variable or the message to be written");
    Variable = pIn->GetString(pOut);
    while (!IsVariable(Variable) && (Variable[0] != '"' || Variable[Variable.length() - 1] != '"')) {
        pOut->PrintMessage("Please enter a valid variable or a valid message to be written");
        Variable = pIn->GetString(pOut);
    }
}

/**
 * @brief Executes the action of adding a Write statement.
 *
 * This function creates a new Write statement, sets its attributes
 * based on the parameters obtained in ReadActionParameters(), and
 * adds the statement to the ApplicationManager's statement list.
 */
void AddWrite::Execute()
{
    ReadActionParameters();

    // Calculating the left corner of the assignment statement block
    if (Position.x > 0 && Position.x <= UI.DrawingAreaWidth && Position.y >= UI.ToolBarHeight && Position.y <= UI.height - 50) {
        Point Corner;
        Corner.x = Position.x - UI.IO_WDTH / 2;
        Corner.y = Position.y;

        Write* pAssign = new Write(Corner, "");
        pAssign->setVariable(Variable);

        pManager->AddStatement(pAssign);
    }
    else {
        Output* pOut = pManager->GetOutput();
        pOut->PrintMessage("Can't Draw Outside Drawing Area");
    }
}