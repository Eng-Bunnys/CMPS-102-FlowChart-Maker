#include "Edit.h"
#include "../Statements/Statement.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"

/**
 * @brief Constructs an Edit object with the given ApplicationManager.
 *
 * @param pManager Pointer to the ApplicationManager.
 */
Edit::Edit(ApplicationManager* pManager)
	:Action(pManager)
{
}

/**
 * @brief Reads parameters required for the edit action to execute.
 *
 * This function is currently empty as there are no specific parameters
 * needed for the edit action in this implementation.
 */
void Edit::ReadActionParameters()
{
	// No parameters to read for the Edit action.
}

/**
 * @brief Executes the edit action.
 *
 * This function checks if a statement is selected and if so,
 * it invokes the Edit function of the selected statement.
 * If no statement is selected, it prints a message indicating
 * that no statement is selected for editing.
 */
void Edit::Execute()
{
	Statement* pStat = pManager->GetSelectedStatement();
	if (pStat != NULL)
	{
		pStat->Edit(pManager);
		pStat->SetSelected(false);
		pManager->SetSelectedStatement(NULL);
		return;
	}
	else
	{
		Output* pOut = pManager->GetOutput();
		pOut->PrintMessage("No Statement selected to Edit");
	}
}