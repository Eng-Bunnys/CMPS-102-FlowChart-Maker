#ifndef ADD_VALUE_ASSIGN_H
#define ADD_VALUE_ASSIGN_H

#include "Action.h"
#include "..\Statements\ValueAssign.h"

// Add Value Assignment Statement Action
// This class is responsible for
// 1 - Getting Assignment stat. coordinates from the user (one of the parameters of this action)
// 2 - Getting the LHS and RHS of the statement from the user (some of the parameters of this action)
// 3 - Creating an object of Assignment class and passing it parameters
// 4 - Adding the created object to the list of statements of the application manager
class AddValueAssign : public Action
{
private:
    // in the data members of the actions
    // we put the parameters of the action
    // to be set in ReadActionParameters() then used in Execute()

    Point Position; // Position where the user clicks to add the stat.
    string LHS;     // Left-hand side of the assignment statement
    double RHS;     // Right-hand side of the assignment statement

public:
    AddValueAssign(ApplicationManager *pAppManager);

    // Read Assignment statements position and parameters
    virtual void ReadActionParameters();

    // Create and add an assignment statement to the list of statements
    virtual void Execute();
};

#endif