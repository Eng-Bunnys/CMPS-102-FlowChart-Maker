#ifndef READ_H
#define READ_H

#include "../Statements/Statement.h"
#include "../ApplicationManager.h"

/**
 * @brief Read class represents a Read statement in the flowchart.
 *
 * The Read statement assigns a value to a variable.
 */
class Read : public Statement
{
private:
    string Variable; // The variable to be read.

    // Value Assignment Stat. has one Connector to the next statement
    // Each statement type in the flowchart has a predefined number of (output) connectors
    // For example, a conditional statement always has 2 output connectors

    // Note: We don't need to keep track with input connectors
    // Whenever we want to iterate on all statements of the flowchart
    // we will begin with the start statement then its output connector
    // then the connector's destination statement and so on (follow the connectors)

    // A point a connection leaves this statement
    // It's used as the (Start) point of the (Output) connector
    Point LeftCorner; // Left corner of the statement block.

    /**
     * @brief Updates the text representation of the Read statement.
     */
    virtual void UpdateStatementText();

public:
    /**
     * @brief Constructs a Read object with the given parameters.
     *
     * @param Lcorner The left corner of the Read statement.
     * @param rVariable The variable to be read.
     */
    Read(Point Lcorner, string rVariable = "");

    /**
     * @brief Sets the variable to be read.
     *
     * @param rVariable The variable to be read.
     */
    void setVariable(const string& rVariable);

    /**
     * @brief Draws the Read statement on the output.
     *
     * @param pOut Pointer to the Output class for drawing.
     */
    virtual void Draw(Output* pOut) const;

    /**
     * @brief Gets the left corner of the Read statement.
     *
     * @return Point representing the left corner of the Read statement.
     */
    Point getLeftCorner() const;

    /**
     * @brief Checks if a given point is within the Read statement.
     *
     * @param position The point to check.
     * @return True if the point is within the Read statement, false otherwise.
     */
    virtual bool ContainsPoint(Point position);

    /**
     * @brief Saves the Read statement to the output file.
     *
     * @param OutFile The output file stream.
     */
    virtual void Save(ofstream& OutFile);

    /**
     * @brief Loads a Read statement from the input file.
     *
     * @param Infile The input file stream.
     */
    virtual void Load(ifstream& Infile);

    /**
     * @brief Sets the outlet point of the Read statement.
     */
    virtual void SetOutlet();

    /**
     * @brief Sets the inlet point of the Read statement.
     */
    virtual void SetInlet();

    /**
     * @brief Sets the drawing point for the Read statement.
     *
     * @param P The new drawing point.
     */
    virtual void SetDrawingPoint(Point P);

    /**
     * @brief Clones the Read statement.
     *
     * @return A cloned instance of the Read statement.
     */
    virtual Statement* MakeCopy();

    /**
     * @brief Checks the variables used in the Read statement.
     *
     * @param arr An array of variable names.
     * @param c The count of variables.
     * @return True if the variables are valid, false otherwise.
     */
    virtual bool CheckVariables(string*& arr, int& c);

    /**
     * @brief Simulates the Read statement.
     *
     * @param pManager Pointer to the ApplicationManager.
     * @return True if the simulation is successful, false otherwise.
     */
    virtual bool Simulate(ApplicationManager* pManager = NULL);

    /**
     * @brief Edits the Read statement.
     *
     * @param pManager Pointer to the ApplicationManager.
     */
    virtual void Edit(ApplicationManager* pManager = NULL);
};

#endif