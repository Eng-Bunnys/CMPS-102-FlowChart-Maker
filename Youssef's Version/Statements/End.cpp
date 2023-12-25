#include "End.h"

/**
 * @brief Constructor for the End class.
 * @param Lcorner Top-left corner of the End statement.
 */
End::End(Point Lcorner) {
    LeftCorner = Lcorner;
    pOutConn = NULL; // Initialize outgoing connector to null
    Outlet.x = LeftCorner.x + UI.START_WDTH / 2;
    Outlet.y = LeftCorner.y + UI.START_HI;
}

/**
 * @brief Draws the End statement on the output window.
 * @param pOut Pointer to the Output class for drawing.
 */
void End::Draw(Output* pOut) const {
    pOut->DrawStart(LeftCorner, UI.START_WDTH, UI.START_HI, "End", Selected);
}

/**
 * @brief Updates the text representation of the End statement.
 */
void End::UpdateStatementText() {
    Text = "End";
}

/**
 * @brief Checks if a given point is inside the boundaries of the End statement.
 * @param p Point to check.
 * @return True if the point is inside the statement, false otherwise.
 */
bool End::ContainsPoint(Point p) {
    if (p.x >= LeftCorner.x && p.x <= LeftCorner.x + UI.START_WDTH && p.y >= LeftCorner.y && p.y <= LeftCorner.y + UI.START_HI) {
        return true;
    }
    return false;
}