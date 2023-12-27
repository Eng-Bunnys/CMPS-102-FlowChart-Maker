#ifndef ADD_VALUE_ASSIGN_H
#define ADD_VALUE_ASSIGN_H

#include "Action.h"
#include "../Statements/ValueAssign.h"

/**
 * @brief AddValueAssign class for adding Value Assignment statements to the flowchart.
 *
 * This class is responsible for:
 * 1. Getting Assignment statement coordinates from the user.
 * 2. Getting the LHS and RHS of the statement from the user.
 * 3. Creating an object of ValueAssign class and passing it parameters.
 * 4. Adding the created object to the list of statements in the application manager.
 */
class AddValueAssign : public Action
{
private:
    Point Position; // Position where the user clicks to add the statement
    string LHS;     // Left-hand side of the assignment statement
    double RHS;     // Right-hand side of the assignment statement

public:
    /**
     * @brief Constructor for AddValueAssign.
     * @param pAppManager Pointer to the ApplicationManager.
     */
    AddValueAssign(ApplicationManager* pAppManager);

    /**
     * @brief Reads Assignment statement position and parameters from user input.
     *        Prompts the user to click on the flowchart to place the statement and enter relevant information.
     */
    virtual void ReadActionParameters();

    /**
     * @brief Executes the action of adding a Value Assignment statement to the flowchart.
     *        Creates a new ValueAssign statement at the specified position and adds it to the list of statements.
     */
    virtual void Execute();
};

#endif