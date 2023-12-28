#ifndef WRITE_H
#define WRITE_H

#include "../Statements/Statement.h"
#include "../ApplicationManager.h"

/**
 * @brief Write class represents a Write statement in the flowchart.
 *
 * The Write statement writes a variable or message to the output.
 */
class Write : public Statement
{
private:
    string Variable; // The variable or message to be written.

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
     * @brief Updates the text representation of the Write statement.
     */
    virtual void UpdateStatementText();

public:
    /**
     * @brief Constructs a Write object with the given parameters.
     *
     * @param Lcorner The left corner of the Write statement.
     * @param rVariable The variable or message to be written.
     */
    Write(Point Lcorner, string rVariable = "");

    /**
     * @brief Sets the variable or message to be written.
     *
     * @param rVariable The variable or message to be written.
     */
    void setVariable(const string& rVariable);

    /**
     * @brief Draws the Write statement on the output.
     *
     * @param pOut Pointer to the Output class for drawing.
     */
    virtual void Draw(Output* pOut) const;

    /**
     * @brief Gets the left corner of the Write statement.
     *
     * @return Point representing the left corner of the Write statement.
     */
    Point getLeftCorner() const;

    /**
     * @brief Checks if a given point is within the Write statement.
     *
     * @param position The point to check.
     * @return True if the point is within the Write statement, false otherwise.
     */
    virtual bool ContainsPoint(Point position);

    /**
     * @brief Saves the Write statement to the output file.
     *
     * @param OutFile The output file stream.
     */
    virtual void Save(ofstream& OutFile);

    /**
     * @brief Loads a Write statement from the input file.
     *
     * @param Infile The input file stream.
     */
    virtual void Load(ifstream& Infile);

    /**
     * @brief Sets the outlet point of the Write statement.
     */
    virtual void SetOutlet();

    /**
     * @brief Sets the inlet point of the Write statement.
     */
    virtual void SetInlet();

    /**
     * @brief Sets the drawing point for the Write statement.
     *
     * @param P The new drawing point.
     */
    virtual void SetDrawingPoint(Point P);

    /**
     * @brief Clones the Write statement.
     *
     * @return A cloned instance of the Write statement.
     */
    virtual Statement* MakeCopy();

    /**
     * @brief Checks the variables used in the Write statement.
     *
     * @param arr An array of variable names.
     * @param c The count of variables.
     * @return True if the variables are valid, false otherwise.
     */
    virtual bool CheckVariables(string*& arr, int& c);

    /**
     * @brief Simulates the Write statement.
     *
     * @param pManager Pointer to the ApplicationManager.
     * @return True if the simulation is successful, false otherwise.
     */
    virtual bool Simulate(ApplicationManager* pManager = NULL);

    /**
     * @brief Edits the Write statement.
     *
     * @param pManager Pointer to the ApplicationManager.
     */
    virtual void Edit(ApplicationManager* pManager = NULL);
};

#endif