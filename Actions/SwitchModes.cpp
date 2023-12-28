#include "SwitchModes.h"

SwitchModes::SwitchModes(ApplicationManager* P) : Action(P) {}

void SwitchModes::ReadActionParameters() {}

void SwitchModes::Execute() {
    Output* pOut = pManager->GetOutput();
    UI.AppMode == DESIGN ? pOut->CreateSimulationToolBar() : pOut->CreateDesignToolBar();
}