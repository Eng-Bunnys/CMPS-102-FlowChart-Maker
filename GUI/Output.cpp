#include "Output.h"

#define PI 3.14159

Output::Output() {
    UI.width = 1550;
    UI.height = 620;
    UI.wx = 15;
    UI.wy = 15;

    // Design Mode is the default mode
    UI.AppMode = DESIGN;

    UI.StatusBarHeight = 50;
    UI.ToolBarHeight = 50;
    UI.MenuItemWidth = 80;
    UI.DrawingAreaWidth = 0.75 * UI.width;

    UI.DrawColor = BLUE;
    UI.HighlightColor = RED;
    UI.MsgColor = RED;

    UI.ASSGN_WDTH = 150;
    UI.ASSGN_HI = 50;

    ConnectorWidth = 2;

    // Create the output window
    pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
    // Change the title
    pWind->ChangeTitle("GBF Flowchart Maker");

    pWind->SetPen(RED, 3);
    CreateDesignToolBar();
    CreateStatusBar();
    ClearDrawArea();
    ClearOutputBar();
}

Input* Output::CreateInput() {
    Input* pIn = new Input(pWind);
    return pIn;
}

//Interface 
window* Output::CreateWind(int wd, int h, int x, int y) {
    return new window(wd, h, x, y);
}

void Output::CreateStatusBar() {
    pWind->DrawLine(0, UI.height - UI.StatusBarHeight, UI.width, UI.height - UI.StatusBarHeight);
}

//Drawing the design menu tool bar
void Output::CreateDesignToolBar() {
    UI.AppMode = DESIGN; // Design Mode

    string MenuItemImages[DSN_ITM_CNT];
    MenuItemImages[ITM_SELECT] = "images\\Select.jpg";
    MenuItemImages[ITM_EDIT] = "images\\Edit.jpg";
    MenuItemImages[ITM_SAVE] = "images\\Save.jpg";
    MenuItemImages[ITM_LOAD] = "images\\load.jpg";
    MenuItemImages[ITM_READ] = "images\\Read.jpg";
    MenuItemImages[ITM_WRITE] = "images\\Write.jpg";
    MenuItemImages[ITM_VALUE_ASSIGN] = "images\\Assign.jpg";
    MenuItemImages[ITM_VAR_ASSIGN] = "images\\AssignVar.jpg";
    MenuItemImages[ITM_OP_ASSIGN] = "images\\AssignOP.jpg";
    MenuItemImages[ITM_COND] = "images\\Condition.jpg";
    MenuItemImages[ITM_START] = "images\\Start_Oval.jpg";
    MenuItemImages[ITM_END] = "images\\End_Oval.jpg";
    MenuItemImages[ITM_INPUT_OUTPUT] = "images\\InputOutput.jpg";
    MenuItemImages[ITM_CONNECTOR] = "images\\Connector.jpg";
    MenuItemImages[ITM_PASTE] = "images\\Paste.jpg";
    MenuItemImages[ITM_COPY] = "images\\copy.jpg";
    MenuItemImages[ITM_DELETE] = "images\\delete.jpg";
    MenuItemImages[ITM_CHANGE_TO_SIM] = "images\\Simulate.jpg";
    MenuItemImages[ITM_EXIT] = "images\\Exit.jpg";

    for (int i = 0; i < DSN_ITM_CNT; i++)
        pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

    pWind->SetPen(RED, 2);
    pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

}
//Drawing the simulation mode tool bar
void Output::CreateSimulationToolBar() {
    UI.AppMode = SIMULATION;

    string MenuItemImages[SIM_ITM_CNT];
    MenuItemImages[ITM_SELECT_SIM] = "images\\Select.jpg";
    MenuItemImages[ITM_EDIT_SIM] = "images\\Edit.jpg";
    MenuItemImages[ITM_SAVE_SIM] = "images\\Save.jpg";
    MenuItemImages[ITM_LOAD_SIM] = "images\\load.jpg";
    MenuItemImages[ITM_VALIDATE] = "images\\Validate.jpg";
    MenuItemImages[ITM_RUN] = "images\\Run.jpg";
    MenuItemImages[ITM_CHANGE_TO_DSN_SIM] = "images\\DesignMenu.jpg";
    MenuItemImages[ITM_EXIT_SIM] = "images\\Exit.jpg";

    for (int i = 0; i < SIM_ITM_CNT; i++)
        pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
}

// Clear Status bar by drawing a filled white rectangle
void Output::ClearStatusBar() {
    pWind->SetPen(RED, 2);
    pWind->SetBrush(WHITE);
    pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}

void Output::ClearDrawArea() {
    pWind->SetPen(RED, 2);
    pWind->SetBrush(WHITE);
    pWind->DrawRectangle(0, UI.ToolBarHeight, UI.DrawingAreaWidth, UI.height - UI.StatusBarHeight);
}

// Create output bar by drawing a filled rectangle
void Output::ClearOutputBar() {
    pWind->SetPen(RED, 2);
    pWind->SetBrush(LIGHTBLUE);
    pWind->DrawRectangle(UI.DrawingAreaWidth, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);
}

// Prints a message on status bar
void Output::PrintMessage(string msg) {
    //Clearing the status bar
    ClearStatusBar();

    pWind->SetPen(UI.MsgColor, 50);
    pWind->SetFont(20, BOLD, BY_NAME, "Arial");
    pWind->DrawString(10, UI.height - (int)(UI.StatusBarHeight / 1.5), msg);
}

void Output::DrawString(const int iX,
    const int iY,
    const string Text) {
    pWind->SetPen(BLACK, 2);
    pWind->DrawString(iX, iY, Text);
}

//Statement drawing functions

//Draw assignment statement and write the "Text" on it
//Rectangle
void Output::DrawAssign(Point Left, int Width, int Height, string Text, bool Selected) {
    if (Selected) pWind->SetPen(UI.HighlightColor, 3);
    else pWind->SetPen(UI.DrawColor, 3);

    //Getting the size of the text entered
    int TextWidth, TextHeight;
    pWind->GetStringSize(TextWidth, TextHeight, Text);

    //Adjusting the width and height based on the text size
    Width = max(UI.ASSGN_WDTH, TextWidth + 20);
    Height = max(UI.ASSGN_HI, TextHeight + 10);

    //Draw the statement block rectangle
    pWind->DrawRectangle(Left.x, Left.y, Left.x + Width, Left.y + Height);

    //Writing the text inside of the shape
    pWind->SetPen(BLACK, 2);
    pWind->DrawString(Left.x + (Width - TextWidth) / 2, Left.y + (Height - TextHeight) / 2, Text);
}
//Diamond
void Output::DrawConditionalStat(Point Left, int Width, int Height, string Text, bool Selected) {
    if (Selected) pWind->SetPen(UI.HighlightColor, 3);
    else pWind->SetPen(UI.DrawColor, 3);

    // Drawing the diamond shape for a conditional statement
    int MidX = Left.x + Width / 2;
    int MidY = Left.y + Height / 2;

    // Calculate and draw the lines for the diamond
    pWind->DrawLine(MidX, MidY - Height / 2, MidX + Width / 2, MidY);
    pWind->DrawLine(MidX + Width / 2, MidY, MidX, MidY + Height / 2);
    pWind->DrawLine(MidX, MidY + Height / 2, MidX - Width / 2, MidY);
    pWind->DrawLine(MidX - Width / 2, MidY, MidX, MidY - Height / 2);

    // Writing the text inside of the shape
    pWind->SetPen(BLACK, 2);
    pWind->DrawString(MidX - Width / 4, MidY - Height / 4, Text);
}
//Oval
void Output::DrawStart(Point Left, int Width, int Height, string Text, bool Selected) {
    if (Selected) pWind->SetPen(UI.HighlightColor, 3);
    else pWind->SetPen(UI.DrawColor, 3);

    //Drawing a circle for the start statement
    int MidX = Left.x + Width / 2;
    int MidY = Left.y + Height / 2;

    pWind->DrawEllipse(Left.x, Left.y, Left.x + Width, Left.y + Height);

    //Writing the text inside of the shape
    pWind->SetPen(BLACK, 2);
    pWind->DrawString(MidX - Width / 4, MidY - Height / 4, Text);
}

void Output::DrawEnd(Point Left, int Width, int Height, string Text, bool Selected) {
    if (Selected) pWind->SetPen(UI.HighlightColor, 3);
    else pWind->SetPen(UI.DrawColor, 3);

    //Drawing an ellipse for the end statement
    int MidX = Left.x + Width / 2;
    int MidY = Left.y + Height / 2;

    pWind->DrawEllipse(Left.x, Left.y, Left.x + Width, Left.y + Height);

    //Writing the text inside of the shape
    pWind->SetPen(BLACK, 2);
    pWind->DrawString(MidX - Width / 4, MidY - Height / 4, Text);
}
//Parallelogram
void Output::DrawRead(Point Left, int Width, int Height, string Text, bool Selected) {
    if (Selected) pWind->SetPen(UI.HighlightColor, 3);
    else pWind->SetPen(UI.DrawColor, 3);

    //Drawing the parallelogram shape for a Read statement
    int MidX = Left.x + Width / 2;
    int MidY = Left.y + Height / 2;

    //Drawing the parallelogram
    pWind->DrawLine(Left.x, Left.y, Left.x + Width, Left.y);
    pWind->DrawLine(Left.x + Width, Left.y, Left.x + (2 * Width) / 3, Left.y + Height);
    pWind->DrawLine(Left.x + (2 * Width) / 3, Left.y + Height, Left.x - Width / 3, Left.y + Height);
    pWind->DrawLine(Left.x - Width / 3, Left.y + Height, Left.x, Left.y);

    // Writing the text inside of the shape
    pWind->SetPen(BLACK, 2);
    pWind->DrawString(MidX - Width / 4, MidY - Height / 4, Text);
}

void Output::DrawWrite(Point Left, int Width, int Height, string Text, bool Selected) {
    if (Selected) pWind->SetPen(UI.HighlightColor, 3);
    else pWind->SetPen(UI.DrawColor, 3);

    //Drawing the parallelogram shape for a Write statement
    int MidX = Left.x + Width / 2;
    int MidY = Left.y + Height / 2;

    //Draw the parallelogram
    pWind->DrawLine(Left.x, Left.y, Left.x + Width, Left.y);
    pWind->DrawLine(Left.x + Width, Left.y, Left.x + (2 * Width) / 3, Left.y + Height);
    pWind->DrawLine(Left.x + (2 * Width) / 3, Left.y + Height, Left.x - Width / 3, Left.y + Height);
    pWind->DrawLine(Left.x - Width / 3, Left.y + Height, Left.x, Left.y);

    //Writing the text inside of the shape
    pWind->SetPen(BLACK, 2);
    pWind->DrawString(MidX - Width / 4, MidY - Height / 4, Text);
}

//Draw a connector line between two points
void Output::DrawConnector(Point Start, Point End, bool Selected) {
    //Drawing the first point
    pWind->DrawPixel(Start.x, Start.y);

    //Drawing the second point
    pWind->DrawPixel(End.x, End.y);

    if (Selected) pWind->SetPen(UI.HighlightColor, ConnectorWidth);
    else pWind->SetPen(UI.DrawColor, ConnectorWidth);

    //Drawing a line between the two points
    pWind->DrawLine(Start.x, Start.y, End.x, End.y);

    //The next part is drawing the arrow heads, which is a bit tricky, I've written comments explaining why I did what I did

    double angle = atan2(End.y - Start.y, End.x - Start.x);
    // Calculate the angle between the line segment and the x-axis using atan2
    // The difference in y-coordinates and x-coordinates between the start and end points is used

    double arrowLength = 15.0;
    // Define the length of the arrow

    double arrowAngle = PI / 6.0;
    // Define the angle between the arrow lines in radians
    // In this case, it's set to pi/6, which corresponds to 30 degrees

    double arrowP1X = End.x - arrowLength * cos(angle - arrowAngle);
    // Calculate the x-coordinate of the first point of the arrow
    // Subtract the horizontal component of the arrow's length (obtained by multiplying the arrow length by the cosine of the angle minus the arrow angle) from the x-coordinate of the end point

    double arrowP1Y = End.y - arrowLength * sin(angle - arrowAngle);
    // Calculate the y-coordinate of the first point of the arrow
    // Subtract the vertical component of the arrow's length (obtained by multiplying the arrow length by the sine of the angle minus the arrow angle) from the y-coordinate of the end point

    double arrowP2X = End.x - arrowLength * cos(angle + arrowAngle);
    // Calculate the x-coordinate of the second point of the arrow
    // Subtract the horizontal component of the arrow's length (obtained by multiplying the arrow length by the cosine of the angle plus the arrow angle) from the x-coordinate of the end point

    double arrowP2Y = End.y - arrowLength * sin(angle + arrowAngle);
    // Calculate the y-coordinate of the second point of the arrow
    // Subtract the vertical component of the arrow's length (obtained by multiplying the arrow length by the sine of the angle plus the arrow angle) from the y-coordinate of the end point

    pWind->DrawLine(End.x, End.y, arrowP1X, arrowP1Y);
    pWind->DrawLine(End.x, End.y, arrowP2X, arrowP2Y);
}

Output::~Output() {
    delete pWind;
}
