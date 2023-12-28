#include "Run.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"

Run::Run(ApplicationManager* ApM) : Action(ApM) {}

void Run::ReadActionParameters() {
}

void Run::Execute() {
    Validate validation(pManager);
    validation.Execute();

    if (!validation.IsValid()) {
        pManager->GetOutput()->PrintMessage("Flowchart isn't valid.");
        return;
    }

    Output* pOut = pManager->GetOutput();
    pOut->ClearOutputBar();

    Statement* currentStatement = pManager->GetStart();

    while (currentStatement->GetMaxNumberOfOutputConnectors() != 0) {
        bool isTrueCase = currentStatement->Simulate(pManager);

        if (currentStatement->GetMaxNumberOfOutputConnectors() == 1) {
            currentStatement = (currentStatement->GetConnecter())->getDstStat();
        }
        else {
            int connectorIndex = isTrueCase ? 1 : 0;
            currentStatement = (currentStatement->GetConnecter(connectorIndex))->getDstStat();
        }
    }
}