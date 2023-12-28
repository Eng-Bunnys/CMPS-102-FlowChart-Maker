#include "Statement.h"
#include "..\ApplicationManager.h"
#include "../Utils.h"

/**
 * @description Returns the smaller of two integers.
 * @param {number} FirstNumber - The first integer to compare.
 * @param {number} SecondNumber - The second integer to compare.
 * @returns {number} The smaller of the two integers.
 */
int GetMin(int FirstNumber, int SecondNumber)
{
    return FirstNumber <= SecondNumber ? FirstNumber : SecondNumber;
}

/**
 * @member UniqueIDMaker
 * @type {number}
 * @description A static member that serves as a unique identifier generator for Statement instances.
 */
int Statement::UniqueIDMaker = 0;

/**
 * @description Represents a statement in a flowchart.
 * @param {number} Case - The type of the statement, determining the maximum number of output connectors.
 * @param {boolean} Connectable - Indicates whether incoming connections are allowed for this statement.
 */
Statement::Statement(int Case, bool Connectable)
    : MaxOutConnectors(Case), AllowsIncomingConnections(Connectable)
{
    HasIncomingConnections = false;
    Text = "";
    Selected = false;
    OutputConnectors[0] = nullptr;
    OutputConnectors[1] = nullptr;
    NumberOfOutConnectors = 0;
    ID = ++UniqueIDMaker;
}

/**
 * @description Sets the selected state of the statement.
 * @param {boolean} s - The selected state to set.
 */
void Statement::SetSelected(bool s)
{
    Selected = s;
}

/**
 * @description Checks if the statement is selected.
 * @returns {boolean} True if the statement is selected, false otherwise.
 */
bool Statement::IsSelected() const
{
    return Selected;
}

/**
 * @description Gets the specified output connector.
 * @param {number} Index - The index of the connector to get (0 or 1).
 * @returns {Connector|null} The specified output connector or null if the index is invalid.
 */
Connector *Statement::GetConnecter(int Index)
{
    return (Index >= 0 && Index < MaxOutConnectors && MaxOutConnectors > 0) ? OutputConnectors[GetMin(Index, 1)] : nullptr;
}

/**
 * @description Sets the specified output connector for the statement.
 * @param {Connector} ConnectorToSet - The connector to set.
 * @param {number} TargetIndex - The index at which to set the connector (0 or 1).
 */
void Statement::SetConnector(Connector *ConnectorToSet, int TargetIndex)
{
    (TargetIndex >= 0 && TargetIndex < MaxOutConnectors && ConnectorToSet)
        ? OutputConnectors[GetMin(TargetIndex, MaxOutConnectors - 1)] = ConnectorToSet
        : void(); // Pretty cool syntax fr
}

/**
 * @description Removes the connector at the specified index if it exists.
 * @param {number} i - The index of the connector to remove.
 * @memberof Statement
 */
void Statement::RemoveConnector(int i)
{
    // The index is within valid bounds, considering the statement's maximum output connectors.
    if (i >= 0 && i < GetMin(2, MaxOutConnectors))
    {
        // Sets the connector at the specified index to `nullptr`, effectively removing it.
        OutputConnectors[i] = nullptr;
    }
}

/**
 * @description Gets the maximum number of output connectors for the statement.
 * @returns {number} The maximum number of output connectors.
 */
int Statement::GetMaxNumberOfOutputConnectors() const
{
    return MaxOutConnectors;
}

/**
 * @description Sets the HasIncomingConnections parameter.
 * @param {boolean} B - The value to set.
 */
void Statement::SetHasIncomingConnectors(bool B)
{
    HasIncomingConnections = B;
}

/**
 * @description Gets the HasIncomingConnections parameter.
 * @returns {boolean} True if the statement has incoming connectors, false otherwise.
 */
bool Statement::GetHasIncomingConnectors() const
{
    return HasIncomingConnections;
}

/**
 * @description Checks if the statement can be connected.
 * @returns {boolean} True if the statement can be connected, false otherwise.
 */
bool Statement::CanBeConnected() const
{
    return AllowsIncomingConnections;
}

/**
 * @description Gets the inlet point of the statement.
 * @returns {Point} The inlet point.
 */
Point Statement::GetInlet() const
{
    return (this) ? Inlet : Point(0, 0);
}

/**
 * @description Gets the outlet point of the statement.
 * @returns {Point} The outlet point.
 */
Point Statement::GetOutlet() const
{
    return (this) ? Outlet : Point(0, 0);
}

/**
 * @description Increments the count of actual output connectors for the statement.
 */
void Statement::AddOutputConnector()
{
    NumberOfOutConnectors++;
}

/**
 * @description Gets the unique identifier of the statement.
 * @returns {number} The unique identifier.
 */
int Statement::GetID()
{
    return ID;
}

/**
 * @description Gets the count of actual output connectors for the statement.
 * @returns {number} The count of actual output connectors.
 */
int Statement::GetDrawnConnectors() const
{
    return NumberOfOutConnectors;
}

/**
 * @description Decrements the count of actual output connectors for the statement.
 */
void Statement::DecrementOutputConnectors()
{
    NumberOfOutConnectors--;
}

/**
 * @description Simulates the statement (placeholder implementation).
 * @param {ApplicationManager} pManager - Pointer to the ApplicationManager.
 * @returns {boolean} True if the simulation is successful.
 */
bool Statement::Simulate(ApplicationManager *pManager)
{
    return true;
}