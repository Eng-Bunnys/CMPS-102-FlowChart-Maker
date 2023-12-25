#include "ApplicationManager.h"
#include "Actions\AddValueAssign.h"
#include "GUI\Input.h"
#include "GUI\Output.h"
#include "Actions/AddStart.h"
#include "Actions/AddEnd.h"
#include "Actions/AddVariableAssign.h"
#include "Actions/AddOperatorAssign.h"
#include "Actions/AddConditionalStatement.h"
#include "Actions/Select.h"
#include "Actions/Copy.h"
#include "Actions/Paste.h"

#include "Statements/Start.h"
#include "Statements/End.h"
#include "Statements/VariableAssign.h"
#include "Statements/ValueAssign.h"
#include "Statements/OperatorAssign.h"
#include "Statements/ConditionalStatement.h"

// Constructor
ApplicationManager::ApplicationManager()
{
	// Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();

	StatCount = 0;
	ConnCount = 0;
	pSelectedStat = NULL; // no Statement is selected yet
	pClipboard = NULL;

	// Create an array of Statement pointers and set them to NULL
	for (int i = 0; i < MaxCount; i++)
	{
		StatList[i] = NULL;
		ConnList[i] = NULL;
	}
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//

ActionType ApplicationManager::GetUserAction() const
{
	// Ask the input to get the action from the user.
	return pIn->GetUserAction();
}
////////////////////////////////////////////////////////////////////////////////////
// Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action* pAct = NULL;

	// According to ActioType, create the corresponding action object
	switch (ActType)
	{
	case ADD_VALUE_ASSIGN:
		pAct = new AddValueAssign(this);
		break;

	case ADD_VAR_ASSIGN:
		pAct = new AddVariableAssign(this);
		break;

	case ADD_OPER_ASSIGN:
		pAct = new AddOperatorAssign(this);
		break;

	case ADD_CONDITION:
		pAct = new AddConditionalStatement(this);
		break;

	case ADD_START:
		pAct = new AddStart(this);
		break;

	case ADD_END:
		pAct = new AddEnd(this);
		break;

	case SELECT:
		pAct = new Select(this);
		break;

	case COPY:
		pAct = new Copy(this);
		break;

	case PASTE:
		pAct = new Paste(this);
		break;

	case EXIT:
		/// create Exit Action here
		break;

	case STATUS:
		return;
	}

	// Execute the created action
	if (pAct != NULL)
	{
		pAct->Execute(); // Execute
		delete pAct;	 // Action is not needed any more ==> delete it
	}
}

//==================================================================================//
// Statements/Connector Management Functions
//==================================================================================//

void ApplicationManager::AddSelected(Statement* pStat) {
	for (int i = 0; i < MaxCount; ++i) {
		if (!SelectedStatements[i]) {
			SelectedStatements[i] = pStat;
			break;
		}
	}
}

void ApplicationManager::RemoveSelected(Statement* pStat) {
	for (int i = 0; i < MaxCount; ++i) {
		if (SelectedStatements[i] == pStat) {
			SelectedStatements[i] = nullptr;
			break;
		}
	}
}

void ApplicationManager::EmptySelectedList() {
	for (int i = 0; i < MaxCount; ++i) {
		SelectedStatements[i] = nullptr;
	}
}

void ApplicationManager::UpdateSelectedInterface() const {
	// You can implement this function based on your requirements
	// For example, you can highlight the selected statements in a different color
	for (int i = 0; i < MaxCount; ++i) {
		if (SelectedStatements[i]) {
			SelectedStatements[i]->Draw(pOut); // Use a different color or any other indication for selected statements
		}
	}
}

void ApplicationManager::AddStatement(Statement* pStat)
{
	if (StatCount < MaxCount)
		StatList[StatCount++] = pStat;
}

Statement* ApplicationManager::GetStatement(Point P) const
{
	//If this point P(x,y) belongs to a statement return a pointer to it.
	//otherwise, return NULL
	//Note:Add another test here to check whether you're inside the drawing area

	for (int i = 0; i < StatCount; i++) {

		Start* TestStart = dynamic_cast<Start*>(StatList[i]);
		if (TestStart) {
			if (TestStart->ContainsPoint(P)) {
				return StatList[i];
			}
			else {
				continue;
			}
		}

		End* TestEnd = dynamic_cast<End*>(StatList[i]);
		if (TestEnd) {
			if (TestEnd->ContainsPoint(P)) {
				return StatList[i];
			}
			else {
				continue;
			}
		}

		ValueAssign* TestValue = dynamic_cast<ValueAssign*>(StatList[i]);
		if (TestValue) {
			if (TestValue->ContainsPoint(P)) {
				return StatList[i];
			}
			else {
				continue;
			}
		}
		VariableAssign* TestVariable = dynamic_cast<VariableAssign*>(StatList[i]);
		if (TestVariable) {
			if (TestVariable->ContainsPoint(P)) {
				return StatList[i];
			}
			else {
				continue;
			}
		}
		OperatorAssign* TestOperator = dynamic_cast<OperatorAssign*>(StatList[i]);
		if (TestOperator) {
			if (TestOperator->ContainsPoint(P)) {
				return StatList[i];
			}
			else {
				continue;
			}
		}

		ConditionalStatement* TestConditional = dynamic_cast<ConditionalStatement*>(StatList[i]);
		if (TestConditional) {
			if (TestConditional->ContainsPoint(P)) {
				return StatList[i];
			}
			else {
				continue;
			}
		}
	}
	
	return NULL;
}

void ApplicationManager::AddConnector(Connector* pConn)
{
	if (ConnCount < MaxCount)
		ConnList[ConnCount++] = pConn;
}

Connector* ApplicationManager::GetConnector(Point P) const
{
	// TODO: Implement the logic to search for a connector given a point P(x, y)
	// WITHOUT breaking class responsibilities
	return NULL;
}

Statement* ApplicationManager::GetSelectedStatement() const
{
	return pSelectedStat;
}

void ApplicationManager::SetSelectedStatement(Statement* pStat)
{
	pSelectedStat = pStat;
}

Statement* ApplicationManager::GetClipboard() const
{
	return pClipboard;
}

void ApplicationManager::SetClipboard(Statement* pStat)
{
	pClipboard = pStat;
}

//==================================================================================//
// Interface Management Functions
//==================================================================================//

Input* ApplicationManager::GetInput() const
{
	return pIn;
}

Output* ApplicationManager::GetOutput() const
{
	return pOut;
}

void ApplicationManager::UpdateInterface() const
{
	pOut->ClearDrawArea();

	// Draw all statements
	for (int i = 0; i < StatCount; i++)
		StatList[i]->Draw(pOut);

	// Draw all connections
	for (int i = 0; i < ConnCount; i++)
		ConnList[i]->Draw(pOut);
}

//==================================================================================//
// Destructor
//==================================================================================//

ApplicationManager::~ApplicationManager()
{
	for (int i = 0; i < StatCount; i++)
		delete StatList[i];

	for (int i = 0; i < ConnCount; i++)
		delete ConnList[i];

	delete pIn;
	delete pOut;
}