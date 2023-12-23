#ifndef ADD_START_H
#define ADD_START_H

#include "Action.h"
#include "../Statements/Statement.h"

// Add Start Statement Action
// This class is responsible for
// 1 - Getting Start statement coordinates from the user
// 2 - Creating an object of Start class
// 3 - Adding the created object to the list of statements of the application manager
class AddStart : public Action
{
private:
    // Position where the user clicks to add the statement
    Point Position;

public:
    AddStart(ApplicationManager *pAppManager);

    // Read Start statement position
    virtual void ReadActionParameters();

    // Create and add a Start statement to the list of statements
    virtual void Execute();
};

#endif