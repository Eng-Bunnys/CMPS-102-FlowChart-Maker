#include "Paste.h"
#include "../ApplicationManager.h"
#include "../Statements/Statement.h" 

Paste::Paste(ApplicationManager* appManager) : Action(appManager)
{
}

void Paste::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("Click anywhere to Paste the Statement");
	pIn->GetPointClicked(Position);

}

void Paste::Execute()
{
	if (pManager->GetClipboard())
	{
		ReadActionParameters();
		Statement* CopiedItem = (pManager->GetClipboard())->MakeCopy();
		CopiedItem->SetDrawingPoint(Position);
		pManager->AddStatement(CopiedItem);
	}
	else
	{
		Output* pOut = pManager->GetOutput();
		pOut->PrintMessage("No Statement in clipboard to paste ");
	}
}