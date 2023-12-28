#include "ValueAssign.h"
#include <sstream>
#include "..\ApplicationManager.h"
using namespace std;

/**
 * @brief Constructor for the ValueAssign class.
 * @param Lcorner The left corner of the assignment statement block.
 * @param LeftHS The left-hand side (LHS) of the assignment statement.
 * @param RightHS The right-hand side (RHS) of the assignment statement.
 */
ValueAssign::ValueAssign(Point Lcorner, string LeftHS, double RightHS) : Statement(1, true)
{
    LHS = LeftHS;
    RHS = RightHS;

    UpdateStatementText();

    LeftCorner = Lcorner;

    // No connectors yet
    SetOutlet();
    SetInlet();
}

/**
 * @brief Set the left-hand side (LHS) of the assignment statement.
 * @param L The value to set as the LHS.
 */
void ValueAssign::setLHS(const string& L)
{
    LHS = L;
    UpdateStatementText();
}

/**
 * @brief Set the right-hand side (RHS) of the assignment statement.
 * @param R The value to set as the RHS.
 */
void ValueAssign::setRHS(double R)
{
    RHS = R;
    UpdateStatementText();
}

/**
 * @brief Draw the ValueAssign statement.
 * @param pOut Pointer to the Output object for drawing.
 */
void ValueAssign::Draw(Output* pOut) const
{
    // Call Output::DrawAssign function to draw assignment statement
    pOut->DrawAssign(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);
}

/**
 * @brief Get the left corner of the assignment statement.
 * @return Point representing the left corner.
 */
Point ValueAssign::getLeftCorner() const
{
    return LeftCorner;
}

/**
 * @brief Check if a given point is inside the assignment statement.
 * @param position The point to check.
 * @return True if the point is inside the statement, false otherwise.
 */
bool ValueAssign::ContainsPoint(Point position)
{
    if (position.x >= LeftCorner.x && position.x <= LeftCorner.x + UI.ASSGN_WDTH &&
        position.y >= LeftCorner.y && position.y <= LeftCorner.y + UI.ASSGN_HI) {
        return true;
    }
    return false;
}

/**
 * @brief Save the ValueAssign statement parameters to a file.
 * @param OutFile The output file stream.
 */
void ValueAssign::Save(ofstream& OutFile)
{
    OutFile << "VALUE_ASSIGN  " << ID << "  " << LeftCorner.x << "  " << LeftCorner.y << "  " << LHS << "  " << RHS << endl;
}

/**
 * @brief Load the ValueAssign statement parameters from a file.
 * @param Infile The input file stream.
 */
void ValueAssign::Load(ifstream& Infile)
{
    Infile >> ID >> LeftCorner.x >> LeftCorner.y >> LHS >> RHS;
    SetOutlet();
    SetInlet();
    UpdateStatementText();
}

/**
 * @brief Set the outlet point of the statement.
 */
void ValueAssign::SetOutlet()
{
    Outlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
    Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}

/**
 * @brief Set the inlet point of the statement.
 */
void ValueAssign::SetInlet()
{
    Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
    Inlet.y = LeftCorner.y;
}

/**
 * @brief Update the statement text based on the LHS and RHS.
 *
 * This function should be called when LHS or RHS changes.
 */
void ValueAssign::UpdateStatementText()
{
    // Build the statement text: Left hand side then equals then right hand side
    ostringstream T;
    T << LHS << " = " << RHS;
    Text = T.str();
}

/**
 * @brief Set the drawing point of the statement.
 * @param P The new drawing point.
 */
void ValueAssign::SetDrawingPoint(Point P)
{
    LeftCorner = P;
    LeftCorner.x = P.x - UI.ASSGN_WDTH / 2;
    LeftCorner.y = P.y;

    Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
    Inlet.y = LeftCorner.y;

    Outlet.x = Inlet.x;
    Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}

/**
 * @brief Clone the ValueAssign statement.
 * @return A pointer to the cloned statement.
 */
Statement* ValueAssign::MakeCopy()
{
    Statement* Clone = new ValueAssign(Point(0, 0), ((ValueAssign*)this)->LHS, ((ValueAssign*)this)->RHS);
    return Clone;
}

/**
 * @brief Check and add the LHS variable to the array of variables.
 * @param arr The array of variables.
 * @param c The count of variables in the array.
 * @return True if the variable was successfully added, false otherwise.
 */
bool ValueAssign::CheckVariables(string*& VariableArray, int& VariableCount)
{
    // If the array is empty, add the LHS variable and increment the count
    if (VariableCount == 0)
    {
        VariableArray[0] = LHS;
        VariableCount++;
        return true;
    }

    // Check if the LHS variable already exists in the array
    for (int i = 0; i < VariableCount; i++)
    {
        if (VariableArray[i] == LHS)
        {
            return true; // LHS variable already exists, no need to add
        }
    }

    // Create a new array with increased size, copy the existing elements, add the LHS variable, and increment the count
    string* TempArray = new string[VariableCount + 1];
    for (int i = 0; i < VariableCount; i++)
    {
        TempArray[i] = VariableArray[i];
    }
    TempArray[VariableCount] = LHS;

    // Cleanup the old array and update the VariableArray pointer
    delete[] VariableArray;
    VariableArray = TempArray;

    VariableCount++;

    return true; // LHS variable added successfully
}

/**
 * @brief Simulate the ValueAssign statement.
 *
 * Adds the LHS variable with the assigned RHS value to the ApplicationManager's
 * list of integer variables.
 * @param pManager Pointer to the ApplicationManager.
 * @return True if the simulation was successful, false otherwise.
 */
bool ValueAssign::Simulate(ApplicationManager* pManager)
{
    pManager->AddIntVariable(LHS, RHS);
    return true;
}

/**
 * @brief Edit the ValueAssign statement.
 *
 * Prompts the user to click on the flowchart to place the statement,
 * and then prompts the user to enter the left-hand side (LHS) and
 * right-hand side (RHS) of the assignment statement.
 * @param pManager Pointer to the ApplicationManager.
 */
void ValueAssign::Edit(ApplicationManager* pManager)
{
    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();
    Point Position;

    // Prompt user to click on the flowchart to place the Value Assignment statement
    pOut->PrintMessage("Click to edit the value assign statement.");
    pIn->GetPointClicked(Position);
    pOut->ClearStatusBar();

    // Prompt the user in the status bar to enter the LHS and set the data member
    pOut->PrintMessage("Enter the left-hand side (LHS) of the assignment statement:");
    LHS = pIn->GetVariable(pOut);

    // Prompt the user in the status bar to enter the RHS and set the data member
    pOut->PrintMessage("Enter the right-hand side (RHS) of the assignment statement:");
    RHS = pIn->GetValue(pOut);
    pOut->ClearStatusBar();
    UpdateStatementText();
}