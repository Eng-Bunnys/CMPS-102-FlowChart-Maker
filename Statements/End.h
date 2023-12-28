#ifndef END_H
#define END_H

#include "../Statements/Statement.h"
#include "../ApplicationManager.h"

// End statement class
// Represents the end of the flowchart
class End : public Statement
{
private:
    Point LeftCorner;  // Left corner of the statement block

    // Helper function to update the text representation of the End statement
    virtual void UpdateStatementText();

public:
    // Constructor for the End statement
    End(Point Lcorner);

    // Draw the End statement on the output window
    virtual void Draw(Output* pOut) const;

    // Get the left corner of the End statement
    Point getLcorner() const;

    // Check if a given point is inside the End statement
    virtual bool ContainsPoint(Point position);

    // Save the End statement to a file
    virtual void Save(ofstream& OutFile);

    // Load the End statement from a file
    virtual void Load(ifstream& Infile);

    // Calculate left corner based on center
    void CenterToLeftCorner(Point C);

    // Set the outlet point for the End statement
    virtual void SetOutlet();

    // Set the inlet point for the End statement
    virtual void SetInlet();

    // Set the drawing point for the End statement
    virtual void SetDrawingPoint(Point P);

    // Clone the End statement
    virtual Statement* MakeCopy();

    // Check if the End statement contains valid variables
    virtual bool CheckVariables(string*& arr, int& c);

    // Simulate the End statement
    virtual bool Simulate(ApplicationManager* pManager = NULL);

    // Edit the End statement
    virtual void Edit(ApplicationManager* pManager = NULL);
};

#endif