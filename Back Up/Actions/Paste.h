#ifndef PASTE_H
#define PASTE_H

#include "Action.h" 

class Paste :public Action
{
protected:
	Point Position;
public:
	Paste(ApplicationManager* pManager);

	virtual void ReadActionParameters();

	virtual void Execute();
};

#endif // PASTE_H