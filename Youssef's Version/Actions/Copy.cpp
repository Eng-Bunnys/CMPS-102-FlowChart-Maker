#include "Copy.h"
#include "../ApplicationManager.h"
#include "../Statements/Statement.h" 

Copy::Copy(ApplicationManager* appManager) : Action(appManager)
{
}

void Copy::ReadActionParameters() {}

void Copy::Execute()
{
	Statement* TargetStatement = pManager->GetSelectedStatement();

	if (TargetStatement != NULL)
	{
		Statement* CopiedStatement = TargetStatement->CopyStatement();
		Statement* Clipboard = pManager->GetClipboard();
		if (Clipboard != NULL) delete Clipboard;
		pManager->SetClipboard(CopiedStatement);
		pManager->SetSelectedStatement(NULL);
		TargetStatement->SetSelected(false);
		pManager->GetOutput()->PrintMessage("Success!");
	}
	else
	{
		pManager->GetOutput()->PrintMessage("You need to select a statement to copy first!");
	}
}