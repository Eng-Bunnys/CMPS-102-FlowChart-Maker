#include "AddRead.h"

#include "../ApplicationManager.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"
#include "../Statements/Read.h"

/**
 * @brief Constructs an AddRead object with the given ApplicationManager.
 *
 * @param pAppManager Pointer to the ApplicationManager.
 */
AddRead::AddRead(ApplicationManager* pAppManager) : Action(pAppManager)
{}

/**
 * @brief Reads parameters required for adding a Read statement.
 *
 * This function prompts the user to click on the drawing area to
 * add the Read statement, asks for the variable to be read, and
 * validates the input.
 */
void AddRead::ReadActionParameters()
{
    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();

    // Read the (Position) parameter
    pOut->PrintMessage("Click to add the read statement.");
    pIn->GetPointClicked(Position);
    pOut->ClearStatusBar();

    // Ask the user to enter the variable to be read
    pOut->PrintMessage("Please enter the variable to be read");
    Variable = pIn->GetVariable(pOut);
}

/**
 * @brief Executes the action of adding a Read statement.
 *
 * This function creates a new Read statement, sets its attributes
 * based on the parameters obtained in ReadActionParameters(), and
 * adds the statement to the ApplicationManager's statement list.
 */
void AddRead::Execute()
{
    ReadActionParameters();
    if (Position.x > 0 && Position.x <= UI.DrawingAreaWidth && Position.y >= UI.ToolBarHeight && Position.y <= UI.height - 50) {

        // Calculating left corner of assignment statement block
        Point Corner;
        Corner.x = Position.x - UI.IO_WDTH / 2;
        Corner.y = Position.y;

        Read* pAssign = new Read(Corner, Variable);

        pManager->AddStatement(pAssign);
    }
    else {
        Output* pOut = pManager->GetOutput();
        pOut->PrintMessage("Can't Draw Outside Drawing Area");
    }
}