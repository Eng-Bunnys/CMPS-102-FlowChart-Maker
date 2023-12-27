#ifndef ADD_WRITE_H
#define ADD_WRITE_H

#include "Action.h"
#include "../Statements/Write.h"

/**
 * @brief AddWrite class represents an action for adding a Write statement.
 *
 * This class is responsible for:
 *  1. Getting Write statement coordinates from the user (one of the parameters of this action).
 *  2. Getting the variable or message to be written from the user (a parameter of this action).
 *  3. Creating an object of the Write class and passing it parameters.
 *  4. Adding the created object to the list of statements of the application manager.
 */
class AddWrite : public Action
{
private:
    // In the data members of the actions,
    // we put the parameters of the action
    // to be set in ReadActionParameters() then used in Execute()

    Point Position; // Position where the user clicks to add the statement.
    string Variable;
public:
    /**
     * @brief Constructs an AddWrite object with the given ApplicationManager.
     *
     * @param pAppManager Pointer to the ApplicationManager.
     */
    AddWrite(ApplicationManager* pAppManager);

    /**
     * @brief Reads parameters required for adding a Write statement.
     *
     * This function prompts the user to click on the drawing area to
     * add the Write statement, asks for the variable or message to be written,
     * and validates the input.
     */
    virtual void ReadActionParameters();

    /**
     * @brief Executes the action of adding a Write statement.
     *
     * This function creates a new Write statement, sets its attributes
     * based on the parameters obtained in ReadActionParameters(), and
     * adds the statement to the ApplicationManager's statement list.
     */
    virtual void Execute();

};

#endif