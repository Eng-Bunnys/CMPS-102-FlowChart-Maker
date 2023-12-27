#include "Start.h"
#include <sstream>

/**
 * @brief Updates the text representation of the Start statement.
 *
 * Sets the Text property to "Start".
 */
void Start::UpdateStatementText()
{
    ostringstream T;
    T << "Start";
    Text = T.str();
}

/**
 * @brief Constructor for the Start statement.
 *
 * Initializes the Start statement with the given left corner.
 * @param Lcorner The left corner of the Start statement.
 */
Start::Start(Point Lcorner) : Statement(1, false)
{
    UpdateStatementText();

    LeftCorner = Lcorner;

    // No connectors yet
    SetOutlet();
    SetInlet();
}

/**
 * @brief Draws the Start statement on the output window.
 *
 * Calls the DrawStart function of the Output class to draw the Start statement.
 * @param pOut Pointer to the Output class for drawing.
 */
void Start::Draw(Output* pOut) const
{
    // Call Output::DrawStart function to draw the Start statement
    pOut->DrawStart(LeftCorner, UI.START_WDTH, UI.START_HI, "Start", Selected);
}

/**
 * @brief Gets the left corner of the Start statement.
 * @return The left corner of the Start statement.
 */
Point Start::getLeftCorner() const
{
    return LeftCorner;
}

/**
 * @brief Checks if a given point is inside the Start statement.
 * @param position The point to check.
 * @return True if the point is inside the Start statement, false otherwise.
 */
bool Start::ContainsPoint(Point position)
{
    if (position.x >= LeftCorner.x && position.x <= LeftCorner.x + UI.START_WDTH &&
        position.y >= LeftCorner.y && position.y <= LeftCorner.y + UI.START_HI)
    {
        return true;
    }
    return false;
}

/**
 * @brief Saves the Start statement to a file.
 *
 * Writes the Start statement details to the output file.
 * @param OutFile Output file stream.
 */
void Start::Save(ofstream& OutFile)
{
    OutFile << "START  " << ID << "  " << LeftCorner.x + (0.5) * UI.START_WDTH << "  " << LeftCorner.y << endl;
}

/**
 * @brief Loads the Start statement from a file.
 *
 * Reads the Start statement details from the input file.
 * @param Infile Input file stream.
 */
void Start::Load(ifstream& Infile)
{
    Point P;
    Infile >> ID >> P.x >> P.y;
    CenterToLeftCorner(P);
    SetOutlet();
    SetInlet();
}

/**
 * @brief Calculates the left corner based on the center of the Start statement.
 * @param C The center of the Start statement.
 */
void Start::CenterToLeftCorner(Point C)
{
    LeftCorner.x = C.x - (0.5) * UI.START_WDTH;
    LeftCorner.y = C.y;
}

/**
 * @brief Sets the outlet point for the Start statement.
 */
void Start::SetOutlet()
{
    Outlet.x = LeftCorner.x + UI.START_WDTH / 2;
    Outlet.y = LeftCorner.y + UI.START_HI;
}

/**
 * @brief Sets the inlet point for the Start statement.
 */
void Start::SetInlet()
{
    Inlet.x = -1;
    Inlet.y = -1;
}

/**
 * @brief Sets the drawing point for the Start statement.
 *
 * @param P The drawing point for the Start statement.
 */
void Start::SetDrawingPoint(Point P)
{
    LeftCorner = P;
    LeftCorner.x = P.x - UI.START_WDTH / 2;
    LeftCorner.y = P.y;
    Outlet.x = LeftCorner.x + UI.START_WDTH / 2;
    Outlet.y = LeftCorner.y + (1.07 * UI.START_HI);
}

/**
 * @brief Clones the Start statement.
 * @return A new instance of the Start statement.
 */
Statement* Start::MakeCopy()
{
    Statement* Clone = new Start(Point(0, 0));
    return Clone;
}

/**
 * @brief Checks if the Start statement contains valid variables.
 *
 * Since Start statement does not contain variables, always returns false.
 * @param arr Array of variables.
 * @param c Number of variables.
 * @return Always false.
 */
bool Start::CheckVariables(string*& arr, int& c)
{
    return false;
}

/**
 * @brief Simulates the Start statement.
 *
 * Since Start statement does not have any simulation logic, always returns false.
 * @param pManager Pointer to the ApplicationManager.
 * @return Always false.
 */
bool Start::Simulate(ApplicationManager* pManager)
{
    return false;
}

/**
 * @brief Edits the Start statement.
 *
 * Since Start statement does not have any editable properties, does nothing.
 * @param pManager Pointer to the ApplicationManager.
 */
void Start::Edit(ApplicationManager* pManager)
{
    // No editable properties for the Start statement
    return;
}