#include <sstream>
#include "ConditionalStatement.h"
using namespace std;

/**
 * @brief Constructor for Conditional class
 *
 * @param Lcorner The left corner point of the conditional statement
 * @param LeftHS The left-hand side of the conditional expression
 * @param rComparator The relational comparator (e.g., >, <, ==)
 * @param RightHS The right-hand side of the conditional expression
 */
Conditional::Conditional(Point Lcorner, string LeftHS, string rComparator, string RightHS) : Statement(2, true)
{
    LHS = LeftHS;
    RHS = RightHS;
    Comparator = rComparator;

    UpdateStatementText();

    LeftCorner = Lcorner;

    SetOutlet();
    SetInlet();
}

/**
 * @brief Setter for LHS
 *
 * @param L The new value for the left-hand side
 */
void Conditional::setLHS(const string& L)
{
    LHS = L;
    UpdateStatementText();
}

/**
 * @brief Setter for RHS
 *
 * @param R The new value for the right-hand side
 */
void Conditional::setRHS(const string& R)
{
    RHS = R;
    UpdateStatementText();
}

/**
 * @brief Setter for Comparator
 *
 * @param C The new value for the comparator (e.g., >, <, ==)
 */
void Conditional::setComparator(const string& C)
{
    Comparator = C;
    UpdateStatementText();
}

/**
 * @brief Getter for the left corner
 *
 * @return Point The left corner point of the conditional statement
 */
Point Conditional::getLeftCorner() const
{
    return LeftCorner;
}

/**
 * @brief Getter for false outlet
 *
 * @return Point The false outlet point of the conditional statement
 */
Point Conditional::getFalseOutlet()
{
    if (this)
    {
        return OutletF;
    }
    else
    {
        return Point(0, 0);
    }
}

/**
 * @brief Draw function to display the Conditional statement
 *
 * @param pOut Pointer to the output object used for drawing
 */
void Conditional::Draw(Output* pOut) const
{
    // Call Output::DrawConditionalStat function to draw the conditional statement
    pOut->DrawConditionalStat(LeftCorner, UI.COND_WDTH, UI.COND_HI, Text, Selected);
}

/**
 * @brief Check if a point is inside the Conditional statement
 *
 * @param position The point to check
 * @return true if the point is inside the conditional statement, false otherwise
 */
bool Conditional::ContainsPoint(Point position)
{
    if (position.x >= LeftCorner.x && position.x <= LeftCorner.x + UI.COND_WDTH &&
        position.y >= LeftCorner.y - UI.COND_HI / 2 && position.y <= LeftCorner.y + UI.COND_HI / 2)
    {
        return true;
    }
    return false;
}

/**
 * @brief Load Conditional statement from file
 *
 * @param Infile Input file stream
 */
void Conditional::Load(ifstream& Infile)
{
    Point P;
    string S;
    Infile >> ID >> P.x >> P.y >> LHS >> S >> RHS;
    CenterToLeftCorner(P);
    ReversegetOperator(S);
    SetOutlet();
    SetInlet();
    UpdateStatementText();
}

/**
 * @brief Calculate left corner based on center
 *
 * @param C The center point of the conditional statement
 */
void Conditional::CenterToLeftCorner(Point C)
{
    LeftCorner.x = C.x - (0.5) * UI.COND_WDTH;
    LeftCorner.y = C.y - (0.5) * UI.COND_HI;
}

/**
 * @brief Set outlets and inlets for the Conditional statement
 */
void Conditional::SetOutlet()
{
    OutletF.x = LeftCorner.x;
    OutletF.y = LeftCorner.y;

    Outlet.x = LeftCorner.x + UI.COND_WDTH;
    Outlet.y = LeftCorner.y;
}

/**
 * @brief Set inlets for the Conditional statement
 */
void Conditional::SetInlet()
{
    Inlet.x = LeftCorner.x + UI.COND_WDTH / 2;
    Inlet.y = LeftCorner.y - UI.COND_HI / 2;
}

/**
 * @brief Update the text representation of the Conditional statement
 */
void Conditional::UpdateStatementText()
{
    // Build the statement text: Left-hand side, then comparator, then right-hand side
    ostringstream T;
    T << LHS << Comparator << RHS;
    Text = T.str();
}

/**
 * @brief Save Conditional statement to file
 *
 * @param OutFile Output file stream
 */
void Conditional::Save(ofstream& OutFile)
{
    string opr = getOperator();
    OutFile << "COND  " << ID << "  " << LeftCorner.x + (0.5) * UI.COND_WDTH << "  " << LeftCorner.y + (0.5) * UI.COND_HI << "  " << LHS << "  " << opr << "  " << RHS << endl;
}

/**
 * @brief Get the operator for saving
 *
 * @return string The operator in string form
 */
string Conditional::getOperator()
{
    if (Comparator == ">")
    {
        return "GRT";
    }
    else if (Comparator == "<")
    {
        return "SML";
    }
    else if (Comparator == ">=")
    {
        return "GRTEQL";
    }
    else if (Comparator == "<=")
    {
        return "SMLEQL";
    }
    else if (Comparator == "==")
    {
        return "EQL";
    }
    else
    {
        return "NOTEQL";
    }
}

/**
 * @brief Reverse the operator for loading
 *
 * @param S The operator in string form
 */
void Conditional::ReversegetOperator(string S)
{
    if (S == "GRT")
    {
        Comparator = ">";
    }
    else if (S == "SML")
    {
        Comparator = "<";
    }
    else if (S == "GRTEQL")
    {
        Comparator = ">=";
    }
    else if (S == "SMLEQL")
    {
        Comparator = "<=";
    }
    else if (S == "EQL")
    {
        Comparator = "==";
    }
    else
    {
        Comparator = "!=";
    }
}

/**
 * @brief Clone the Conditional statement
 *
 * @return Statement* A dynamically allocated clone of the conditional statement
 */
Statement* Conditional::MakeCopy()
{
    Statement* clone = new Conditional(Point(0, 0), ((Conditional*)this)->LHS, ((Conditional*)this)->RHS, ((Conditional*)this)->Comparator);
    return clone;
}

/**
 * @brief Set the drawing point for the Conditional statement
 *
 * @param P The new drawing point
 */
void Conditional::SetDrawingPoint(Point P)
{
    LeftCorner = P;
    LeftCorner.x = P.x - UI.COND_WDTH / 2;
    LeftCorner.y = P.y + UI.COND_HI / 2;

    SetOutlet();
    SetInlet();
}

/**
 * @brief Check if the variable is present in the array
 *
 * @param variableArray Array of variables to check
 * @param arraySize Size of the variable array
 * @param targetVariable The variable to check for
 * @return true if the variable is present, false otherwise
 */
bool ContainsVariable(string*& variableArray, const int& arraySize, const string& targetVariable)
{
    for (int i = 0; i < arraySize; ++i)
    {
        if (variableArray[i] == targetVariable)
        {
            return true;
        }
    }

    return false;
}

/**
 * @brief Check if the variables in the Conditional statement are valid
 *
 * @param variableArray Array of variables to check
 * @param arraySize Size of the variable array
 * @return true if the variables are valid, false otherwise
 */
bool Conditional::CheckVariables(string*& variableArray, int& arraySize)
{
    if (arraySize == 0)
    {
        return false;
    }

    if (IsVariable(LHS) && !ContainsVariable(variableArray, arraySize, LHS))
    {
        return false;
    }

    if (IsVariable(RHS) && !ContainsVariable(variableArray, arraySize, RHS))
    {
        return false;
    }

    return true;
}

/**
 * @brief Simulate the Conditional statement
 *
 * @param pManager Pointer to the ApplicationManager
 * @return true if simulation is successful, false otherwise
 */
bool Conditional::Simulate(ApplicationManager* pManager)
{
    return true;
}

/**
 * @brief Edit the Conditional statement
 *
 * @param pManager Pointer to the ApplicationManager
 */
void Conditional::Edit(ApplicationManager* pManager)
{
    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();
    Point Position;

    // Prompt user to click on the flowchart to place the statement
    pOut->PrintMessage("Click to edit the conditional statement.");
    pIn->GetPointClicked(Position);
    pOut->ClearStatusBar();

    // Ask the user to enter the LHS parameter
    pOut->PrintMessage("Please enter the LHS parameter");
    LHS = pIn->GetString(pOut);
    while (ValueOrVariable(LHS) == INVALID_OP)
    {
        pOut->PrintMessage("Invalid LHS. Enter a valid value or variable.");
        LHS = pIn->GetString(pOut);
    }

    // Ask the user to enter an arithmetic comparator
    pOut->PrintMessage("Please enter an arithmetic comparator");
    Comparator = pIn->GetCompOperator(pOut);

    // Ask the user to enter the RHS parameter
    pOut->PrintMessage("Please enter the RHS parameter");
    RHS = (ValueOrVariable(LHS) == 0) ? pIn->GetVariable(pOut) : pIn->GetString(pOut);
    while (ValueOrVariable(RHS) == INVALID_OP)
    {
        pOut->PrintMessage("Invalid RHS. Enter a valid value or variable.");
        RHS = (ValueOrVariable(LHS) == 0) ? pIn->GetVariable(pOut) : pIn->GetString(pOut);
    }

    UpdateStatementText();
}