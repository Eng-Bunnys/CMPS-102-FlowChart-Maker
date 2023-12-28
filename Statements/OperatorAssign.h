#ifndef OPERATOR_ASSIGN_H
#define OPERATOR_ASSIGN_H

#include "Statement.h"
#include "../ApplicationManager.h"

/**
 * @brief The OperatorAssign class represents an assignment statement with an operator.
 */
class OperatorAssign : public Statement
{
private:
    string LHS;      ///< Left-hand side of the assignment (name of a variable).
    string RHSOne;   ///< First right-hand side operand.
    string Operator; ///< Operator (e.g., +, -, *, /).
    string RHSTwo;   ///< Second right-hand side operand.

    Point LeftCorner; ///< Left corner of the statement block.

    /**
     * @brief Updates the text representation of the operator assignment statement.
     */
    virtual void UpdateStatementText();

public:
    /**
     * @brief Constructor for OperatorAssign class.
     * @param Lcorner The top-left corner of the operator assignment statement.
     * @param LeftHS The left-hand side variable.
     * @param RightHSOne The first right-hand side operand.
     * @param oP The operator (e.g., +, -, *, /).
     * @param RightHSTwo The second right-hand side operand.
     */
    OperatorAssign(Point Lcorner, string LeftHS = "", string RightHSOne = "", string oP = "", string RightHSTwo = "");

    /**
     * @brief Draws the operator assignment statement on the output.
     * @param pOut Pointer to the output object for drawing.
     */
    virtual void Draw(Output* pOut) const;

    /**
     * @brief Gets the top-left corner of the operator assignment statement.
     * @return The top-left corner point.
     */
    Point getLeftCorner() const;

    /**
     * @brief Checks if a given point is within the boundaries of the operator assignment statement.
     * @param position The point to check.
     * @return True if the point is within the boundaries, false otherwise.
     */
    virtual bool ContainsPoint(Point position);

    /**
     * @brief Saves the operator assignment statement to an output file.
     * @param OutFile Output file stream.
     */
    virtual void Save(ofstream& OutFile);

    /**
     * @brief Gets the operator type for saving to a file.
     * @return The operator type as a string.
     */
    string getOperator();

    /**
     * @brief Loads the operator assignment statement from an input file.
     * @param Infile Input file stream.
     */
    virtual void Load(ifstream& Infile);

    /**
     * @brief Translates the operator type from file representation to internal representation.
     * @param S The operator type as a string.
     */
    void TranslateOperator(string S);

    /**
     * @brief Sets the outlet point for the operator assignment statement.
     */
    virtual void SetOutlet();

    /**
     * @brief Sets the inlet point for the operator assignment statement.
     */
    virtual void SetInlet();

    /**
     * @brief Sets the drawing point for the operator assignment statement.
     * @param P The new drawing point.
     */
    virtual void SetDrawingPoint(Point P);

    /**
     * @brief Creates a copy of the operator assignment statement.
     * @return A pointer to the copied statement.
     */
    virtual Statement* MakeCopy();

    /**
     * @brief Checks the validity of variables in the operator assignment statement.
     * @param arr Array of variables to check.
     * @param c Size of the array.
     * @return True if variables are valid, false otherwise.
     */
    virtual bool CheckVariables(string*& arr, int& c);

    /**
     * @brief Simulates the execution of the operator assignment statement.
     * @param pManager Pointer to the application manager.
     * @return True if simulation is successful, false otherwise.
     */
    virtual bool Simulate(ApplicationManager* pManager = NULL);

    /**
     * @brief Edits the operator assignment statement.
     * @param pManager Pointer to the application manager.
     */
    virtual void Edit(ApplicationManager* pManager = NULL);
};

#endif