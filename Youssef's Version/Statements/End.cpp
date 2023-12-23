#include "End.h"

End::End(Point Lcorner)
{
    LeftCorner = Lcorner;
    pOutConn = NULL;
    Outlet.x = LeftCorner.x + UI.START_WDTH / 2;
    Outlet.y = LeftCorner.y + UI.START_HI;
}

void End::Draw(Output* pOut) const
{
    pOut->DrawStart(LeftCorner, UI.START_WDTH, UI.START_HI, "End", Selected);
}

// Implement the pure virtual function from the base class
void End::UpdateStatementText()
{
    // Implement the logic to update the statement text if needed
    // For example, set Text to a default value or update it based on some conditions
    Text = "End";
}