#ifndef VALUE_ASSIGN_H
#define VALUE_ASSIGN_H

#include "Statement.h"
///Yeah I added docs to this file too xD

/**
 * @brief Value Assignment statement class.
 *
 * The value assignment statement assigns a value to a variable.
 */
class ApplicationManager;
class ValueAssign : public Statement
{
private:
    string LHS;     // Left Handside of the assignment (name of a variable)
    double RHS;     // Right Handside (Value)

    // Value Assignment Stat. has one Connector to the next statement
    // Each statement type in flowchart has a predefined number of (output) connectors
    // For example, conditional statement always has 2 output connectors
    // Note: We don't need to keep track with input connectors
    // Whenever we want to iterate on all statements of the flowchart,
    // we will begin with the start statement then its output connector,
    // then the connector's destination statement and so on (follow the connectors)

    // A point a connection leaves this statement
    // It's used as the (Start) point of the (Output) connector
    Point LeftCorner; // left corner of the statement block.

    /**
     * @brief Update the text representation of the statement.
     */
    virtual void UpdateStatementText();

public:
    /**
     * @brief Constructor for the ValueAssign class.
     * @param Lcorner The left corner of the statement block.
     * @param LeftHS The left-hand side of the assignment (variable name).
     * @param RightHS The right-hand side of the assignment (value).
     */
    ValueAssign(Point Lcorner, string LeftHS = "", double RightHS = 0);

    /**
     * @brief Set the left-hand side (LHS) of the assignment.
     * @param L The left-hand side variable name.
     */
    void setLHS(const string& L);

    /**
     * @brief Set the right-hand side (RHS) of the assignment.
     * @param R The right-hand side value.
     */
    void setRHS(double R);

    /**
     * @brief Draw the ValueAssign statement.
     * @param pOut Pointer to the output interface.
     */
    virtual void Draw(Output* pOut) const;

    /**
     * @brief Get the left corner of the statement block.
     * @return The left corner point.
     */
    Point getLeftCorner() const;

    /**
     * @brief Check if a point is inside the statement block.
     * @param position The point to check.
     * @return True if the point is inside the statement block, false otherwise.
     */
    virtual bool ContainsPoint(Point position);

    /**
     * @brief Save the statement to a file.
     * @param OutFile The output file stream.
     */
    virtual void Save(ofstream& OutFile);

    /**
     * @brief Load the statement from a file.
     * @param Infile The input file stream.
     */
    virtual void Load(ifstream& Infile);

    /**
     * @brief Set the outlet point for the statement.
     */
    virtual void SetOutlet();

    /**
     * @brief Set the inlet point for the statement.
     */
    virtual void SetInlet();

    /**
     * @brief Set the drawing point for the statement.
     * @param P The new drawing point.
     */
    virtual void SetDrawingPoint(Point P);

    /**
     * @brief Clone the ValueAssign statement.
     * @return A pointer to the cloned statement.
     */
    virtual Statement* MakeCopy();

    /**
     * @brief Check and add the LHS variable to the array of variables.
     * @param arr The array of variables.
     * @param c The count of variables in the array.
     * @return True if the variable was successfully added or already exists, false otherwise.
     */
    virtual bool CheckVariables(string*& arr, int& c);

    /**
     * @brief Simulate the execution of the statement.
     * @param pManager Pointer to the application manager.
     * @return True if the simulation was successful, false otherwise.
     */
    virtual bool Simulate(ApplicationManager* pManager = NULL);

    /**
     * @brief Edit the properties of the ValueAssign statement.
     * @param pManager Pointer to the application manager.
     */
    virtual void Edit(ApplicationManager* pManager = NULL);
};

#endif