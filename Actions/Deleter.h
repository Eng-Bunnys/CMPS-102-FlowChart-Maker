#ifndef DELETER_H
#define DELETER_H

#include "../Actions/Action.h"
#include "../Statements/ConditionalStatement.h"
#include "../Statements/End.h"
#include "../Statements/OperatorAssign.h"
#include "../Statements/Read.h"
#include "../Statements/Start.h"
#include "../Statements/VariableAssign.h"
#include "../Statements/Write.h"
#include "../Statements/ValueAssign.h"

/**
 * @brief The Remove class represents an action to remove statements and connectors from the flowchart.
 *
 * It is derived from the Action class and provides functionality to execute the removal operation.
 */
class Deleter : public Action
{
public:
    /**
     * @brief Constructs a Remove object with a given ApplicationManager.
     *
     * @param P The ApplicationManager associated with the action.
     */
    Deleter(ApplicationManager* P);

    /**
     * @brief Executes the remove action.
     */
    virtual void Execute();

    /**
     * @brief Deletes a connector from the flowchart.
     *
     * @param pConn Pointer to the Connector to be deleted.
     */
    void DeleteConnector(Connector* pConn);

    /**
     * @brief Deletes a statement from the flowchart.
     *
     * @param pManager Pointer to the ApplicationManager.
     * @param pStat Pointer to the Statement to be deleted.
     */
    void DeleteStatement(ApplicationManager* pManager, Statement* pStat);
};

#endif // DELETER_H