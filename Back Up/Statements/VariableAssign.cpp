#include "VariableAssign.h"
#include <sstream>

/**
 * @brief Constructor for the VariableAssign class.
 *
 * The left-hand side (LHS) and right-hand side (RHS) should be validated
 * inside the (AddValueAssign) action before passing them to the constructor of VariableAssign.
 *
 * @param Lcorner The left corner of the statement block.
 * @param LeftHS The left-hand side of the assignment (variable name).
 * @param RightHS The right-hand side of the assignment (value).
 */
VariableAssign::VariableAssign(Point Lcorner, string LeftHS, string RightHS) : Statement(1, true)
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
 * @brief Set the left-hand side (LHS) of the assignment.
 * @param L The left-hand side variable name.
 */
void VariableAssign::setLHS(const string& L)
{
    LHS = L;
    UpdateStatementText();
}

/**
 * @brief Set the right-hand side (RHS) of the assignment.
 * @param R The right-hand side value.
 */
void VariableAssign::setRHS(const string& R)
{
    RHS = R;
    UpdateStatementText();
}

/**
 * @brief Draw the VariableAssign statement.
 * @param pOut Pointer to the output interface.
 */
void VariableAssign::Draw(Output* pOut) const
{
    // Call Output::DrawAssign function to draw the assignment statement
    pOut->DrawAssign(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);
}

/**
 * @brief Get the left corner of the statement block.
 * @return The left corner point.
 */
Point VariableAssign::getLeftCorner() const
{
    return LeftCorner;
}

/**
 * @brief Check if a point is inside the statement block.
 * @param position The point to check.
 * @return True if the point is inside the statement block, false otherwise.
 */
bool VariableAssign::ContainsPoint(Point position)
{
    if (position.x >= LeftCorner.x && position.x <= LeftCorner.x + UI.ASSGN_WDTH && position.y >= LeftCorner.y && position.y <= LeftCorner.y + UI.ASSGN_HI)
    {
        return true;
    }
    return false;
}

/**
 * @brief Save the statement to a file.
 * @param OutFile The output file stream.
 */
void VariableAssign::Save(ofstream& OutFile)
{
    OutFile << "VRBL_ASSIGN  " << ID << "  " << LeftCorner.x << "  " << LeftCorner.y << "  " << LHS << "  " << RHS << endl;
}

/**
 * @brief Load the statement from a file.
 * @param Infile The input file stream.
 */
void VariableAssign::Load(ifstream& Infile)
{
    Infile >> ID >> LeftCorner.x >> LeftCorner.y >> LHS >> RHS;
    SetOutlet();
    SetInlet();
    UpdateStatementText();
}

/**
 * @brief Set the outlet point for the statement.
 */
void VariableAssign::SetOutlet()
{
    Outlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
    Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}

/**
 * @brief Set the inlet point for the statement.
 */
void VariableAssign::SetInlet()
{
    Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
    Inlet.y = LeftCorner.y;
}

/**
 * @brief Update the text representation of the statement.
 *
 * This function should be called when LHS or RHS changes.
 */
void VariableAssign::UpdateStatementText()
{
    // Build the statement text: Left hand side then equals then right hand side
    ostringstream T;
    T << LHS << " = " << RHS;
    Text = T.str();
}

/**
 * @brief Set the drawing point for the statement.
 * @param P The new drawing point.
 */
void VariableAssign::SetDrawingPoint(Point P)
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
 * @brief Clone the VariableAssign statement.
 * @return A pointer to the cloned statement.
 */
Statement* VariableAssign::MakeCopy()
{
    Statement* Clone = new VariableAssign(Point(0, 0), ((VariableAssign*)this)->LHS, ((VariableAssign*)this)->RHS);
    return Clone;
}

/**
 * @brief Check and add the LeftHandSide (LHS) variable to the array of variables.
 * @param VariableArray The array of variables.
 * @param variableCount The count of variables in the array.
 * @return True if the variable was successfully added or already exists, false otherwise.
 */
bool VariableAssign::CheckVariables(string*& VariableArray, int& VariableCount)
{
    // Check if the variableCount is zero
    if (VariableCount == 0)
    {
        return false;
    }

    // Check if RHS is already in the array
    int existingIndex = -1;
    for (int i = 0; i < VariableCount; ++i)
    {
        if (VariableArray[i] == RHS)
        {
            existingIndex = i;
            break;
        }
    }

    // If RHS is not found, return false
    if (existingIndex == -1)
    {
        return false;
    }

    // Check if LHS is already in the array
    for (int i = 0; i < VariableCount; ++i)
    {
        if (VariableArray[i] == LHS)
        {
            return true; // LHS is already in the array, return true
        }
    }

    // LHS is not in the array, add it to the array
    string* tempArray = new string[VariableCount + 1];
    for (int i = 0; i < VariableCount; ++i)
    {
        tempArray[i] = VariableArray[i];
    }

    delete[] VariableArray;
    VariableArray = tempArray;
    VariableArray[VariableCount] = LHS;
    ++VariableCount;

    return true;
}

/**
 * @brief Simulate the execution of the statement.
 * @param pManager Pointer to the application manager.
 * @return True if the simulation was successful, false otherwise.
 */
bool VariableAssign::Simulate(ApplicationManager* pManager)
{
    double Value = pManager->ReturnValue(RHS);
    pManager->AddIntVariable(LHS, Value);
    return true;
}

/**
 * @brief Edit the properties of the VariableAssign statement.
 * @param pManager Pointer to the application manager.
 */
void VariableAssign::Edit(ApplicationManager* pManager)
{
    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();
    Point Position;

    // Read the (Position) parameter
    pOut->PrintMessage("Click to add the variable assign statement.");
    pIn->GetPointClicked(Position);
    pOut->ClearStatusBar();

    // Ask the user in the status bar to enter the LHS and set the data member
    pOut->PrintMessage("Please enter The LHS parameter");
    LHS = pIn->GetVariable(pOut);

    // Ask the user in the status bar to enter the RHS and set the data member
    pOut->PrintMessage("Please enter The RHS value");
    RHS = pIn->GetVariable(pOut);
    UpdateStatementText();
}
