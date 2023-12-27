#include "AddStart.h"
#include "../ApplicationManager.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"
#include "../Statements/Start.h"

#include <sstream>

using namespace std;

/**
 * @brief Constructor for AddStart action.
 *
 * Initializes the AddStart action with the provided ApplicationManager.
 * @param pAppManager Pointer to the ApplicationManager.
 */
AddStart::AddStart(ApplicationManager* pAppManager) : Action(pAppManager)
{}

/**
 * @brief Reads action parameters for AddStart.
 *
 * Prompts the user to click on the flowchart to place the Start statement.
 */
void AddStart::ReadActionParameters()
{
    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();

    // Read the (Position) parameter
    pOut->PrintMessage("Start Statement: Click to add the statement");
    pIn->GetPointClicked(Position);
    pOut->ClearStatusBar();
}

/**
 * @brief Executes the AddStart action.
 *
 * Calculates the left corner of the Start statement block and adds the created statement to the application manager's statement list.
 */
void AddStart::Execute()
{
    // Calculating the left corner of the assignment statement block
    ReadActionParameters();

    if (Position.x > 0 && Position.x <= UI.DrawingAreaWidth && Position.y >= UI.ToolBarHeight && Position.y <= UI.height - 50)
    {
        Point Corner;
        Corner.x = Position.x - UI.START_WDTH / 2;
        Corner.y = Position.y;

        Start* pAssign = new Start(Corner);
        pManager->AddStatement(pAssign);
    }
    else
    {
        Output* pOut = pManager->GetOutput();
        pOut->PrintMessage("Can't Draw Outside Drawing Area");
    }
}