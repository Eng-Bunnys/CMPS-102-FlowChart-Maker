/// There are some issues with this code that I have no idea on how to fix
/*
1. If a user chooses Conditional that is above the End and tries to link both the arrow will point to nothing but it will think it is pointing to the end statement
2. Conditional is super buggy with connections for some reason, sometimes the connector goes through it
*/
#include "Connector.h"
#include "ConditionalStatement.h"
#include "../GUI/Output.h"
#include <fstream>

/**
 * @brief Checks if a value is within a specified range.
 * @param value - The value to check.
 * @param target - The target value.
 * @param tolerance - The allowed tolerance range (default is 2.0).
 * @return True if the value is within the specified range, false otherwise.
 */
bool isWithinRange(double value, double target, double tolerance = 2.0) {
	return value >= target - tolerance && value <= target + tolerance;
}

/**
 * @brief Checks if a point is within a vertical range between two other points.
 * @param P - The point to check.
 * @param start - The start point of the range.
 * @param end - The end point of the range.
 * @param tolerance - The allowed tolerance range (default is 2.0).
 * @return True if the point is within the vertical range, false otherwise.
 */
bool isWithinVerticalRange(Point P, Point start, Point end, double tolerance = 2.0) {
	return isWithinRange(P.x, start.x, tolerance) && P.y >= start.y && P.y <= end.y;
}

/**
 * @brief Checks if a point is within a horizontal range between two other points.
 * @param P - The point to check.
 * @param start - The start point of the range.
 * @param end - The end point of the range.
 * @param tolerance - The allowed tolerance range (default is 2.0).
 * @return True if the point is within the horizontal range, false otherwise.
 */
bool isWithinHorizontalRange(Point P, Point start, Point end, double tolerance = 2.0) {
	return isWithinRange(P.y, start.y, tolerance) && P.x >= start.x && P.x <= end.x;
}

/**
 * @brief Checks if a point is within a triangle defined by the target point.
 * @param P - The point to check.
 * @param end - The target point of the triangle.
 * @param tolerance - The allowed tolerance range (default is 5.0).
 * @return True if the point is within the triangle, false otherwise.
 */
bool isWithinTriangle(Point P, Point end, double tolerance = 5.0) {
	return isWithinRange(P.x, end.x, tolerance) && isWithinRange(P.y, end.y, tolerance);
}

Connector::Connector(Statement* Src, Statement* Dst, int CurrentCase)
{
	Case = CurrentCase;
	SrcStat = Src;
	DstStat = Dst;
	Selected = false;
	Point P;
	P.x = 0; P.y = 0;
	setStartAndEnd();
}

/**
 * @brief Sets the source statement of the connector.
 * @param Src - The source statement to set.
 */
void Connector::setSrcStat(Statement* Src)
{
    SrcStat = Src;
}

/**
 * @brief Gets the source statement of the connector.
 * @return The source statement of the connector.
 */
Statement* Connector::getSrcStat() const
{
    return SrcStat;
}

/**
 * @brief Sets the destination statement of the connector.
 * @param Dst - The destination statement to set.
 */
void Connector::setDstStat(Statement* Dst)
{
    DstStat = Dst;
}

/**
 * @brief Gets the destination statement of the connector.
 * @return The destination statement of the connector.
 */
Statement* Connector::getDstStat()
{
    return DstStat;
}

/**
 * @brief Sets the start and end points of the connector based on the current case.
 */
void Connector::setStartAndEnd()
{
    if (Case == 2)
        setStartPoint(((Conditional*)SrcStat)->getFalseOutlet());
    else
        setStartPoint(SrcStat->GetOutlet());

    setEndPoint(DstStat->GetInlet());
}

/**
 * @brief Sets the start point of the connector.
 * @param P - The point to set as the start point.
 */
void Connector::setStartPoint(Point P)
{
    Start = P;
}

/**
 * @brief Gets the start point of the connector.
 * @return The start point of the connector.
 */
Point Connector::getStartPoint()
{
    return Start;
}

/**
 * @brief Sets the end point of the connector.
 * @param P - The point to set as the end point.
 */
void Connector::setEndPoint(Point P)
{
    End = P;
}

/**
 * @brief Gets the end point of the connector.
 * @return The end point of the connector.
 */
Point Connector::getEndPoint()
{
    return End;
}

/**
 * @brief Draws the connector using the specified output object.
 * @param pOut - The output object used for drawing.
 */
void Connector::Draw(Output* pOut) const
{
    pOut->DrawConnector(Start, End, Selected);
}

/**
 * @brief Sets the selected state of the connector.
 * @param CurrentSelected - The selected state to set.
 */
void Connector::SetSelected(bool CurrentSelected)
{
    Selected = CurrentSelected;
}

/**
 * @brief Checks if the connector is selected.
 * @return True if the connector is selected, false otherwise.
 */
bool Connector::IsSelected() const
{
    return Selected;
}

/**
 * @brief Checks if a point is within the connector.
 * @param P - The point to check.
 * @return True if the point is within the connector, false otherwise.
 */
bool Connector::isInConnector(Point P)
{
    if (Case == 0 || Case == 1 || Case == 2)
    {
        if (isWithinVerticalRange(P, Start, End) || isWithinHorizontalRange(P, Start, End))
            return true;

        if (isWithinTriangle(P, End))
            return true;

        return false;
    }

    return false;
}

/**
 * @brief Sets the case of the connector.
 * @param CurrentCase - The case to set.
 */
void Connector::SetCase(int CurrentCase)
{
    if (CurrentCase == 0 || CurrentCase == 1 || CurrentCase == 2)
    {
        Case = CurrentCase;
    }
}

/**
 * @brief Saves the connector to an output file stream.
 * @param OutFile - The output file stream.
 */
void Connector::Save(ofstream& OutFile)
{
    OutFile << SrcStat->GetID() << "  " << DstStat->GetID() << "  " << Case << endl;
}

/**
 * @brief Loads the connector from an input file stream.
 * @param Infile - The input file stream.
 * @param ID1 - The first ID.
 * @param ID2 - The second ID.
 */
void Connector::Load(ifstream& Infile, int& ID1, int& ID2)
{
    Infile >> ID1 >> ID2 >> Case;
}

/**
 * @brief Gets the case of the connector.
 * @return The case of the connector.
 */
int Connector::getCase()
{
    return Case;
}