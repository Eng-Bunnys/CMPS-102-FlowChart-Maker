#ifndef STATEMENT_H
#define STATEMENT_H

#include "../Utils.h"
#include "Connector.h"

// This is for the file system https://cplusplus.com/reference/fstream/fstream/
#include <fstream>

class ApplicationManager;

/**
 * @class Statement
 * @brief Base class for all Statements in the flowchart.
 */
class Statement
{
    /// I decided to go with JSDocs like comments for these Data Members since they're used a lot
protected:
    /**
     * @brief A unique identifier generator for Statement instances.
     * @details This static member keeps track of the unique IDs assigned to each Statement instance.
     *          It ensures that each statement has a distinct identifier.
     */
    static int UniqueIDMaker;

    /**
     * @brief Indicates whether incoming connections are allowed for this statement.
     * @details If false, it means the statement is of type Start, and another statement cannot connect to it.
     *          If true, it allows incoming connections.
     */
    const bool AllowsIncomingConnections;

    /**
     * @brief Indicates whether the statement has incoming connections.
     * @details If true, it means there is an Input Connector connected to this statement.
     *          If false, it indicates that there are no incoming connections.
     */
    bool HasIncomingConnections;

    /**
     * @brief The maximum number of output connectors for this statement.
     * @details It is set to 0 if the statement is of type End, 2 if Conditional, and 1 for all other statement types.
     *          This value determines the maximum number of outgoing connections the statement can have.
     */
    const int MaxOutConnectors;

    /**
     * @brief An array of output connectors for this statement.
     * @details The array holds pointers to the output connectors. The size of the array is determined by MaxOutConnectors.
     *          OutputConnectors[0] is the first output connector, and OutputConnectors[1] is the second (if MaxOutConnectors is 2).
     */
    Connector *OutputConnectors[2];

    /**
     * @brief The unique identifier for each Statement instance.
     * @details Each statement is assigned a unique ID upon creation. This ID helps in distinguishing statements in the system.
     */
    int ID;

    /**
     * @brief The text associated with the statement.
     * @details It represents the content or condition of the statement, such as "X = 5" or "salary > 3000".
     */
    string Text;

    /**
     * @brief Indicates whether the statement is currently selected on the flowchart.
     * @details If true, it means the statement is selected; if false, it is not selected.
     *          Selection often involves highlighting the statement for user interaction or modification.
     */
    bool Selected;

    /**
     * @brief The inlet point of the statement.
     * @details The inlet point is the connection point where incoming connectors are attached.
     *          It is a part of the statement's graphical representation in the flowchart.
     */
    Point Inlet;

    /**
     * @brief The outlet point of the statement.
     * @details The outlet point is the connection point where outgoing connectors are attached.
     *          It is a part of the statement's graphical representation in the flowchart.
     */
    Point Outlet;

    /**
     * @brief The current number of outgoing connectors for this statement.
     * @details It keeps track of the actual number of output connectors that are currently connected.
     *          This count is useful for managing the dynamic addition or removal of connectors during interaction.
     */
    int NumberOfOutConnectors;

    /**
     * @brief Update the text of the statement.
     * @details This function is called when any part of the statement is edited.
     */
    virtual void UpdateStatementText() = 0;

public:
    /**
     * @brief Constructor for the Statement class.
     * @param Num The unique identifier for the statement.
     * @param CanConn Boolean indicating if the statement can have outgoing connectors.
     */
    Statement(int Num, bool CanConn);

    void SetSelected(bool s);
    bool IsSelected() const;

    /**
     * @brief Draw the statement on the output.
     * @param pOut Pointer to the Output object.
     */
    virtual void Draw(Output *pOut) const = 0;

    /**
     * @brief Check if a point is inside the statement.
     * @param position The point to check.
     * @return True if the point is inside the statement, false otherwise.
     */
    virtual bool ContainsPoint(Point position) = 0;

    /**
     * @brief Remove a connector from the statement.
     * @param i The index of the connector to remove (0 or 1).
     */
    void RemoveConnector(int i = 0);

    /**
     * @brief Get the maximum number of output connectors.
     * @return The maximum number of output connectors.
     */
    int GetMaxNumberOfOutputConnectors() const;

    /**
     * @brief Get the specified output connector.
     * @param i The index of the connector to get (0 or 1).
     * @return The specified output connector or nullptr if index is invalid.
     */
    virtual Connector *GetConnecter(int i = 0);

    /**
     * @brief Set the output connector at the specified index.
     * @param C The Connector to set.
     * @param i The index of the connector to set (0 or 1).
     */
    void SetConnector(Connector *C, int i = 0);

    /**
     * @brief Set whether the statement has incoming connectors.
     * @param B Boolean value indicating whether the statement has incoming connectors.
     */
    void SetHasIncomingConnectors(bool B);

    /**
     * @brief Get whether the statement has incoming connectors.
     * @return True if the statement has incoming connectors, false otherwise.
     */
    bool GetHasIncomingConnectors() const;

    /**
     * @brief Check if the statement can be connected.
     * @return True if the statement can be connected, false otherwise.
     */
    bool CanBeConnected() const;

    /**
     * @brief Get the inlet point of the statement.
     * @return The inlet point.
     */
    Point GetInlet() const;

    /**
     * @brief Get the outlet point of the statement.
     * @return The outlet point.
     */
    Point GetOutlet() const;

    /**
     * @brief Get the unique identifier of the statement.
     * @return The unique identifier.
     */
    int GetID();

    /**
     * @brief Set the outlet point of the statement.
     */
    virtual void SetOutlet() = 0;

    /**
     * @brief Set the inlet point of the statement.
     */
    virtual void SetInlet() = 0;

    /**
     * @brief Create a copy of the statement.
     * @return A new instance of the statement with the same properties.
     */
    virtual Statement *MakeCopy() = 0;

    /**
     * @brief Set the drawing point of the statement.
     * @param P The drawing point to set.
     */
    virtual void SetDrawingPoint(Point P) = 0;

    /**
     * @brief Get the number of drawn connectors.
     * @return The number of drawn connectors.
     */
    int GetDrawnConnectors() const;

    /**
     * @brief Add an output connector to the statement.
     */
    void AddOutputConnector();

    /**
     * @brief Decrement the number of output connectors.
     */
    void DecrementOutputConnectors();

    /**
     * @brief Save the Statement parameters to a file.
     * @param OutFile Output file stream to write the parameters.
     */
    virtual void Save(ofstream &OutFile) = 0;

    /**
     * @brief Load the Statement parameters from a file.
     * @param Infile Input file stream to read the parameters.
     */
    virtual void Load(ifstream &Infile) = 0;

    /**
     * @brief Edit the Statement parameters.
     * @param pManager Pointer to the ApplicationManager.
     */
    virtual void Edit(ApplicationManager *pManager) = 0;

    /**
     * @brief Execute the statement in the simulation mode.
     * @param pManager Pointer to the ApplicationManager.
     * @return True if the simulation is successful.
     */
    virtual bool Simulate(ApplicationManager *pManager = nullptr) = 0;

    /**
     * @brief Check and collect variables used in the statement.
     * @param arr Array to store the variables.
     * @param c Counter for the number of variables.
     * @return True if the variables are checked successfully.
     */
    virtual bool CheckVariables(string *&arr, int &c) = 0;
};

#endif // STATEMENT_H