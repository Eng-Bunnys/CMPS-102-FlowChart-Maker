#include "AddEnd.h"
#include "../ApplicationManager.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"
#include <sstream>
#include "../Actions/Action.h"
#include "../Statements/End.h"

using namespace std;

// Constructor
AddEnd::AddEnd(ApplicationManager* pAppManager) : Action(pAppManager) {}

void AddEnd::ReadActionParameters()

{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	// Read the position where the user clicks
	pOut->PrintMessage("End Statement: Click to add the statement");
	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();
}

void AddEnd::Execute()
{
	ReadActionParameters();

	// Create a new Start statement at the specified position
	End* pEnd = new End(Position);

	// Add the statement to the list of statements
	pManager->AddStatement(pEnd);
}