#ifndef SELECT_H
#define SELECT_H

#include "Action.h"
#include "../Statements/Statement.h"

/**
 * @brief Select class for handling the selection of statements or connectors in the flowchart.
 *
 * This class is responsible for:
 * 1. Initializing the action with the ApplicationManager.
 * 2. Reading user input to select a statement or connector.
 * 3. Executing the action to perform the selection or deselection based on user input.
 */
class Select : public Action
{
private:
    Point Position; //!< Position where the user clicks to select a statement or connector

public:
    /**
     * @brief Constructor for the Select class.
     * @param pAppManager Pointer to the ApplicationManager.
     */
    Select(ApplicationManager* pAppManager);

    /**
     * @brief Reads parameters for the action from user input.
     *        Prompts the user to click on the flowchart to select a statement or connector.
     */
    virtual void ReadActionParameters();

    /**
     * @brief Executes the action of selecting or deselecting a statement based on user input.
     *        Reads the position clicked by the user, gets the corresponding statement, and updates the interface accordingly.
     */
    virtual void Execute();
};

#endif // SELECT_H