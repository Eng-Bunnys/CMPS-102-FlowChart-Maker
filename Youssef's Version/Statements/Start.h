#ifndef START_H
#define START_H

#include "Statement.h"
#include "Connector.h"

/**
 * @brief The Start class represents the starting point of a flowchart.
 */
class Start : public Statement
{
private:
    Connector* pOutConn; ///< Pointer to the outgoing connector.
    Point LeftCorner;    ///< Position of the left corner of the Start shape.
    Point Outlet;        ///< Outlet point of the Start shape.

public:
    /**
     * @brief Constructor for the Start class.
     * @param Lcorner The position of the left corner of the Start shape.
     */
    Start(Point Lcorner);

    /**
     * @brief Draws the Start shape on the output window.
     * @param pOut Pointer to the Output class for drawing.
     */
    virtual void Draw(Output* pOut) const;

    /**
     * @brief Updates the statement text for the Start shape.
     * This function is required to implement the pure virtual function from the base class.
     */
    virtual void UpdateStatementText();

    /**
     * @brief Checks if a given point is inside the boundaries of the Start shape.
     * @param P The point to check.
     * @return True if the point is inside the Start shape, false otherwise.
     */
    virtual bool ContainsPoint(Point P);
};

#endif