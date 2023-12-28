#include "Save.h"

#include "../GUI/Input.h"
#include "../GUI/Output.h"

#include <sstream>
using namespace std;

/**
 * @brief Constructor for the Save class.
 * @param pAppManager A pointer to the ApplicationManager managing the application.
 */
Save::Save(ApplicationManager* pAppManager) : Action(pAppManager)
{}

/**
 * @brief Reads the necessary parameters for the Save action.
 * This function prompts the user to enter the file name for saving.
 */
void Save::ReadActionParameters()
{
    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();

    // Read the (Position) parameter
    pOut->PrintMessage("Enter the file's name");
    FileName = pIn->GetString(pOut);

    // npos pretty much ends of string
    if (FileName.find(".txt") == string::npos)  FileName += ".txt";
}

/**
 * @brief Executes the Save action.
 * This function performs the actual saving of the application's state to the specified file.
 */
void Save::Execute()
{
    ReadActionParameters();
    ofstream OutputFile;
    OutputFile.open(FileName, ios::out);
    pManager->SaveAll(OutputFile);
    OutputFile.close();
    pManager->GetOutput()->PrintMessage("Successfully saved " + FileName);
}