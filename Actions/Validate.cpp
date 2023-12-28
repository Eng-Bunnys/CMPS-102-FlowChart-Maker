#include "Validate.h"

#include "../GUI/Input.h"
#include "../GUI/Output.h"
#include <sstream>
using namespace std;

Validate::Validate(ApplicationManager *ApM)
    : Action(ApM)
{
    IsValidBool = true;
}

/**
 * @brief Empty implementation for ReadActionParameters.
 * This function does not require any user input parameters.
 */
void Validate::ReadActionParameters()
{
    // Empty implementation as there are no action parameters to read.
}

/**
 * @brief Executes the Validate action.
 * Checks the validity of the flowchart based on specific criteria.
 */
void Validate::Execute()
{
    Input *pIn = pManager->GetInput();
    Output *pOut = pManager->GetOutput();

    // Check various aspects of the flowchart for validity
    if (CheckStart() && CheckEnd() && CheckConnectorCount())
    {
        Statement *startStatement = pManager->GetStart();
        Statement *endStatement = (startStatement->GetConnecter())->getDstStat();

        // Initialize an array to store variable values
        string *valuesArray = new string[1];
        int variableCount = 0;

        // Check values recursively
        IsValidBool = CheckValues(endStatement, variableCount, valuesArray);

        delete[] valuesArray;

        // Display validation result
        pOut->PrintMessage(IsValidBool ? "The flowchart is valid" : "The flowchart is invalid");
    }
    else
    {
        IsValidBool = false;
        pOut->PrintMessage("The flowchart is invalid");
    }
}

/**
 * @brief Checks if there is exactly one start statement in the flowchart.
 * @return True if there is exactly one start statement, false otherwise.
 */
bool Validate::CheckStart()
{
    Statement **statementArray = pManager->getStatList();
    int startCount = 0; // Count number of start statements

    // Loop through all statements to find start statements
    for (int i = 0; i < pManager->GetStatCount(); ++i)
    {
        // Check if the statement cannot be connected, indicating a start statement
        if (!statementArray[i]->CanBeConnected())
        {
            ++startCount;

            // Early return if more than one start statement is found
            if (startCount > 1)
                return false;
        }
    }

    // Return true only if exactly one start statement is found
    return (startCount == 1);
}

/**
 * @brief Checks if there is exactly one end statement in the flowchart.
 * @return True if there is exactly one end statement, false otherwise.
 */
bool Validate::CheckEnd()
{
    Statement **statementArray = pManager->getStatList();
    int endCount = 0; // Count number of end statements

    // Loop through all statements to find end statements
    for (int i = 0; i < pManager->GetStatCount(); ++i)
    {
        // Check if the statement has no output connectors, indicating an end statement
        if (statementArray[i]->GetMaxNumberOfOutputConnectors() == 0)
        {
            ++endCount;

            // Early return if more than one end statement is found
            if (endCount > 1)
                return false;
        }
    }

    // Return true only if exactly one end statement is found
    return (endCount == 1);
}

/**
 * @brief Checks if the flowchart is fully connected by comparing the sum of possible connectors with the actual connector count.
 * @return True if the flowchart is fully connected, false otherwise.
 */
bool Validate::CheckConnectorCount()
{
    Statement **statementArray = pManager->getStatList();
    int sumOfConnectors = 0; // Sum of possible connectors

    // Loop through all statements to calculate the sum of possible connectors
    for (int i = 0; i < pManager->GetStatCount(); i++)
    {
        // Accumulate the maximum number of output connectors for each statement
        sumOfConnectors += statementArray[i]->GetMaxNumberOfOutputConnectors();
    }

    // Return true only if the sum of possible connectors matches the actual connector count
    return (sumOfConnectors == pManager->GetConnCount());
}

/**
 * @brief Checks if the connections in the flowchart meet specific criteria.
 * @return True if all connection criteria are met, false otherwise.
 */
bool Validate::CheckConnections()
{
    Statement **statementArray = pManager->getStatList();
    int statementCount = pManager->GetStatCount();

    // Loop through all statements to check connection criteria
    for (int i = 0; i < statementCount; i++)
    {
        if (!statementArray[i]->CanBeConnected())
        {
            // Check if a non-connectable statement has exactly one drawn connector
            if (statementArray[i]->GetDrawnConnectors() != 1)
                return false;
        }
        else
        {
            // Check if a connectable statement has incoming connectors
            if (!statementArray[i]->GetHasIncomingConnectors())
                return false;

            // Check if the number of drawn connectors matches the maximum possible
            int maxConnectors = statementArray[i]->GetMaxNumberOfOutputConnectors();
            if (statementArray[i]->GetDrawnConnectors() != maxConnectors)
                return false;
        }
    }

    // Return true only if all conditions are met
    return true;
}

/**
 * @brief Recursive function to check the values in the flowchart.
 * @param currentStatement The current statement to check.
 * @param variableCount The count of variables.
 * @param variableArray The array of variables.
 * @return True if the values in the flowchart meet specific criteria, false otherwise.
 */
bool Validate::CheckValues(Statement *currentStatement, int variableCount, string *variableArray)
{
    if (currentStatement == NULL)
        return false;

    if (currentStatement->GetMaxNumberOfOutputConnectors() == 0)
    {
        delete[] variableArray;
        return true;
    }

    if (currentStatement->CheckVariables(variableArray, variableCount))
    {
        if (currentStatement->GetMaxNumberOfOutputConnectors() == 1)
        {
            Statement *nextStatement = currentStatement->GetConnecter()->getDstStat();
            return CheckValues(nextStatement, variableCount, variableArray);
        }
        else if (currentStatement->GetMaxNumberOfOutputConnectors() == 2)
        {
            Statement *leftChild = currentStatement->GetConnecter()->getDstStat();
            Statement *rightChild = currentStatement->GetConnecter(1)->getDstStat();

            // Copy array elements for leftChild and rightChild
            string *leftArrayCopy = new string[variableCount];
            string *rightArrayCopy = new string[variableCount];
            for (int i = 0; i < variableCount; ++i)
            {
                leftArrayCopy[i] = rightArrayCopy[i] = variableArray[i];
            }

            // Delete the original array
            delete[] variableArray;

            // Check values for leftChild and rightChild
            if (!CheckValues(leftChild, variableCount, leftArrayCopy) || !CheckValues(rightChild, variableCount, rightArrayCopy))
            {
                delete[] leftArrayCopy;
                delete[] rightArrayCopy;
                return false;
            }
        }
    }
    else
    {
        return false;
    }

    return true;
}

/**
 * @brief Getter for the validity status of the flowchart.
 * @return True if the flowchart is valid, false otherwise.
 */
bool Validate::IsValid()
{
    return IsValidBool;
}