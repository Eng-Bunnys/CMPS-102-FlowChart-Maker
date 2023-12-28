#pragma once
#ifndef VARIABLE_ASSIGN_H
#define VARIABLE_ASSIGN_H

#include "../Statements/Statement.h"
#include "../ApplicationManager.h"

/**
 * @class VariableAssign
 * @brief Represents a variable assignment statement in the flowchart.
 * The variable assignment statement assigns a value to a variable.
 */
class VariableAssign : public Statement
{
private:
    string LHS;  /**< Left Handside of the assignment (name of a variable) */
    string RHS;  /**< Right Handside (Value) */

    // A point a connection leaves this statement
    // It's used as the (Start) point of the (Output) connector
    Point LeftCorner;  /**< Left corner of the statement block. */

    /**
     * @brief Updates the text representation of the statement based on LHS and RHS.
     */
    virtual void UpdateStatementText();

public:
    /**
     * @brief Constructor for VariableAssign.
     * @param Lcorner The left corner of the statement block.
     * @param LeftHS Left-hand side of the assignment (variable name).
     * @param RightHS Right-hand side of the assignment (value).
     */
    VariableAssign(Point Lcorner, string LeftHS = "", string RightHS = "");

    /**
     * @brief Set the left-hand side (LHS) of the assignment.
     * @param L The left-hand side (variable name).
     */
    void setLHS(const string& L);

    /**
     * @brief Set the right-hand side (RHS) of the assignment.
     * @param R The right-hand side (value).
     */
    void setRHS(const string& R);

    /**
     * @brief Draw the VariableAssign statement on the output.
     * @param pOut Pointer to the Output class for drawing.
     */
    virtual void Draw(Output* pOut) const;

    /**
     * @brief Get the left corner of the statement block.
     * @return Point representing the left corner.
     */
    Point getLeftCorner() const;

    /**
     * @brief Check if a given point is inside the VariableAssign statement.
     * @param position The point to check.
     * @return True if the point is inside the statement, false otherwise.
     */
    virtual bool ContainsPoint(Point position);

    /**
     * @brief Save the VariableAssign statement to an output file.
     * @param OutFile The output file stream.
     */
    virtual void Save(ofstream& OutFile);

    /**
     * @brief Load the VariableAssign statement from an input file.
     * @param Infile The input file stream.
     */
    virtual void Load(ifstream& Infile);

    /**
     * @brief Set the outlet point for connectors.
     */
    virtual void SetOutlet();

    /**
     * @brief Set the inlet point for connectors.
     */
    virtual void SetInlet();

    /**
     * @brief Set the drawing point for the VariableAssign statement.
     * @param P The new drawing point.
     */
    virtual void SetDrawingPoint(Point P);

    /**
     * @brief Clone the VariableAssign statement.
     * @return A pointer to the cloned VariableAssign statement.
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
     * @brief Simulate the VariableAssign statement (placeholder implementation).
     * @param pManager Pointer to the ApplicationManager.
     * @return Always returns true.
     */
    virtual bool Simulate(ApplicationManager* pManager = NULL);

    /**
     * @brief Edit the VariableAssign statement.
     * @param pManager Pointer to the ApplicationManager.
     */
    virtual void Edit(ApplicationManager* pManager = NULL);
};

#endif