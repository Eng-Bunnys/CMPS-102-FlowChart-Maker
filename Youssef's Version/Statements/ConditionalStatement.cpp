#include "ConditionalStatement.h"
#include <sstream>

/**
 * @class ConditionalStatement
 * @brief Represents a conditional statement in the flowchart.
 */
ConditionalStatement::ConditionalStatement(Point Lcorner, string lhs, string Op, string rhs)
    : LHS(lhs), Operator(Op), RHS(rhs)
{
    UpdateStatementText();

    Inlet.x = Lcorner.x + UI.COND_WDTH / 2;
    Inlet.y = Lcorner.y;

    Outlet.x = Inlet.x;
    Outlet.y = Lcorner.y + UI.COND_HI;

    pOutConn = nullptr;
    LeftCorner = Lcorner;
}

/**
 * @brief Sets the left-hand side of the conditional statement.
 * @param L New left-hand side value.
 */
void ConditionalStatement::setLHS(const string& L)
{
    LHS = L;
    UpdateStatementText();
}

/**
 * @brief Sets the right-hand side of the conditional statement.
 * @param R New right-hand side value.
 */
void ConditionalStatement::setRHS(const string& R)
{
    RHS = R;
    UpdateStatementText();
}

/**
 * @brief Sets the comparison operator of the conditional statement.
 * @param O New comparison operator.
 */
void ConditionalStatement::setOperator(const string& Op)
{
    Operator = Op;
    UpdateStatementText();
}

/**
 * @brief Draws the conditional statement on the output window.
 * @param pOut Pointer to the Output class for drawing.
 */
void ConditionalStatement::Draw(Output* pOut) const
{
    pOut->DrawConditionalStat(LeftCorner, UI.COND_WDTH, UI.COND_HI, Text, Selected);
}

/**
 * @brief Updates the text representation of the conditional statement.
 */
void ConditionalStatement::UpdateStatementText()
{
    // Build the statement text: Left-hand side then operator then right-hand side
    ostringstream T;
    T << LHS << " " << Operator << " " << RHS;
    Text = T.str();
}

/**
 * @brief Checks if a given point is inside the boundaries of the conditional statement.
 * @param p Point to check.
 * @return True if the point is inside the statement, false otherwise.
 */
bool ConditionalStatement::ContainsPoint(Point p)
{
    if (p.x >= LeftCorner.x && p.x <= LeftCorner.x + UI.COND_WDTH && p.y >= LeftCorner.y - UI.COND_HI / 2 && p.y <= LeftCorner.y + UI.COND_HI / 2) {
        return true;
    }
    return false;
}

Statement* ConditionalStatement::CopyStatement()
{
    Statement* CopiedStatement = new ConditionalStatement(Point(0, 0), ((ConditionalStatement*)this)->LHS, ((ConditionalStatement*)this)->Operator, ((ConditionalStatement*)this)->RHS);
    return CopiedStatement;
}

void ConditionalStatement::SetPosition(Point P) {
    LeftCorner = P;
    LeftCorner.x = P.x - UI.COND_WDTH / 2;
    LeftCorner.y = P.y + UI.COND_HI / 2;

    /// setOutlet();
   /// setIntlet();
}