#include "AddEnd.h"
#include "../ApplicationManager.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"
#include "../Actions/Action.h"
#include "../Statements/End.h"

 /**
  * @brief Constructor for the AddEnd class.
  * @param pAppManager Pointer to the ApplicationManager.
  */
AddEnd::AddEnd(ApplicationManager* pAppManager) : Action(pAppManager) {}

/**
 * @brief Reads the parameters for adding an End statement from user input.
 *        Prompts the user to click on the flowchart to place the End statement.
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
 * @brief Executes the action of adding an End statement to the flowchart.
 *        Creates a new End statement at the specified position and adds it to the list of statements.
 */
void AddEnd::Execute()
{
    ReadActionParameters();

    // Create a new End statement at the specified position
    End* pEnd = new End(Position);

    // Add the statement to the list of statements
    pManager->AddStatement(pEnd);
}