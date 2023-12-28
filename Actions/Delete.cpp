#include "Delete.h"
#include "../Statements/Statement.h"
#include "../ApplicationManager.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"
#include <sstream>

 /**
  * @brief Constructs a Delete object.
  *
  * @param pManager Pointer to the ApplicationManager.
  */
Delete::Delete(ApplicationManager* pManager)
    : Deleter(pManager)
{
}

/**
 * @brief Reads any action parameters if needed (no action parameters for Delete).
 */
void Delete::ReadActionParameters()
{
    // No action parameters to read
}

/**
 * @brief Executes the Delete action.
 *
 * Checks if a Connector or a Statement is selected and deletes it accordingly.
 * If neither is selected, displays an error message.
 */
void Delete::Execute()
{
    Connector* selectedConnector = pManager->GetSelectedConnector();
    Statement* selectedStatement = pManager->GetSelectedStatement();

    if (selectedConnector != NULL)
    {
        pManager->RemoveConnFromList(selectedConnector);
        DeleteConnector(selectedConnector);
        pManager->SetSelectedConnector(NULL);
        return;
    }
    else if (selectedStatement != NULL)
    {
        // Deleter::Execute will handle the deletion of statements and associated connectors
        Deleter::Execute();
        return;
    }

    Output* pOut = pManager->GetOutput();
    pOut->PrintMessage("Select an item to delete");
}