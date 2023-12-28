#ifndef LOAD_H
#define LOAD_H

#include "../ApplicationManager.h"
#include "Action.h"
#include <fstream>

/**
 * @brief The Load class represents an action for loading the application state from a file.
 */
class Load : public Action
{
    string FileName; /**< The name of the file to load the state from. */

public:
    /**
     * @brief Constructor for the Load class.
     * @param pAppManager A pointer to the ApplicationManager managing the application.
     */
    Load(ApplicationManager *pAppManager);

    /**
     * @brief Reads the necessary parameters for the Load action.
     * This function prompts the user to enter the file name for loading.
     */
    virtual void ReadActionParameters();

    /**
     * @brief Executes the Load action.
     * This function performs the actual loading of the application's state from the specified file.
     */
    virtual void Execute();
};

#endif