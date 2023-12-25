#include "VariableAssign.h"
#include <sstream>

/**
 * @brief Constructor for the VariableAssign class.
 * @param Lcorner The position of the left corner of the VariableAssign shape.
 * @param LeftHS The left-hand side of the assignment.
 * @param RightHS The right-hand side of the assignment.
 */
VariableAssign::VariableAssign(Point Lcorner, string LeftHS, string RightHS)
{
    LHS = LeftHS;
    RHS = RightHS;

    UpdateStatementText();

    LeftCorner = Lcorner;

    pOutConn = NULL; // No connectors yet

    Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
    Inlet.y = LeftCorner.y;

    Outlet.x = Inlet.x;
    Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}

/**
 * @brief Sets the left-hand side of the assignment.
 * @param L The string representing the left-hand side.
 */
void VariableAssign::setLHS(const string& L)
{
    LHS = L;
    UpdateStatementText();
}

/**
 * @brief Sets the right-hand side of the assignment.
 * @param R The string representing the right-hand side.
 */
void VariableAssign::setRHS(const string& R)
{
    RHS = R;
    UpdateStatementText();
}

/**
 * @brief Draws the VariableAssign shape on the output window.
 * @param pOut Pointer to the Output class for drawing.
 */
void VariableAssign::Draw(Output* pOut) const
{
    // Call Output::DrawAssign function to draw assignment statement
    pOut->DrawAssign(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);
}

/**
 * @brief Updates the statement text for the VariableAssign shape.
 * This function should be called when LHS or RHS changes.
 */
void VariableAssign::UpdateStatementText()
{
    // Build the statement text: Left-hand side then equals then right-hand side
    ostringstream T;
    T << LHS << " = " << RHS;
    Text = T.str();
}

/**
 * @brief Checks if a given point is inside the boundaries of the VariableAssign shape.
 * @param p The point to check.
 * @return True if the point is inside the VariableAssign shape, false otherwise.
 */
bool VariableAssign::ContainsPoint(Point p)
{
    if (p.x >= LeftCorner.x && p.x <= LeftCorner.x + UI.ASSGN_WDTH && p.y >= LeftCorner.y && p.y <= LeftCorner.y + UI.ASSGN_HI) {
        return true;
    }
    return false;
}

Statement* VariableAssign::CopyStatement()
{
    Statement* CopiedStatement = new VariableAssign(Point(0, 0), ((VariableAssign*)this)->LHS, ((VariableAssign*)this)->RHS);
    return CopiedStatement;
}