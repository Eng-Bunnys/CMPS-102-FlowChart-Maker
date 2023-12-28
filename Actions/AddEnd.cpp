#include "AddEnd.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "../Statements/End.h"

#include <sstream>

AddEnd::AddEnd(ApplicationManager* pAppManager) : Action(pAppManager)
{}

/**
 * @brief Reads parameters for adding an End statement.
 *
 * Prompts the user to click on the flowchart to place the End statement.
 */
void AddEnd::ReadActionParameters()
{
    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();

    // Prompt user to click on the flowchart to place the End statement
    pOut->PrintMessage("Click to add the end statement");
    pIn->GetPointClicked(Position);
    pOut->ClearStatusBar();
}

/**
 * @brief Executes the action to add an End statement to the flowchart.
 *
 * Calculates the left corner of the End statement block and adds
 * the created End statement to the application manager's statement list.
 */
void AddEnd::Execute()
{
    ReadActionParameters();

    if (Position.x > 0 && Position.x <= UI.DrawingAreaWidth && Position.y >= UI.ToolBarHeight && Position.y <= UI.height - 50)
    {
        // Calculating left corner of End statement block
        Point Corner;
        Corner.x = Position.x - UI.START_WDTH / 2;
        Corner.y = Position.y;

        End* pEndStatement = new End(Corner);

        pManager->AddStatement(pEndStatement);
    }
    else
    {
        Output* pOut = pManager->GetOutput();
        pOut->PrintMessage("Can't Draw Outside Drawing Area");
    }
}