#ifndef ADD_START_H
#define ADD_START_H

#include "Action.h"
#include "../Statements/Statement.h"

/**
 * @brief AddStart class for adding Start statements to the flowchart.
 *
 * This class is responsible for:
 * 1. Getting Start statement coordinates from the user.
 * 2. Creating an object of the Start class.
 * 3. Adding the created object to the list of statements in the application manager.
 */
class AddStart : public Action
{
private:
    // Position where the user clicks to add the statement
    Point Position;

public:
    /**
     * @brief Constructor for AddStart.
     * @param pAppManager Pointer to the ApplicationManager.
     */
    AddStart(ApplicationManager* pAppManager);

    /**
     * @brief Reads Start statement position from user input.
     *        Prompts the user to click on the flowchart to place the Start statement.
     */
    virtual void ReadActionParameters();

    /**
     * @brief Executes the action of adding a Start statement to the flowchart.
     *        Creates a new Start statement at the specified position and adds it to the list of statements.
     */
    virtual void Execute();
};

#endif