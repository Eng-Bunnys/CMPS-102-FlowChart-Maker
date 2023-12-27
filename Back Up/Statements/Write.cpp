#include "Write.h"
#include <sstream>

/**
 * @brief Constructs a Write object with the given parameters.
 *
 * @param Lcorner The left corner of the Write statement.
 * @param rVariable The variable or message to be written.
 */
Write::Write(Point Lcorner, string rVariable) : Statement(1, true)
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
 * @brief Sets the variable or message to be written.
 *
 * @param rVariable The variable or message to be written.
 */
void Write::setVariable(const string& rVariable)
{
    Variable = rVariable;
    UpdateStatementText();
}

/**
 * @brief Draws the Write statement on the output.
 *
 * @param pOut Pointer to the Output class for drawing.
 */
void Write::Draw(Output* pOut) const
{
    // Call Output::DrawAssign function to draw assignment statement
    pOut->DrawWrite(LeftCorner, UI.IO_WDTH, UI.IO_HI, Text, Selected);
}

/**
 * @brief Gets the left corner of the Write statement.
 *
 * @return Point representing the left corner of the Write statement.
 */
Point Write::getLeftCorner() const
{
    return LeftCorner;
}

/**
 * @brief Checks if a given point is within the Write statement.
 *
 * @param position The point to check.
 * @return True if the point is within the Write statement, false otherwise.
 */
bool Write::ContainsPoint(Point position)
{
    if (position.x >= LeftCorner.x && position.x <= LeftCorner.x + (1.1) * UI.IO_WDTH && position.y >= LeftCorner.y && position.y <= LeftCorner.y + UI.IO_HI) {
        return true;
    }
    return false;
}

/**
 * @brief Saves the Write statement to the output file.
 *
 * @param OutFile The output file stream.
 */
void Write::Save(ofstream& OutFile)
{
    OutFile << "WRITE  " << ID << "  " << LeftCorner.x << "  " << LeftCorner.y << "  " << Variable << endl;
}

/**
 * @brief Loads a Write statement from the input file.
 *
 * @param Infile The input file stream.
 */
void Write::Load(ifstream& Infile)
{
    Infile >> ID >> LeftCorner.x >> LeftCorner.y >> Variable;
    SetOutlet();
    SetInlet();
    UpdateStatementText();
}

/**
 * @brief Sets the outlet point of the Write statement.
 */
void Write::SetOutlet()
{
    Outlet.x = LeftCorner.x + UI.IO_WDTH / 2;
    Outlet.y = LeftCorner.y + UI.IO_WDTH;
}

/**
 * @brief Sets the inlet point of the Write statement.
 */
void Write::SetInlet()
{
    Inlet.x = LeftCorner.x + UI.IO_WDTH / 2;
    Inlet.y = LeftCorner.y;
}

/**
 * @brief Updates the text representation of the Write statement.
 */
void Write::UpdateStatementText()
{
    // Build the statement text: Write followed by the variable or message
    ostringstream T;
    T << "Write " << Variable;
    Text = T.str();
}

/**
 * @brief Sets the drawing point for the Write statement.
 *
 * @param P The new drawing point.
 */
void Write::SetDrawingPoint(Point P)
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
 * @brief Clones the Write statement.
 *
 * @return A cloned instance of the Write statement.
 */
Statement* Write::MakeCopy()
{
    Statement* Clone = new Write(Point(0, 0), ((Write*)this)->Variable);
    return Clone;
}

/**
 * @brief Checks the variables used in the Write statement.
 *
 * @param arr An array of variable names.
 * @param c The count of variables.
 * @return True if the variables are valid, false otherwise.
 */
bool Write::CheckVariables(string*& arr, int& c)
{
    if (Variable[0] == '"')
        return true;
    else
    {
        if (c == 0)
        {
            return false;
        }
        for (int i = 0; i < c; i++)
        {
            if (Variable == arr[i])
                return true;
        }
    }
    return false;
}

/**
 * @brief Simulates the Write statement.
 *
 * @param pManager Pointer to the ApplicationManager.
 * @return True if the simulation is successful, false otherwise.
 */
bool Write::Simulate(ApplicationManager* pManager)
{
    static int y = UI.ToolBarHeight + 10;
    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();
    string Var;
    int x;
    x = UI.DrawingAreaWidth + ((UI.width - UI.DrawingAreaWidth) / 2);

    if (Variable[0] != '"')
    {
        Var = Variable + " = " + to_string(pManager->ReturnValue(Variable));
        pOut->DrawString(x, y, Var);
    }
    else
    {
        pOut->DrawString(x, y, Variable);
    }
    y += 10;
    return true;
}

/**
 * @brief Edits the Write statement.
 *
 * @param pManager Pointer to the ApplicationManager.
 */
void Write::Edit(ApplicationManager* pManager)
{
    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();
    Point Position;
    // Read the (Position) parameter
    pOut->PrintMessage("Write Statement: Click to add the statement");

    pIn->GetPointClicked(Position);
    pOut->ClearStatusBar();

    // Ask the user to enter the variable or the message to be written
    pOut->PrintMessage("Please enter the variable or the message to be written ");
    Variable = pIn->GetString(pOut);
    while (!IsVariable(Variable) && (Variable[0] != '"' || Variable[Variable.length() - 1] != '"')) {
        pOut->PrintMessage("Please enter a valid variable or a valid message to be written ");
        Variable = pIn->GetString(pOut);
    }
    setVariable(Variable);
    UpdateStatementText();
}