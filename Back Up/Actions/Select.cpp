#include "Select.h"
#include "../ApplicationManager.h"

/**
 * @brief Constructor for the Select class.
 * @param appManager Pointer to the ApplicationManager.
 */
Select::Select(ApplicationManager* appManager) : Action(appManager) {
}

/**
 * @brief Reads parameters for the action from user input.
 *        Prompts the user to click on the flowchart to select a statement or connector.
 */
void Select::ReadActionParameters() {
    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();

    // Prompt the user to click on the flowchart to select a statement or connector
    pOut->PrintMessage("Select a statement or connector");
    pIn->GetPointClicked(Position);
    pOut->ClearStatusBar();
}

/**
 * @brief Executes the action of selecting or deselecting a statement based on user input.
 *        Reads the position clicked by the user, gets the corresponding statement, and updates the interface accordingly.
 */
void Select::Execute() {
    ReadActionParameters();

    // Get the statement at the clicked position
    Statement* SelectedStatement = pManager->GetStatement(Position);

    // If no statement is found at the clicked position, exit the function
    if (!SelectedStatement) return;

    // Check if the statement was previously selected
    bool WasSelectedBool = SelectedStatement->IsSelected();

    // Get the currently selected statement
    Statement* ClickedStatement = pManager->GetSelectedStatement();

    // If the clicked statement is different from the currently selected one
    if (SelectedStatement != ClickedStatement) {
        // Deselect the currently selected statement, if any
        if (ClickedStatement) ClickedStatement->SetSelected(false);

        // Select the clicked statement
        SelectedStatement->SetSelected(true);

        // Set the clicked statement as the selected one
        pManager->SetSelectedStatement(SelectedStatement);
    }

    // Update the interface
    pManager->UpdateInterface();
}