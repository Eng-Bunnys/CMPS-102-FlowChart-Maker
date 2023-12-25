#ifndef CONDITIONAL_STATEMENT_H
#define CONDITIONAL_STATEMENT_H

#include "Statement.h"
#include "Connector.h"

/**
 * @class ConditionalStatement
 * @brief Represents a conditional statement in the flowchart.
 */
class ConditionalStatement : public Statement {
private:
    string LHS; ///< Left-hand side of the conditional statement.
    string RHS; ///< Right-hand side of the conditional statement.
    string Operator; ///< Comparison operator used in the conditional statement.

    Connector* pOutConn; ///< Pointer to the outgoing connector.
    Point Inlet; ///< Inlet point for incoming connectors.
    Point Outlet; ///< Outlet point for outgoing connectors.

    Point LeftCorner; ///< Top-left corner of the conditional statement.

    /**
     * @brief Updates the text representation of the conditional statement.
     */
    virtual void UpdateStatementText() override;

public:
    /**
     * @brief Constructor for the ConditionalStatement class.
     * @param Lcorner Top-left corner of the conditional statement.
     * @param lhs Left-hand side initial value (default is an empty string).
     * @param oper Comparison operator initial value (default is an empty string).
     * @param rhs Right-hand side initial value (default is an empty string).
     */
    ConditionalStatement(Point Lcorner, string lhs = "", string oper = "", string rhs = "");

    /**
     * @brief Sets the left-hand side of the conditional statement.
     * @param L New left-hand side value.
     */
    void setLHS(const string& L);

    /**
     * @brief Sets the right-hand side of the conditional statement.
     * @param F New right-hand side value.
     */
    void setRHS(const string& F);

    /**
     * @brief Sets the comparison operator of the conditional statement.
     * @param O New comparison operator.
     */
    void setOperator(const string& Op);

    /**
     * @brief Draws the conditional statement on the output window.
     * @param pOut Pointer to the Output class for drawing.
     */
    virtual void Draw(Output* pOut) const override;

    /**
     * @brief Checks if a given point is inside the boundaries of the conditional statement.
     * @param position Point to check.
     * @return True if the point is inside the statement, false otherwise.
     */
    virtual bool ContainsPoint(Point position);
};

#endif // !CONDITIONAL_STATEMENT_H
