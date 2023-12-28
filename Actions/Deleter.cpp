#include "Deleter.h"
#include "../Statements/Statement.h"
#include "../ApplicationManager.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"
#include <sstream>

/**
 * @brief Constructor for the Deleter class.
 * @param pManager Pointer to the ApplicationManager.
 */
Deleter::Deleter(ApplicationManager* pManager)
    : Action(pManager)
{
}

/**
 * @brief Executes the deletion action.
 * Checks for a selected statement, removes it, and deletes associated connectors.
 */
void Deleter::Execute()
{
    // Get the currently selected statement from the ApplicationManager
    Statement* selectedStatement = pManager->GetSelectedStatement();

    // Check if a statement is selected
    if (selectedStatement == NULL)
    {
        // If no statement is selected, print an error message and return
        Output* pOut = pManager->GetOutput();
        pOut->PrintMessage("Select a statement to be deleted");
        return;
    }

    // Remove the selected statement from the list of statements
    pManager->RemoveStatFromList(selectedStatement);

    // Delete the selected statement and its associated connectors
    DeleteStatement(pManager, selectedStatement);

    // Set the selected statement to NULL after deletion
    pManager->SetSelectedStatement(NULL);
}

/**
 * @brief Deletes a connector and updates source and destination statements.
 * @param connector The connector to be deleted.
 */
void Deleter::DeleteConnector(Connector* connector)
{
    // Get source and destination statements of the connector
    Statement* source = connector->getSrcStat();
    Statement* destination = connector->getDstStat();

    // Remove the connector from the source statement
    if (source->GetMaxNumberOfOutputConnectors() == 1)
    {
        source->RemoveConnector();
    }
    else
    {
        // If there are multiple connectors, determine the index and remove
        const int connectorIndex = (connector == source->GetConnecter(0)) ? 0 : 1;
        source->RemoveConnector(connectorIndex);
    }

    // Check if there is a connector to the destination statement
    Connector* connectorToDestination = pManager->GetConnectorToStat(destination);
    if (connectorToDestination == NULL)
    {
        // If no connector to destination, update the destination statement
        destination->SetHasIncomingConnectors(false);
    }

    // Decrement the output connectors count of the source statement
    source->DecrementOutputConnectors();

    // Delete the connector
    delete connector;
}

/**
 * @brief Deletes a statement and its associated connectors.
 * @param pManager Pointer to the ApplicationManager.
 * @param statement The statement to be deleted.
 */
void Deleter::DeleteStatement(ApplicationManager* pManager, Statement* statement)
{
    // Get the maximum number of output connectors for the statement
    const int maxConnectors = statement->GetMaxNumberOfOutputConnectors();

    // Check the number of output connectors and perform deletion accordingly
    if (maxConnectors == 2)
    {
        // If there are two connectors, get and delete both
        Connector* leftConnector = statement->GetConnecter(0);
        Connector* rightConnector = statement->GetConnecter(1);

        if (leftConnector != NULL)
        {
            // Remove and delete the left connector
            pManager->RemoveConnFromList(leftConnector);
            DeleteConnector(leftConnector);
        }

        if (rightConnector != NULL)
        {
            // Remove and delete the right connector
            pManager->RemoveConnFromList(rightConnector);
            DeleteConnector(rightConnector);
        }
    }
    else if (maxConnectors == 1)
    {
        // If there is one connector, get and delete it
        Connector* outputConnector = statement->GetConnecter();

        if (outputConnector != NULL)
        {
            // Remove and delete the output connector
            pManager->RemoveConnFromList(outputConnector);
        }
    }

    // Check if the statement can be connected and has incoming connectors
    if (statement->CanBeConnected() && statement->GetHasIncomingConnectors())
    {
        // If true, get and delete all incoming connectors
        Connector* inputConnector = pManager->GetConnectorToStat(statement);

        while (inputConnector != NULL)
        {
            // Remove and delete each incoming connector
            pManager->RemoveConnFromList(inputConnector);
            DeleteConnector(inputConnector);
            inputConnector = pManager->GetConnectorToStat(statement);
        }
    }

    // Remove the statement from the list of statements
    pManager->RemoveStatFromList(statement);
}