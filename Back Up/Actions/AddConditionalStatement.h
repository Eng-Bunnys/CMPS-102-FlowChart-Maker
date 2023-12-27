#ifndef ADD_CONDITIONAL_H
#define ADD_CONDITIONAL_H

#include "../Statements/ConditionalStatement.h"
#include "../ApplicationManager.h"
#include "Action.h"

/**
 * @brief AddConditional class.
 *
 * This class is responsible for:
 * 1. Getting Conditional statement coordinates from the user (one of the parameters of this action).
 * 2. Getting the LHS and RHS of the statement from the user (some of the parameters of this action).
 * 3. Creating an object of Conditional class and passing it parameters.
 * 4. Adding the created object to the list of statements of the application manager.
 */
class AddConditional : public Action
{
private:
    Point Position; // Position where the user clicks to add the statement.
    //TODO: you should add LHS and RHS of the conditional statement as parameters
    string LHS;
    string ComparisonOperator;
    string RHS;

public:
    /**
     * @brief Constructor for AddConditional class.
     * @param pAppManager Pointer to the ApplicationManager.
     */
    AddConditional(ApplicationManager* pAppManager);

    /**
     * @brief Read conditional statement parameters from the user.
     */
    virtual void ReadActionParameters();

    /**
     * @brief Execute the action to add a conditional statement.
     */
    virtual void Execute();

};

#endif