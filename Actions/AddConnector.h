#ifndef ADD_CONNECTORS_H
#define ADD_CONNECTORS_H
#include "../ApplicationManager.h"
#include "Action.h"

class AddConnectors :public Action {
	Point Position;
	Statement* SourceStatement;
	Statement* DestinationStatement;
	int Case;
public:
	AddConnectors(ApplicationManager* pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();
};
#endif