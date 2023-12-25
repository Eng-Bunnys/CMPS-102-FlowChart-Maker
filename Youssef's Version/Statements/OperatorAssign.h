#ifndef OPERATOR_ASSIGN_H
#define OPERATOR_ASSIGN_H

#include "Statement.h"
#include "Connector.h"

/**
 * @brief The OperatorAssign class represents an assignment statement with an operator.
 */
class OperatorAssign : public Statement
{
private:
    string LHS;      ///< Left-hand side variable
    string RHSFirst;  ///< First input (value or variable)
    string Operator;       ///< Operator
    string RHSSecond; ///< Second input (value or variable)

    Connector* pOutConn; ///< OperatorAssign statement has one Connector to the next statement
    Point Inlet;         ///< A point where connections enter this statement (End point of Input connectors)
    Point Outlet;        ///< A point where a connection leaves this statement (Start point of Output connector)

    Point LeftCorner; ///< Left corner of the statement block

    /**
     * @brief Updates the text representation of the statement based on its members.
     */
    virtual void UpdateStatementText();

public:
    /**
     * @brief Constructor for the OperatorAssign class.
     * @param Lcorner The top-left corner of the OperatorAssign statement.
     * @param LeftHS The Left-Hand Side (LHS) of the assignment statement.
     * @param First The First input of the assignment statement.
     * @param Operator The Operator of the assignment statement.
     * @param Second The Second input of the assignment statement.
     */
    OperatorAssign(Point Lcorner, string LeftHS = "", string First = "", string Operator = "", string Second = "");

    /**
     * @brief Set the Left-Hand Side (LHS) of the assignment statement.
     * @param L The new value for the LHS.
     */
    void setLHS(const string& L);

    /**
     * @brief Set the First input of the assignment statement.
     * @param F The new value for the First input.
     */
    void setFirst(const string& F);

    /**
     * @brief Set the Operator of the assignment statement.
     * @param Op The new value for the Operator.
     */
    void setOperator(const string& Op);

    /**
     * @brief Set the Second input of the assignment statement.
     * @param S The new value for the Second input.
     */
    void setSecond(const string& S);

    /**
     * @brief Draw the OperatorAssign statement on the output window.
     * @param pOut Pointer to the Output class for drawing.
     */
    virtual void Draw(Output* pOut) const;

    /**
     * @brief Check if a given point is inside the boundaries of the OperatorAssign statement.
     * @param P The point to check.
     * @return True if the point is inside the statement, false otherwise.
     */
    virtual bool ContainsPoint(Point P);
    virtual Statement* CopyStatement();
};

#endif // OPERATOR_ASSIGN_H