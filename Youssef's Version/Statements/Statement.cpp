#include "Statement.h"

int Statement::IDCounter = 1;

Statement::Statement()
{
    ID = IDCounter++;
    Text = "";
    Selected = false;
}

void Statement::SetSelected(bool s)
{
    Selected = s;
}

bool Statement::IsSelected() const
{
    return Selected;
}

int Statement::GetID() const
{
    return ID;
}