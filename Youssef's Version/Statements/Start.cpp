#include "Start.h"

/**
 * @brief Constructor for the Start class.
 * @param Lcorner The position of the left corner of the Start shape.
 */
Start::Start(Point Lcorner)
{
    LeftCorner = Lcorner;
    pOutConn = NULL;
    Outlet.x = LeftCorner.x + UI.START_WDTH / 2;
    Outlet.y = LeftCorner.y + UI.START_HI;
}

/**
 * @brief Draws the Start shape on the output window.
 * @param pOut Pointer to the Output class for drawing.
 */
void Start::Draw(Output* pOut) const
{
    pOut->DrawStart(LeftCorner, UI.START_WDTH, UI.START_HI, "Start", Selected);
}

/**
 * @brief Updates the statement text for the Start shape.
 * This function is required to implement the pure virtual function from the base class.
 */
void Start::UpdateStatementText()
{
    Text = "Start";
}

/**
 * @brief Checks if a given point is inside the boundaries of the Start shape.
 * @param p The point to check.
 * @return True if the point is inside the Start shape, false otherwise.
 */
bool Start::ContainsPoint(Point p)
{
    if (p.x >= LeftCorner.x && p.x <= LeftCorner.x + UI.START_WDTH && p.y >= LeftCorner.y && p.y <= LeftCorner.y + UI.START_HI) {
        return true;
    }
    return false;
}

Statement* Start::CopyStatement()
{
    Statement* CopiedStatement = new Start(Point(0, 0));
    return CopiedStatement;
}