// Start.h
#ifndef START_H
#define START_H

#include "Statement.h"
#include "Connector.h"

class Start : public Statement
{
private:
    Connector *pOutConn;
    Point LeftCorner;
    Point Outlet;

public:
    Start(Point Lcorner);

    virtual void Draw(Output *pOut) const;

    // Implement the pure virtual function from the base class
    virtual void UpdateStatementText();
};

#endif