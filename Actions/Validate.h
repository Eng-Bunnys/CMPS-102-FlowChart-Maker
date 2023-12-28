#ifndef VALIDATE_H
#define VALIDATE_H

#include "../ApplicationManager.h"
#include "Action.h"

/**
 * @brief The Validate class is responsible for validating the flowchart.
 * It checks for various conditions such as the presence of Start and End statements,
 * correct connector count, proper connections, and valid values in statements.
 */
class Validate : public Action
{
private:
    bool IsValidBool; /**< Indicates whether the flowchart is valid or not. */

public:
    /**
     * @brief Constructor for the Validate class.
     * @param ApM Pointer to the ApplicationManager.
     */
    Validate(ApplicationManager *ApM);

    /**
     * @brief Reads any necessary parameters for the Validate action.
     */
    virtual void ReadActionParameters();

    /**
     * @brief Executes the validation process.
     */
    virtual void Execute();

    /**
     * @brief Checks the presence of a Start statement in the flowchart.
     * @return True if a Start statement is found, false otherwise.
     */
    bool CheckStart();

    /**
     * @brief Checks the presence of an End statement in the flowchart.
     * @return True if an End statement is found, false otherwise.
     */
    bool CheckEnd();

    /**
     * @brief Checks the count of connectors in the flowchart.
     * @return True if the connector count is valid, false otherwise.
     */
    bool CheckConnectorCount();

    /**
     * @brief Checks the connections between statements in the flowchart.
     * @return True if connections are valid, false otherwise.
     */
    bool CheckConnections();

    /**
     * @brief Checks the values in statements for validity.
     * @param pStat Pointer to a Statement.
     * @param c Counter variable for recursive calls (default is 0).
     * @param arr Pointer to a string array for storing values (default is NULL).
     * @return True if values are valid, false otherwise.
     */
    bool CheckValues(Statement *pStat, int c = 0, string *arr = NULL);

    /**
     * @brief Gets the validity status of the flowchart.
     * @return True if the flowchart is valid, false otherwise.
     */
    bool IsValid();
};

#endif // VALIDATE_H
