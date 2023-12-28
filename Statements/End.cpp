#include "End.h"
#include <sstream>

using namespace std;

/**
 * @brief Updates the text representation of the End statement.
 *
 * Sets the Text property to "End".
 */
void End::UpdateStatementText()
{
    ostringstream T;
    T << "End";
    Text = T.str();
}

/**
 * @brief Constructor for the End statement.
 *
 * Initializes the End statement with the given left corner.
 * @param Lcorner The left corner of the End statement.
 */
End::End(Point Lcorner) : Statement(0, true)
{
    UpdateStatementText();

    LeftCorner = Lcorner;

    SetOutlet();
    SetInlet();
}

/**
 * @brief Draws the End statement on the output window.
 *
 * Calls the DrawEnd function of the Output class to draw the End statement.
 * @param pOut Pointer to the Output class for drawing.
 */
void End::Draw(Output* pOut) const
{
    pOut->DrawEnd(LeftCorner, UI.START_WDTH, UI.START_HI, "End", Selected);
}

/**
 * @brief Gets the left corner of the End statement.
 * @return The left corner of the End statement.
 */
Point End::getLcorner() const
{
    return LeftCorner;
}

/**
 * @brief Checks if a given point is inside the End statement.
 * @param position The point to check.
 * @return True if the point is inside the End statement, false otherwise.
 */
bool End::ContainsPoint(Point position)
{
    if (position.x >= LeftCorner.x && position.x <= LeftCorner.x + UI.START_WDTH &&
        position.y >= LeftCorner.y && position.y <= LeftCorner.y + UI.START_HI)
    {
        return true;
    }
    return false;
}

/**
 * @brief Saves the End statement to a file.
 *
 * Writes the End statement details to the output file.
 * @param OutFile Output file stream.
 */
void End::Save(ofstream& OutFile)
{
    OutFile << "END  " << ID << "  " << LeftCorner.x + (0.5) * UI.START_WDTH << "  " << LeftCorner.y << endl;
}

/**
 * @brief Loads the End statement from a file.
 *
 * Reads the End statement details from the input file.
 * @param Infile Input file stream.
 */
void End::Load(ifstream& Infile)
{
    Point P;
    Infile >> ID >> P.x >> P.y;
    CenterToLeftCorner(P);
    SetOutlet();
    SetInlet();
}

/**
 * @brief Calculates the left corner based on the center of the End statement.
 * @param C The center of the End statement.
 */
void End::CenterToLeftCorner(Point C)
{
    LeftCorner.x = C.x - (0.5) * UI.START_WDTH;
    LeftCorner.y = C.y;
}

/**
 * @brief Sets the outlet point for the End statement.
 */
void End::SetOutlet()
{
    Outlet.x = -1;
    Outlet.y = -1;
}

/**
 * @brief Sets the inlet point for the End statement.
 */
void End::SetInlet()
{
    Inlet.x = LeftCorner.x + UI.START_WDTH / 2;
    Inlet.y = LeftCorner.y;
}

/**
 * @brief Sets the drawing point for the End statement.
 *
 * @param P The drawing point for the End statement.
 */
void End::SetDrawingPoint(Point P)
{
    LeftCorner = P;
    LeftCorner.x = P.x - UI.START_WDTH / 2;
    LeftCorner.y = P.y;
    Inlet.x = LeftCorner.x + UI.START_WDTH / 2;
    Inlet.y = LeftCorner.y - (0.07 * UI.START_HI);
}

/**
 * @brief Clones the End statement.
 * @return A new instance of the End statement.
 */
Statement* End::MakeCopy()
{
    Statement* Clone = new End(Point(0, 0));
    return Clone;
}

/**
 * @brief Checks if the End statement contains valid variables.
 *
 * Since End statement does not contain variables, always returns true.
 * @param arr Array of variables.
 * @param c Number of variables.
 * @return Always true.
 */
bool End::CheckVariables(string*& arr, int& c)
{
    return true;
}

/**
 * @brief Simulates the End statement.
 *
 * Since End statement does not have any simulation logic, always returns true.
 * @param pManager Pointer to the ApplicationManager.
 * @return Always true.
 */
bool End::Simulate(ApplicationManager* pManager)
{
    return true;
}

/**
 * @brief Edits the End statement.
 *
 * Since End statement does not have any editable properties, does nothing.
 * @param pManager Pointer to the ApplicationManager.
 */
void End::Edit(ApplicationManager* pManager)
{
    // No editable properties for the End statement
    return;
}