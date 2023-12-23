#ifndef END_H
#define END_H

#include "Statement.h"
#include "Connector.h"

class End : public Statement
{
private:
    Connector* pOutConn;
    Point LeftCorner;
    Point Outlet;

public:
    End(Point Lcorner);

    virtual void Draw(Output* pOut) const;

    // Implement the pure virtual function from the base class
    virtual void UpdateStatementText();
};

#endif