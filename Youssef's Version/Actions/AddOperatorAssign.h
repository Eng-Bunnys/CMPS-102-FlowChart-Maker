#ifndef ADD_OPERATOR_ASSIGN_H
#define ADD_OPERATOR_ASSIGN_H

#include "Action.h"
#include "../Statements/OperatorAssign.h"

/**
 * @brief AddOperatorAssign class for adding Operator Assignment statements to the flowchart.
 *
 * This class is responsible for:
 * 1. Getting Operator Assignment statement coordinates and parameters from the user.
 * 2. Creating an object of OperatorAssign class.
 * 3. Adding the created object to the list of statements in the application manager.
 */
class AddOperatorAssign : public Action
{
private:
    Point Position;   // Position where the user clicks to add the statement
    string LHS;       // Left-hand side of the assignment statement
    string RHSFirst;  // First input (value or variable)
    string Operator;  // Operator
    string RHSSecond; // Second input (value or variable)

public:
    /**
     * @brief Constructor for AddOperatorAssign.
     * @param pAppManager Pointer to the ApplicationManager.
     */
    AddOperatorAssign(ApplicationManager* pAppManager);

    /**
     * @brief Reads OperatorAssign statement position and parameters from user input.
     *        Prompts the user to click on the flowchart to place the statement and enter relevant information.
     */
    virtual void ReadActionParameters();

    /**
     * @brief Executes the action of adding an OperatorAssign statement to the flowchart.
     *        Creates a new OperatorAssign statement at the specified position and adds it to the list of statements.
     */
    virtual void Execute();
};

#endif