#include "Load.h"
#include "../Statements/Connector.h"
#include "../Statements/ConditionalStatement.h"
#include "../Statements/Start.h"
#include "../Statements/End.h"
#include "../Statements/VariableAssign.h"
#include "../Statements/ValueAssign.h"
#include "../Statements/Read.h"
#include "../Statements/Write.h"
#include "../GUI/Input.h"
#include <sstream>

/**
 * @brief Constructor for the Load class.
 * @param appManager Pointer to the ApplicationManager.
 */
Load::Load(ApplicationManager* appManager) : Action(appManager) {}

/**
 * @brief Reads action parameters from the user.
 * Uses the input and output objects of the ApplicationManager.
 */
void Load::ReadActionParameters() {
    Input* input = pManager->GetInput();
    Output* output = pManager->GetOutput();

    // Prompt the user to enter a file name
    output->PrintMessage("Enter File Name");
    FileName = input->GetString(output);
    output->ClearStatusBar();
}

/**
 * @brief Executes the Load action.
 * Reads statements and connectors from a file and loads them into the application.
 */
void Load::Execute() {
    // Read parameters from the user
    ReadActionParameters();

    // Open the input file
    ifstream inputFile(FileName, ios::in);

    if (inputFile.is_open()) {
        Output* output = pManager->GetOutput();
        output->ClearDrawArea();
        pManager->EmptyAllLists();

        // Read the number of statements
        int statementCount;
        inputFile >> statementCount;

        // Loop through each statement in the file
        for (int i = 0; i < statementCount; i++) {
            string statementType;
            inputFile >> statementType;
            Point position;

            Statement* newStatement = 0; // Equivalent to NULL

            // Create a new statement based on its type
            if (statementType == "START") {
                newStatement = new Start(position);
            }
            // Add more conditions for other statement types...

            // Load statement data from the file
            if (newStatement) {
                newStatement->Load(inputFile);
                pManager->AddStatement(newStatement);
            }
        }

        // Read the number of connectors
        int connectorCount;
        inputFile >> connectorCount;

        // Loop through each connector in the file
        for (int i = 0; i < connectorCount; i++) {
            int srcID, dstID;
            // I had to re-name it to ConnectorVar cuz Connector would cause issues in the line below :/
            Connector* ConnectorVar = new Connector(0, 0, 0); // Equivalent to NULL

            // Load connector data from the file
            ConnectorVar->Load(inputFile, srcID, dstID);

            // Get source and destination statements
            Statement* SourceStatement = pManager->GetStatementFromID(srcID);
            Statement* DestinationStatement = pManager->GetStatementFromID(dstID);

            // Check if statements exist
            if (SourceStatement && DestinationStatement) {
                // Set connector properties
                ConnectorVar->setSrcStat(SourceStatement);
                ConnectorVar->setDstStat(DestinationStatement);
                ConnectorVar->setStartAndEnd();

                // Connect statements with the connector
                if (ConnectorVar->getDstStat() && ConnectorVar->getSrcStat()) {
                    if (ConnectorVar->getCase() == 0 || ConnectorVar->getCase() == 2) {
                        ConnectorVar->getSrcStat()->SetConnector(ConnectorVar);
                    }
                    else {
                        ConnectorVar->getSrcStat()->SetConnector(ConnectorVar, 1);
                    }

                    ConnectorVar->getDstStat()->SetHasIncomingConnectors(true);
                    ConnectorVar->getSrcStat()->AddOutputConnector();
                    pManager->AddConnector(ConnectorVar);
                }
            }
            else {
                delete ConnectorVar;
            }
        }
    }
}