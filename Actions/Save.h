#ifndef SAVE_H
#define SAVE_H

#include <fstream>
#include "../ApplicationManager.h"
#include "Action.h"

/**
 * @brief The Save class represents an action for saving the current state of the application.
 */
class Save : public Action {
    string FileName; /**< The name of the file to save the state to. */

public:
    /**
     * @brief Constructor for the Save class.
     * @param pAppManager A pointer to the ApplicationManager managing the application.
     */
    Save(ApplicationManager* pAppManager);

    /**
     * @brief Reads the necessary parameters for the Save action.
     * This function prompts the user to enter the file name for saving.
     */
    virtual void ReadActionParameters();

    /**
     * @brief Executes the Save action.
     * This function performs the actual saving of the application's state to the specified file.
     */
    virtual void Execute();
};

#endif