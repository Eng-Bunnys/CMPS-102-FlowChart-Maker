#include "OperatorAssign.h"
#include <sstream>
using namespace std;

/**
 * @brief Constructor for OperatorAssign class.
 * @param Lcorner The top-left corner of the operator assignment statement.
 * @param LeftVar The left-hand side variable.
 * @param RightFirst The first right-hand side operand.
 * @param Op The operator (e.g., +, -, *, /).
 * @param RightTwo The second right-hand side operand.
 */
OperatorAssign::OperatorAssign(Point Lcorner, string LeftVar, string RightFirst, string Op, string RightTwo) : Statement(1, true)
{
    LHS = LeftVar;
    RHSOne = RightFirst;
    RHSTwo = RightTwo;
    Operator = Op;

    UpdateStatementText();

    LeftCorner = Lcorner;

    SetOutlet();
    SetInlet();
}

/**
 * @brief Draws the operator assignment statement on the output.
 * @param pOut Pointer to the output object for drawing.
 */
void OperatorAssign::Draw(Output* pOut) const
{
    pOut->DrawAssign(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);
}

/**
 * @brief Gets the top-left corner of the operator assignment statement.
 * @return The top-left corner point.
 */
Point OperatorAssign::getLeftCorner() const
{
    return LeftCorner;
}

/**
 * @brief Checks if a given point is within the boundaries of the operator assignment statement.
 * @param position The point to check.
 * @return True if the point is within the boundaries, false otherwise.
 */
bool OperatorAssign::ContainsPoint(Point position)
{
    if (position.x >= LeftCorner.x && position.x <= LeftCorner.x + UI.ASSGN_WDTH && position.y >= LeftCorner.y && position.y <= LeftCorner.y + UI.ASSGN_HI)
    {
        return true;
    }
    return false;
}

/**
 * @brief Saves the operator assignment statement to an output file.
 * @param OutFile Output file stream.
 */
void OperatorAssign::Save(ofstream& OutFile)
{
    string type = getOperator();
    OutFile << "OP_ASSIGN  " << ID << "  " << LeftCorner.x << "  " << LeftCorner.y << "  " << LHS << "  " << RHSOne << "  " << type << "  " << RHSTwo << endl;
}

/**
 * @brief Gets the operator type for saving to a file.
 * @return The operator type as a string.
 */
string OperatorAssign::getOperator()
{
    if (Operator == "+")
    {
        return "PLUS";
    }
    else if (Operator == "-")
    {
        return "MINUS";
    }
    else if (Operator == "/")
    {
        return "DIVIDE";
    }
    else if (Operator == "*")
    {
        return "MUL";
    }
}

/**
 * @brief Loads the operator assignment statement from an input file.
 * @param Infile Input file stream.
 */
void OperatorAssign::Load(ifstream& Infile)
{
    string Operator;
    Infile >> ID >> LeftCorner.x >> LeftCorner.y >> LHS >> RHSOne >> Operator >> RHSTwo;
    TranslateOperator(Operator);
    SetOutlet();
    SetInlet();
    UpdateStatementText();
}

/**
 * @brief Translates the operator type from file representation to internal representation.
 * @param S The operator type as a string.
 */
void OperatorAssign::TranslateOperator(string S)
{
    if (S == "PLUS")
    {
        Operator = "+";
    }
    else if (S == "MINUS")
    {
        Operator = "-";
    }
    else if (S == "DIVIDE")
    {
        Operator = "/";
    }
    else if (S == "MUL")
    {
        Operator = "*";
    }
}

/**
 * @brief Sets the outlet point for the operator assignment statement.
 */
void OperatorAssign::SetOutlet()
{
    Outlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
    Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}

/**
 * @brief Sets the inlet point for the operator assignment statement.
 */
void OperatorAssign::SetInlet()
{
    Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
    Inlet.y = LeftCorner.y;
}

/**
 * @brief Updates the text representation of the operator assignment statement.
 */
void OperatorAssign::UpdateStatementText()
{
    ostringstream T;
    T << LHS << " = " << RHSOne << " " << Operator << " " << RHSTwo;
    Text = T.str();
}

/**
 * @brief Creates a copy of the operator assignment statement.
 * @return A pointer to the copied statement.
 */
Statement* OperatorAssign::MakeCopy()
{
    Statement* CopiedStatement = new OperatorAssign(Point(0, 0), ((OperatorAssign*)this)->LHS, ((OperatorAssign*)this)->RHSOne, ((OperatorAssign*)this)->Operator, ((OperatorAssign*)this)->RHSTwo);
    return CopiedStatement;
}

/**
 * @brief Sets the drawing point for the operator assignment statement.
 * @param P The new drawing point.
 */
void OperatorAssign::SetDrawingPoint(Point P)
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
 * @brief Checks if a variable is in the given variable array.
 * @param variableArray Array of variables.
 * @param arraySize Size of the array.
 * @param targetVariable The variable to check.
 * @return True if the variable is in the array, false otherwise.
 */
bool IsInVariableArray(string* variableArray, const int& arraySize, const string& targetVariable)
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
 * @brief Copies the source array to the destination array.
 * @param sourceArray Source array to copy from.
 * @param destinationArray Destination array to copy to.
 * @param arraySize Size of the arrays.
 */
void CopyVariableArray(const string* sourceArray, string* destinationArray, const int& arraySize)
{
    for (int i = 0; i < arraySize; i++)
    {
        destinationArray[i] = sourceArray[i];
    }
}

/**
 * @brief Checks the validity of variables in the operator assignment statement.
 * @param variableArray Array of variables to check.
 * @param arraySize Size of the array.
 * @return True if variables are valid, false otherwise.
 */
bool OperatorAssign::CheckVariables(string*& variableArray, int& arraySize)
{
    if (arraySize == 0)
    {
        if (IsVariable(RHSOne) || IsVariable(RHSTwo))
        {
            return false;
        }
        else
        {
            // Add LHS to the array
            variableArray[0] = LHS;
            arraySize++;
            return true;
        }
    }

    if (IsVariable(RHSOne) && !IsInVariableArray(variableArray, arraySize, RHSOne))
    {
        return false;
    }

    if (IsVariable(RHSTwo) && !IsInVariableArray(variableArray, arraySize, RHSTwo))
    {
        return false;
    }

    if (IsInVariableArray(variableArray, arraySize, LHS))
    {
        return true;
    }

    string* newArray = new string[arraySize + 1];
    CopyVariableArray(variableArray, newArray, arraySize);
    delete[] variableArray;
    variableArray = newArray;
    variableArray[arraySize] = LHS;
    arraySize++;
    return true;
}

/**
 * @brief Simulates the execution of the operator assignment statement.
 * @param pManager Pointer to the application manager.
 * @return True if simulation is successful, false otherwise.
 */
bool OperatorAssign::Simulate(ApplicationManager* pManager)
{
    double D1, D3;
    if (IsValue(RHSOne))
    {
        D1 = atof(RHSOne.c_str());
    }
    else
    {
        D1 = pManager->ReturnValue(RHSOne);
    }

    if (IsValue(RHSTwo))
    {
        D3 = atof(RHSTwo.c_str());
    }
    else
    {
        D3 = pManager->ReturnValue(RHSTwo);
    }
    if (Operator == "+")
    {
        pManager->AddIntVariable(LHS, D1 + D3);
    }
    else if (Operator == "-")
    {
        pManager->AddIntVariable(LHS, D1 - D3);
    }
    else if (Operator == "*")
    {
        pManager->AddIntVariable(LHS, D1 * D3);
    }
    else
    {
        pManager->AddIntVariable(LHS, D1 / D3);
    }
    return true;
}

/**
 * @brief Edits the operator assignment statement.
 * @param pManager Pointer to the application manager.
 */
void OperatorAssign::Edit(ApplicationManager* pManager)
{
    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();
    // Get the left-hand side (LHS) variable from user input
    pOut->PrintMessage("Enter the left-hand side (LHS) variable: ");
    LHS = pIn->GetVariable(pOut);

    // Get the first operand from user input
    while (true) {
        pOut->PrintMessage("Enter the first operand: ");
        RHSOne = pIn->GetString(pOut);

        if (ValueOrVariable(RHSOne) != INVALID_OP) break;
        else  pOut->PrintMessage("Invalid input for the first operand. Please enter a valid value or variable.");
    }

    // Get the arithmetic operator from user input
    Operator = pIn->GetArithOperator(pOut);

    // Get the second operand from user input
    while (true) {
        pOut->PrintMessage("Enter the second operand: ");
        RHSTwo = pIn->GetString(pOut);

        if (ValueOrVariable(RHSTwo) != INVALID_OP)   break;
        else pOut->PrintMessage("Invalid input for the second operand. Please enter a valid value or variable.");
    }

    pOut->ClearStatusBar();
    UpdateStatementText();
}
