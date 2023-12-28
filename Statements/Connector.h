#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "../GUI/UI_Info.h"
#include "../GUI/Output.h"
#include "../GUI/Input.h"

class Conditional;
class Statement;

class Connector
{
private:
    Statement* SrcStat; // The source statement of the connector
    Statement* DstStat; // The destination statement of the connector
    Point Start;        // Start point of the connector
    Point End;          // End point of the connector
    bool Selected;      // Indicates whether the connector is selected
    int Case;           // Case number (used for connectors between conditional statements)

public:
    /**
     * @brief Constructor for the Connector class.
     *
     * @param Src The source statement of the connector.
     * @param Dst The destination statement of the connector.
     * @param rCase The case number (default is 0).
     */
    Connector(Statement* Src, Statement* Dst, int rCase);

    void setSrcStat(Statement* Src);   // Setter for the source statement
    Statement* getSrcStat() const;     // Getter for the source statement
    void setDstStat(Statement* Dst);   // Setter for the destination statement
    Statement* getDstStat();           // Getter for the destination statement

    /**
     * @brief Sets the start and end points of the connector.
     */
    void setStartAndEnd();

    void setStartPoint(Point P);       // Setter for the start point
    Point getStartPoint();              // Getter for the start point

    void setEndPoint(Point P);         // Setter for the end point
    Point getEndPoint();                // Getter for the end point

    /**
     * @brief Draws the connector on the output window.
     *
     * @param pOut Pointer to the output object used for drawing.
     */
    void Draw(Output* pOut) const;

    void SetSelected(bool rSelected);   // Setter for the selected status
    bool IsSelected() const;            // Checks if the connector is selected

    /**
     * @brief Checks if a point is inside the connector.
     *
     * @param P The point to check.
     * @return true if the point is inside the connector, false otherwise.
     */
    bool isInConnector(Point P);

    void SetCase(int rCase = 0);        // Setter for the case number
    void Save(ofstream& OutFile);       // Saves the connector to a file
    void Load(ifstream& Infile, int& ID1, int& ID2);  // Loads the connector from a file
    int getCase();                      // Getter for the case number
};

#endif