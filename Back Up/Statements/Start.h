#ifndef START_H
#define START_H

#include "../Statements/Statement.h"
#include "../ApplicationManager.h"

/**
 * @brief Start statement class.
 *
 * Represents a start statement in the flowchart.
 * The start statement indicates the beginning of the flowchart.
 */
class Start : public Statement
{
private:
    Point LeftCorner; // Left corner of the statement block.

    // Helper function
    virtual void UpdateStatementText();

public:
    /**
     * @brief Constructor for the Start statement.
     *
     * Initializes the Start statement with the given left corner.
     * @param Lcorner The left corner of the Start statement.
     */
    Start(Point Lcorner);

    /**
     * @brief Draws the Start statement on the output window.
     *
     * Calls the DrawStart function of the Output class to draw the Start statement.
     * @param pOut Pointer to the Output class for drawing.
     */
    virtual void Draw(Output* pOut) const;

    /**
     * @brief Gets the left corner of the Start statement.
     * @return The left corner of the Start statement.
     */
    Point getLeftCorner() const;

    /**
     * @brief Checks if a given point is inside the Start statement.
     * @param position The point to check.
     * @return True if the point is inside the Start statement, false otherwise.
     */
    virtual bool ContainsPoint(Point position);

    /**
     * @brief Saves the Start statement to a file.
     *
     * Writes the Start statement details to the output file.
     * @param OutFile Output file stream.
     */
    virtual void Save(ofstream& OutFile);

    /**
     * @brief Loads the Start statement from a file.
     *
     * Reads the Start statement details from the input file.
     * @param Infile Input file stream.
     */
    virtual void Load(ifstream& Infile);

    /**
     * @brief Calculates the left corner based on the center of the Start statement.
     * @param C The center of the Start statement.
     */
    void CenterToLeftCorner(Point C);

    /**
     * @brief Sets the outlet point for the Start statement.
     */
    virtual void SetOutlet();

    /**
     * @brief Sets the inlet point for the Start statement.
     */
    virtual void SetInlet();

    /**
     * @brief Sets the drawing point for the Start statement.
     *
     * @param P The drawing point for the Start statement.
     */
    virtual void SetDrawingPoint(Point P);

    /**
     * @brief Clones the Start statement.
     * @return A new instance of the Start statement.
     */
    virtual Statement* MakeCopy();

    /**
     * @brief Checks if the Start statement contains valid variables.
     *
     * Since the Start statement does not contain variables, always returns false.
     * @param arr Array of variables.
     * @param c Number of variables.
     * @return Always false.
     */
    virtual bool CheckVariables(string*& arr, int& c);

    /**
     * @brief Simulates the Start statement.
     *
     * Since the Start statement does not have any simulation logic, always returns false.
     * @param pManager Pointer to the ApplicationManager.
     * @return Always false.
     */
    virtual bool Simulate(ApplicationManager* pManager = NULL);

    /**
     * @brief Edits the Start statement.
     *
     * Since the Start statement does not have any editable properties, does nothing.
     * @param pManager Pointer to the ApplicationManager.
     */
    virtual void Edit(ApplicationManager* pManager);
};

#endif