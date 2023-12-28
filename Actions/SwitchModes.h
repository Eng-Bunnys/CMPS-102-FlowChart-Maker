#pragma once
#include "../ApplicationManager.h"
#include "Action.h"

class SwitchModes : public Action
{
public:
	SwitchModes(ApplicationManager* P);

	//Read Assignemt statements position
	virtual void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();

};