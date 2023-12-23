#include "AddStart.h"
#include "../ApplicationManager.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"
#include <sstream>
#include "../Actions/Action.h"
#include "../Statements/Start.h"

using namespace std;

// Constructor
AddStart::AddStart(ApplicationManager *pAppManager) : Action(pAppManager) {}

void AddStart::ReadActionParameters()

{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	// Read the position where the user clicks
	pOut->PrintMessage("Start Statement: Click to add the statement");
	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();
}

void AddStart::Execute()
{
	ReadActionParameters();

	// Create a new Start statement at the specified position
	Start *pStart = new Start(Position);

	// Add the statement to the list of statements
	pManager->AddStatement(pStart);
}