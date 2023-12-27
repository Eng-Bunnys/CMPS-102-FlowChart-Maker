#ifndef ADD_VARIABLE_ASSIGN_H
#define ADD_VARIABLE_ASSIGN_H

#include "Action.h"
#include "../Statements/VariableAssign.h"

/**
 * @brief AddVariableAssign class for adding Variable Assignment statements to the flowchart.
 *
 * This class is responsible for:
 * 1. Getting Assignment statement coordinates from the user.
 * 2. Getting the LHS and RHS of the statement from the user.
 * 3. Creating an object of VariableAssign class and passing it parameters.
 * 4. Adding the created object to the list of statements in the application manager.
 */
class AddVariableAssign : public Action
{
private:
    Point Position; // Position where the user clicks to add the statement
    string LHS;     // Left-hand side of the assignment statement
    string RHS;     // Right-hand side of the assignment statement

public:
    /**
     * @brief Constructor for AddVariableAssign.
     * @param pAppManager Pointer to the ApplicationManager.
     */
    AddVariableAssign(ApplicationManager* pAppManager);

    /**
     * @brief Reads Assignment statement position and parameters from user input.
     *        Prompts the user to click on the flowchart to place the statement and enter relevant information.
     */
    virtual void ReadActionParameters();

    /**
     * @brief Executes the action of adding a Variable Assignment statement to the flowchart.
     *        Creates a new VariableAssign statement at the specified position and adds it to the list of statements.
     */
    virtual void Execute();
};

#endif