#include "Read.h"
#include <sstream>

/**
 * @brief Constructs a Read object with the given parameters.
 *
 * @param Lcorner The left corner of the Read statement.
 * @param rVariable The variable to be read.
 */
Read::Read(Point Lcorner, string rVariable) : Statement(1, true)
{
    // Note: The LeftHS and RightHS should be validated inside (AddValueAssign) action
    // before passing it to the constructor of ValueAssign
    Variable = rVariable;

    UpdateStatementText();

    LeftCorner = Lcorner;

    // No connectors yet

    SetOutlet();
    SetInlet();
}

/**
 * @brief Sets the variable to be read.
 *
 * @param rVariable The variable to be read.
 */
void Read::setVariable(const string& rVariable)
{
    Variable = rVariable;
    UpdateStatementText();
}

/**
 * @brief Draws the Read statement on the output.
 *
 * @param pOut Pointer to the Output class for drawing.
 */
void Read::Draw(Output* pOut) const
{
    // Call Output::DrawAssign function to draw the Read statement
    pOut->DrawRead(LeftCorner, UI.IO_WDTH, UI.IO_HI, Text, Selected);
}

/**
 * @brief Gets the left corner of the Read statement.
 *
 * @return Point representing the left corner of the Read statement.
 */
Point Read::getLeftCorner() const
{
    return LeftCorner;
}

/**
 * @brief Checks if a given point is within the Read statement.
 *
 * @param position The point to check.
 * @return True if the point is within the Read statement, false otherwise.
 */
bool Read::ContainsPoint(Point position)
{
    if (position.x >= LeftCorner.x && position.x <= LeftCorner.x + (1.1) * UI.IO_WDTH && position.y >= LeftCorner.y && position.y <= LeftCorner.y + UI.IO_HI) {
        return true;
    }
    return false;
}

/**
 * @brief Saves the Read statement to the output file.
 *
 * @param OutFile The output file stream.
 */
void Read::Save(ofstream& OutFile)
{
    OutFile << "READ" << "  " << ID << "  " << LeftCorner.x << "  " << LeftCorner.y << "  " << Variable << endl;
}

/**
 * @brief Loads a Read statement from the input file.
 *
 * @param Infile The input file stream.
 */
void Read::Load(ifstream& Infile)
{
    Infile >> ID >> LeftCorner.x >> LeftCorner.y >> Variable;
    SetOutlet();
    SetInlet();
    UpdateStatementText();
}

/**
 * @brief Sets the outlet point of the Read statement.
 */
void Read::SetOutlet()
{
    Outlet.x = LeftCorner.x + UI.IO_WDTH / 2;
    Outlet.y = LeftCorner.y + UI.IO_HI;
}

/**
 * @brief Sets the inlet point of the Read statement.
 */
void Read::SetInlet()
{
    Inlet.x = LeftCorner.x + UI.IO_WDTH / 2;
    Inlet.y = LeftCorner.y;
}

/**
 * @brief Updates the text representation of the Read statement.
 */
void Read::UpdateStatementText()
{
    // Build the statement text: Read followed by the variable name
    ostringstream T;
    T << "Read " << Variable;
    Text = T.str();
}

/**
 * @brief Sets the drawing point for the Read statement.
 *
 * @param P The new drawing point.
 */
void Read::SetDrawingPoint(Point P)
{
    LeftCorner = P;
    LeftCorner.x = P.x - UI.IO_WDTH / 2;
    LeftCorner.y = P.y;
    Inlet.x = LeftCorner.x + UI.IO_WDTH / 2;
    Inlet.y = LeftCorner.y;

    Outlet.x = Inlet.x;
    Outlet.y = LeftCorner.y + UI.IO_HI;
}

/**
 * @brief Clones the Read statement.
 *
 * @return A cloned instance of the Read statement.
 */
Statement* Read::MakeCopy()
{
    Statement* Clone = new Read(Point(0, 0), ((Read*)this)->Variable);
    return Clone;
}

/**
 * @brief Checks the variables used in the Read statement.
 *
 * @param arr An array of variable names.
 * @param c The count of variables.
 * @return True if the variables are valid, false otherwise.
 */
bool Read::CheckVariables(string*& arr, int& c)
{
    if (c == 0)
    {
        arr[0] = Variable;
        c++;
        return true;
    }
    for (int i = 0; i < c; i++)
    {
        if (arr[i] == Variable)
        {
            return true;
        }
    }
    string* temp = new string[c + 1];
    for (int i = 0; i < c; i++)
    {
        temp[i] = arr[i];
    }
    delete[] arr;
    arr = temp;
    arr[c] = Variable;
    c++;
    return true;
}

/**
 * @brief Simulates the Read statement.
 *
 * @param pManager Pointer to the ApplicationManager.
 * @return True if the simulation is successful, false otherwise.
 */
bool Read::Simulate(ApplicationManager* pManager)
{
    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();
    double V = pIn->GetValue(pOut);

    pManager->AddIntVariable(Variable, V);
    return true;
}

/**
 * @brief Edits the Read statement.
 *
 * @param pManager Pointer to the ApplicationManager.
 */
void Read::Edit(ApplicationManager* pManager)
{
    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();
    Point Position;
    // Read the (Position) parameter
    pOut->PrintMessage("Read Assignment Statement: Click to add the statement");

    pIn->GetPointClicked(Position);
    pOut->ClearStatusBar();

    // Ask the user to enter the variable to be read
    pOut->PrintMessage("Please enter the variable to be read");
    Variable = pIn->GetVariable(pOut);
    UpdateStatementText();
}