#pragma once

#include "../Action.h"

/*
1- Get point from the user
2- Recognize the selected area and detect the selected item
(i.e: Loop on each item in the statements list and find which one is located in this area using seperate conditions for each item type)
3- Add this item to selected items list in App manager and set it as "Selected" --> item then should be redrawn
4- if user clicks in another area,item(s) become unselected and
removed from  selected items list in App manager and set it as "unSelected" --> item then should be redrawn
*/


class Select : public Action
{
private:
	Point Position;

public:
	Select(ApplicationManager* pAppManager);

	virtual void ReadActionParameters();

	virtual void Execute();

}