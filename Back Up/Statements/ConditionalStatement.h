#pragma once
#ifndef CONDITIONAL_H
#define CONDITIONAL_H

#include "Statement.h"
#include "../ApplicationManager.h"

/**
 * @brief Represents a conditional statement in the flowchart.
 *
 * This class inherits from the Statement class and provides functionality
 * for creating and manipulating conditional statements.
 */
class Conditional : public Statement {
private:
    string LHS;        ///< Left-hand side of the conditional expression (variable)
    string Comparator;  ///< Comparison operator
    string RHS;        ///< Right-hand side of the conditional expression (value)

    Point OutletF;      ///< End point of the input connectors
    Point LeftCorner;   ///< Left corner of the statement block

    // Helper functions
    virtual void UpdateStatementText();
    virtual void Save(ofstream& OutFile);
    string getOperator();
    void ReversegetOperator(string S);

public:
    /**
     * @brief Constructor for the Conditional statement.
     * @param Lcorner The left corner of the conditional statement.
     * @param LeftHS The left-hand side of the conditional expression.
     * @param rComparator The comparison operator.
     * @param RightHS The right-hand side of the conditional expression.
     */
    Conditional(Point Lcorner, string LeftHS = "", string rComparator = "", string RightHS = "");

    // Setters for LHS, RHS, and Comparator
    void setLHS(const string& L);
    void setRHS(const string& R);
    void setComparator(const string& C);

    // Getters for LeftCorner and OutletF
    Point getLeftCorner() const;
    Point getFalseOutlet();

    // Draw the Conditional statement
    virtual void Draw(Output* pOut) const;

    // Check if a point is inside the Conditional statement
    virtual bool ContainsPoint(Point position);

    // Load Conditional statement from file
    virtual void Load(ifstream& Infile);

    // Calculate left corner based on center
    void CenterToLeftCorner(Point C);

    // Set outlets and inlets for the Conditional statement
    virtual void SetOutlet();
    virtual void SetInlet();

    // Set the drawing point for the Conditional statement
    virtual void SetDrawingPoint(Point P);

    // Clone the Conditional statement
    virtual Statement* MakeCopy();

    // Check if the variables in the Conditional statement are valid
    virtual bool CheckVariables(string*& arr, int& c);

    // Simulate the Conditional statement
    virtual bool Simulate(ApplicationManager* pManager = NULL);

    // Edit the Conditional statement
    virtual void Edit(ApplicationManager* pManager = NULL);
};

#endif