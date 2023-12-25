#include "AddStart.h"
#include "../ApplicationManager.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"
#include "../Actions/Action.h"
#include "../Statements/Start.h"

/**
 * @brief Constructor for AddStart class.
 * @param pAppManager Pointer to the ApplicationManager.
 */
AddStart::AddStart(ApplicationManager* pAppManager) : Action(pAppManager) {}

/**
 * @brief Reads parameters for adding a Start statement from user input.
 *        Prompts the user to click on the flowchart to place the statement.
 */
void AddStart::ReadActionParameters()
{
    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();

    // Prompt user to click on the flowchart to place the Start statement
    pOut->PrintMessage("Start Statement: Click to add the statement");
    pIn->GetPointClicked(Position);
    pOut->ClearStatusBar();
}

/**
 * @brief Executes the action of adding a Start statement to the flowchart.
 *        Creates a new Start statement at the specified position and adds it to the list of statements.
 */
void AddStart::Execute()
{
    ReadActionParameters();

    // Create a new Start statement at the specified position
    Start* pStart = new Start(Position);

    // Add the statement to the list of statements
    pManager->AddStatement(pStart);
}