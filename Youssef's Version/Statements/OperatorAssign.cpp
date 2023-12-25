#include "OperatorAssign.h"
#include <sstream>

using namespace std;

/**
 * @brief Constructor for the OperatorAssign class.
 * @param Lcorner The top-left corner of the OperatorAssign statement.
 * @param LeftHS The Left-Hand Side (LHS) of the assignment statement.
 * @param First The First input of the assignment statement.
 * @param op The Operator of the assignment statement.
 * @param Second The Second input of the assignment statement.
 */
OperatorAssign::OperatorAssign(Point Lcorner, string LeftHS, string First, string op, string Second)
    : LHS(LeftHS), RHSFirst(First), Operator(op), RHSSecond(Second)
{
    // Note: The LeftHS, First, Operator, and Second should be validated before passing them to the constructor
    // Initialize member variables and update the statement text
    UpdateStatementText();

    // Set the top-left corner of the OperatorAssign statement
    LeftCorner = Lcorner;

    // No connectors yet
    pOutConn = NULL;

    // Set the Inlet and Outlet points for the OperatorAssign statement
    Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
    Inlet.y = LeftCorner.y;
    Outlet.x = Inlet.x;
    Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}

/**
 * @brief Set the Left-Hand Side (LHS) of the assignment statement.
 * @param L The new value for the LHS.
 */
void OperatorAssign::setLHS(const string& L)
{
    LHS = L;
    UpdateStatementText();
}

/**
 * @brief Set the First input of the assignment statement.
 * @param F The new value for the First input.
 */
void OperatorAssign::setFirst(const string& F)
{
    RHSFirst = F;
    UpdateStatementText();
}

/**
 * @brief Set the Operator of the assignment statement.
 * @param O The new value for the Operator.
 */
void OperatorAssign::setOperator(const string& Op)
{
    Operator = Op;
    UpdateStatementText();
}

/**
 * @brief Set the Second input of the assignment statement.
 * @param S The new value for the Second input.
 */
void OperatorAssign::setSecond(const string& S)
{
    RHSSecond = S;
    UpdateStatementText();
}

/**
 * @brief Draw the OperatorAssign statement on the output window.
 * @param pOut Pointer to the Output class for drawing.
 */
void OperatorAssign::Draw(Output* pOut) const
{
    pOut->DrawAssign(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);
}

/**
 * @brief Update the statement text based on the current values of LHS, RHSFirst, Operator, and RHSSecond.
 */
void OperatorAssign::UpdateStatementText()
{
    // Build the statement text: Left-hand side, equals sign, First input, Operator, Second input
    ostringstream T;
    T << LHS << " = " << RHSFirst << " " << Operator << " " << RHSSecond;
    Text = T.str();
}

/**
 * @brief Check if a given point is inside the boundaries of the OperatorAssign statement.
 * @param p The point to check.
 * @return True if the point is inside the statement, false otherwise.
 */
bool OperatorAssign::ContainsPoint(Point p)
{
    if (p.x >= LeftCorner.x && p.x <= LeftCorner.x + UI.ASSGN_WDTH && p.y >= LeftCorner.y && p.y <= LeftCorner.y + UI.ASSGN_HI)
    {
        return true;
    }
    return false;
}