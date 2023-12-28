#pragma once
#include "Deleter.h"
#include "../Actions/Action.h"
#include "../Statements/ConditionalStatement.h"
#include "../Statements/End.h"
#include "../Statements/OperatorAssign.h"
#include "../Statements/Read.h"
#include "../Statements/Start.h"
#include "../Statements/VariableAssign.h"
#include "../Statements/Write.h"
#include "../Statements/ValueAssign.h"


class Delete : public Deleter
{
public:
	Delete(ApplicationManager* pManager);

	virtual void ReadActionParameters();

	virtual void Execute();

};

