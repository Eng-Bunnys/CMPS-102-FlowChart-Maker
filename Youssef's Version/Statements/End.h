#ifndef END_H
#define END_H

#include "Statement.h"
#include "Connector.h"

class End : public Statement
{
private:
    Connector* pOutConn; // Pointer to the outgoing connector
    Point LeftCorner;    // Top-left corner of the End statement
    Point Inlet;        // Inlet point of the statement

public:
    /**
     * @brief Constructor for the End class.
     * @param Lcorner Top-left corner of the End statement.
     */
    End(Point Lcorner);

    /**
     * @brief Draws the End statement on the output window.
     * @param pOut Pointer to the Output class for drawing.
     */
    virtual void Draw(Output* pOut) const;

    // Implement the pure virtual function from the base class
    virtual void UpdateStatementText(); // Updates the text representation of the End statement
    virtual bool ContainsPoint(Point P); // Checks if a given point is inside the boundaries of the End statement.
    virtual Statement* CopyStatement();
    virtual void SetPosition(Point P);
};

#endif