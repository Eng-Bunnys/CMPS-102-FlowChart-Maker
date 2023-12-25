#ifndef VARIABLE_ASSIGN_H
#define VARIABLE_ASSIGN_H

#include "Statement.h"
#include "Connector.h"

/**
 * @brief The VariableAssign class represents a variable assignment statement in a flowchart.
 * The variable assignment statement assigns a value to a variable.
 */
class VariableAssign : public Statement
{
private:
    string LHS;           ///< Left-hand side of the assignment (name of a variable).
    string RHS;           ///< Right-hand side (Value).
    Connector* pOutConn;  ///< Variable Assignment Statement has one Connector to the next statement.

    Point Inlet;          ///< A point where connections enter this statement.
    Point Outlet;         ///< A point a connection leaves this statement.

    Point LeftCorner;     ///< Left corner of the statement block.

    /**
     * @brief Updates the statement text for the VariableAssign shape.
     * This function should be called when LHS or RHS changes.
     */
    virtual void UpdateStatementText();

public:
    /**
     * @brief Constructor for the VariableAssign class.
     * @param Lcorner The position of the left corner of the VariableAssign shape.
     * @param LeftHS The left-hand side of the assignment.
     * @param RightHS The right-hand side of the assignment.
     */
    VariableAssign(Point Lcorner, string LeftHS = "", string RightHS = "");

    /**
     * @brief Sets the left-hand side of the assignment.
     * @param L The string representing the left-hand side.
     */
    void setLHS(const string& L);

    /**
     * @brief Sets the right-hand side of the assignment.
     * @param R The string representing the right-hand side.
     */
    void setRHS(const string& R);

    /**
     * @brief Draws the VariableAssign shape on the output window.
     * @param pOut Pointer to the Output class for drawing.
     */
    virtual void Draw(Output* pOut) const;

    /**
     * @brief Checks if a given point is inside the boundaries of the VariableAssign shape.
     * @param P The point to check.
     * @return True if the point is inside the VariableAssign shape, false otherwise.
     */
    virtual bool ContainsPoint(Point P);

    virtual Statement* CopyStatement();
};

#endif