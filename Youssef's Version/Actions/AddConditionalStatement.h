#ifndef ADD_CONDITIONAL_STATEMENT_H
#define ADD_CONDITIONAL_STATEMENT_H

#include "Action.h"

 /**
  * @class AddConditionalStatement
  * @brief Represents an action that adds a conditional statement to the flowchart.
  */
class AddConditionalStatement : public Action {
private:
    Point Position; /**< Position where the user clicks to add the statement. */
    string LHS;       /**< Left-hand side of the conditional statement. */
    string CompOperator; /**< Comparison operator. */
    string RHS;       /**< Right-hand side of the conditional statement. */

public:
    /**
     * @brief Constructor.
     * @param pAppManager Pointer to the application manager.
     */
    AddConditionalStatement(ApplicationManager* pAppManager);

    /**
     * @brief Reads the parameters for the conditional statement from user input.
     */
    virtual void ReadActionParameters();

    /**
     * @brief Creates and adds a conditional statement to the list of statements.
     */
    virtual void Execute();
};

#endif