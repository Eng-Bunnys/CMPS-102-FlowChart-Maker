#ifndef COPY_H
#define COPY_H

#include "Action.h" // Assuming you have an Action base class

class Copy :public Action
{
public:
	Copy(ApplicationManager* pManager);

	virtual void ReadActionParameters();

	virtual void Execute();
};

#endif // COPY_H