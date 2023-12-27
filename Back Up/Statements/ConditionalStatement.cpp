#include <sstream>
#include "ConditionalStatement.h"
using namespace std;

// Constructor for Conditional class
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

// Setter for LHS
void Conditional::setLHS(const string& L)
{
    LHS = L;
    UpdateStatementText();
}

// Setter for RHS
void Conditional::setRHS(const string& R)
{
    RHS = R;
    UpdateStatementText();
}

// Setter for Comparator
void Conditional::setComparator(const string& C)
{
    Comparator = C;
    UpdateStatementText();
}

// Getter for the left corner
Point Conditional::getLeftCorner() const
{
    return LeftCorner;
}

// Getter for false outlet
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

// Draw function to display the Conditional statement
void Conditional::Draw(Output* pOut) const
{
    // Call Output::DrawConditionalStat function to draw the conditional statement
    pOut->DrawConditionalStat(LeftCorner, UI.COND_WDTH, UI.COND_HI, Text, Selected);
}

// Check if a point is inside the Conditional statement
bool Conditional::ContainsPoint(Point position)
{
    if (position.x >= LeftCorner.x && position.x <= LeftCorner.x + UI.COND_WDTH && position.y >= LeftCorner.y - UI.COND_HI / 2 && position.y <= LeftCorner.y + UI.COND_HI / 2)
    {
        return true;
    }
    return false;
}

// Load Conditional statement from file
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

// Calculate left corner based on center
void Conditional::CenterToLeftCorner(Point C)
{
    LeftCorner.x = C.x - (0.5) * UI.COND_WDTH;
    LeftCorner.y = C.y - (0.5) * UI.COND_HI;
}

// Set outlets and inlets for the Conditional statement
void Conditional::SetOutlet()
{
    OutletF.x = LeftCorner.x;
    OutletF.y = LeftCorner.y;

    Outlet.x = LeftCorner.x + UI.COND_WDTH;
    Outlet.y = LeftCorner.y;
}

void Conditional::SetInlet()
{
    Inlet.x = LeftCorner.x + UI.COND_WDTH / 2;
    Inlet.y = LeftCorner.y - UI.COND_HI / 2;
}

// Update the text representation of the Conditional statement
void Conditional::UpdateStatementText()
{
    // Build the statement text: Left handside, then comparator, then right handside
    ostringstream T;
    T << LHS << Comparator << RHS;
    Text = T.str();
}

// Save Conditional statement to file
void Conditional::Save(ofstream& OutFile)
{
    string opr = getOperator();
    OutFile << "COND  " << ID << "  " << LeftCorner.x + (0.5) * UI.COND_WDTH << "  " << LeftCorner.y + (0.5) * UI.COND_HI << "  " << LHS << "  " << opr << "  " << RHS << endl;
}

// Get the operator for saving
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

// Reverse the operator for loading
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

// Clone the Conditional statement
Statement* Conditional::MakeCopy()
{
    Statement* clone = new Conditional(Point(0, 0), ((Conditional*)this)->LHS, ((Conditional*)this)->RHS, ((Conditional*)this)->Comparator);
    return clone;
}

// Set the drawing point for the Conditional statement
void Conditional::SetDrawingPoint(Point P)
{
    LeftCorner = P;
    LeftCorner.x = P.x - UI.COND_WDTH / 2;
    LeftCorner.y = P.y + UI.COND_HI / 2;

    SetOutlet();
    SetInlet();
}

// Check if the variables in the Conditional statement are valid
bool Conditional::CheckVariables(string*& arr, int& c)
{
    if (c == 0)
    {
        return false;
    }
    if (IsVariable(LHS))
    {
        int i = 0;
        while (i < c)
        {
            if (arr[i] == LHS)
            {
                break;
            }
            else
            {
                i++;
            }
        }
        if (i == c)
            return false;
    }

    if (IsVariable(RHS))
    {
        int i = 0;
        while (i < c)
        {
            if (arr[i] == RHS)
            {
                break;
            }
            else
            {
                i++;
            }
        }
        if (i == c)
            return false;
    }
    return true;
}

// Simulate the Conditional statement
bool Conditional::Simulate(ApplicationManager* pManager)
{
    double D1, D2;
    if (IsValue(LHS))
    {
        D1 = atof(LHS.c_str());
    }
    else
    {
        D1 = pManager->ReturnValue(LHS);
    }
    if (IsValue(RHS))
    {
        D2 = atof(RHS.c_str());
    }
    else
    {
        D2 = pManager->ReturnValue(RHS);
    }

    if (Comparator == ">")
    {
        return (D1 > D2);
    }
    else if (Comparator == ">=")
    {
        return (D1 >= D2);
    }
    else if (Comparator == "<")
    {
        return (D1 < D2);
    }
    else if (Comparator == "<=")
    {
        return (D1 <= D2);
    }
    else if (Comparator == "==")
    {
        return (D1 == D2);
    }
    else if (Comparator == "!=")
    {
        return (D1 != D2);
    }
}

// Edit the Conditional statement
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