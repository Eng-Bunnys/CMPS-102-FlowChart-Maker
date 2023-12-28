#include "AddConnector.h"
#include "../Statements/Start.h"
#include "../Statements/End.h"
#include "../Utils.h"

/**
 * @brief Constructor for the AddConnectors class.
 * @param pAppManager Pointer to the ApplicationManager.
 */
AddConnectors::AddConnectors(ApplicationManager* pAppManager) : Action(pAppManager)
{
}

/**
 * @brief Reads action parameters from the user.
 */
void AddConnectors::ReadActionParameters()
{
    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();

    pOut->PrintMessage("Choose the source statement");
    pIn->GetPointClicked(Position);
    SourceStatement = pManager->GetStatement(Position);
    if (SourceStatement)
    {
        if (SourceStatement->GetMaxNumberOfOutputConnectors() == 2)
        {
            // Prompt user for left or right connector
            pOut->PrintMessage("Enter 'L' to add the connector to the left and 'R' to add the connector to the right.");
            string UserInput;
            do
            {
                UserInput = Utils::toLowerCase(pIn->GetString(pOut));
                if (UserInput != "l" && UserInput != "r")
                    pOut->PrintMessage("Invalid input. Enter 'L' to add the connector to the left and 'R' to add the connector to the right.");
            } while (UserInput != "l" && UserInput != "r");
            Case = UserInput == "r" ? 1 : 2;
        }
        else
        {
            Case = 0;
        }
    }
    pOut->ClearStatusBar();
    pOut->PrintMessage("Choose the destination statement");
    pIn->GetPointClicked(Position);
    DestinationStatement = pManager->GetStatement(Position);
}

/**
 * @brief Executes the action to add connectors between statements.
 */
void AddConnectors::Execute()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    ReadActionParameters();
    pOut->ClearStatusBar();

    // Check if both source and destination statements are selected
    if (!SourceStatement || !DestinationStatement)
    {
        pOut->PrintMessage("Please select both source and destination statements before proceeding.");
        return;
    }

    // Check if the source statement already has a connector on the right side
    if (Case == 1 && SourceStatement->GetConnecter(1))
    {
        pOut->PrintMessage("The selected source statement already has an output connector on the right side. Please remove it before creating a new one.");
        return;
    }

    // Check if destination statement can be connected
    if (!DestinationStatement->CanBeConnected())
    {
        pOut->PrintMessage("Start statements cannot be used as destinations. Please select a different destination statement.");
        return;
    }

    // Check if end statements can have outgoing connectors
    if (SourceStatement->GetMaxNumberOfOutputConnectors() == 0)
    {
        pOut->PrintMessage("End statements cannot have outgoing connectors. Please select a different source statement.");
        return;
    }

    // Check for self-connections
    if (SourceStatement == DestinationStatement)
    {
        pOut->PrintMessage("Self-connections are not allowed. Please choose a different destination statement.");
        return;
    }

    // Check if the source statement already has a connector on the left side
    if ((Case == 0 || Case == 2) && SourceStatement->GetConnecter(0))
    {
        pOut->PrintMessage("The selected source statement already has an output connector on the left side. Please remove it before creating a new one.");
        return;
    }

    // Create a new connector and connect the statements
    Connector* NewConnector = new Connector(SourceStatement, DestinationStatement, Case);
    if (Case == 0 || Case == 2)
        SourceStatement->SetConnector(NewConnector);
    else
        SourceStatement->SetConnector(NewConnector, 1);

    DestinationStatement->SetHasIncomingConnectors(true);
    SourceStatement->AddOutputConnector();
    pManager->AddConnector(NewConnector);
}