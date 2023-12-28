#pragma once
#include "Action.h"
#include "../ApplicationManager.h"
#include "Validate.h"
class Run : public Action
{
public:
	Run(ApplicationManager* ApM);
	virtual void ReadActionParameters();
	virtual void Execute();
};

