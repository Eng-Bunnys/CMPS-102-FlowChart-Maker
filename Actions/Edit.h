#include "Action.h"
#include "../ApplicationManager.h"

/**
 * @brief The Edit class represents an editing action.
 *
 * This class is derived from the Action class and provides
 * functionality for editing in the application.
 */
class Edit : public Action
{
public:
    /**
     * @brief Constructs an Edit object with the given ApplicationManager.
     *
     * @param pManager Pointer to the ApplicationManager.
     */
    Edit(ApplicationManager* pManager);

    /**
     * @brief Reads parameters required for the action to execute.
     *
     * This function is responsible for reading any necessary parameters
     * from the user or other sources to prepare for the execution of the action.
     */
    virtual void ReadActionParameters();

    /**
     * @brief Executes the edit action.
     *
     * The code for the execution of the edit action depends on the specific
     * type of edit being performed.
     */
    virtual void Execute();
};