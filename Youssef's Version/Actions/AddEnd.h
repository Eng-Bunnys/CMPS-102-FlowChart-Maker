#ifndef ADD_END_H
#define ADD_END_H

#include "Action.h"
#include "../Statements/Statement.h"

/**
 * @brief AddEnd class for adding End statements to the flowchart.
 *
 * This class is responsible for:
 * 1. Getting End statement coordinates from the user.
 * 2. Creating an object of the End class.
 * 3. Adding the created object to the list of statements in the application manager.
 */
class AddEnd : public Action
{
private:
    // Position where the user clicks to add the statement
    Point Position;

public:
    /**
     * @brief Constructor for AddEnd.
     * @param pAppManager Pointer to the ApplicationManager.
     */
    AddEnd(ApplicationManager* pAppManager);

    /**
     * @brief Reads the End statement position from user input.
     *        Prompts the user to click on the flowchart to place the End statement.
     */
    virtual void ReadActionParameters();

    /**
     * @brief Executes the action of adding an End statement to the flowchart.
     *        Creates a new End statement at the specified position and adds it to the list of statements.
     */
    virtual void Execute();
};

#endif