#ifndef VALUE_ASSIGN_H
#define VALUE_ASSIGN_H

#include "Statement.h"
#include "Connector.h"

/*
Yes I've also updated this file :skull:
*/

/**
 * @brief The ValueAssign class represents a value assignment statement in a flowchart.
 * The value assignment statement assigns a value to a variable.
 */
class ValueAssign : public Statement
{
private:
    string LHS;            // Left-hand side of the assignment (name of a variable).
    double RHS;            // Right-hand side (Value).
    Connector* pOutConn;   // Value Assignment Statement has one Connector to the next statement.
    // Each statement type in a flowchart has a predefined number of (output) connectors.
    // Note: We don't need to keep track of input connectors.
    // Whenever we want to iterate on all statements of the flowchart,
    // we will begin with the start statement, then its output connector,
    // then the connector's destination statement, and so on (follow the connectors).

    Point Inlet;           // A point where connections enter this statement.
    // It's used as the (End) point of the (Input) connectors.
    Point Outlet;          // A point a connection leaves this statement.
    // It's used as the (Start) point of the (Output) connector.

    Point LeftCorner;      // Left corner of the statement block.

    /**
     * @brief Updates the statement text for the ValueAssign shape.
     * This function should be called when LHS or RHS changes.
     */
    virtual void UpdateStatementText();

public:
    /**
     * @brief Constructor for the ValueAssign class.
     * @param Lcorner The position of the left corner of the ValueAssign shape.
     * @param LeftHS The left-hand side of the assignment.
     * @param RightHS The right-hand side of the assignment.
     */
    ValueAssign(Point Lcorner, string LeftHS = "", double RightHS = 0);

    /**
     * @brief Sets the left-hand side of the assignment.
     * @param L The string representing the left-hand side.
     */
    void setLHS(const string& L);

    /**
     * @brief Sets the right-hand side of the assignment.
     * @param R The value representing the right-hand side.
     */
    void setRHS(double R);

    /**
     * @brief Draws the ValueAssign shape on the output window.
     * @param pOut Pointer to the Output class for drawing.
     */
    virtual void Draw(Output* pOut) const;

    /**
     * @brief Checks if a given point is inside the boundaries of the ValueAssign shape.
     * @param P The point to check.
     * @return True if the point is inside the ValueAssign shape, false otherwise.
     */
    virtual bool ContainsPoint(Point P);

    virtual Statement* CopyStatement();
};

#endif
