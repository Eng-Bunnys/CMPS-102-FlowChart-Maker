#include "Output.h"
#define PI 3.14159

Output::Output() {
    // Initialize user interface parameters
    UI.width = 1200;
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
    MenuItemImages[ITM_VALUE_ASSIGN] = "images\\Assign.jpg";
    MenuItemImages[ITM_COND] = "images\\Condition.jpg";
    MenuItemImages[ITM_EXIT] = "images\\Exit.jpg";
    MenuItemImages[ITM_START] = "images\\Start.jpg";
    MenuItemImages[ITM_END] = "images\\End.jpg";
    MenuItemImages[ITM_READ] = "images\\Read.jpg";
    MenuItemImages[ITM_WRITE] = "images\\Write.jpg";
    MenuItemImages[ITM_CONNECTOR] = "images\\Connector.jpg";

    for (int i = 0; i < DSN_ITM_CNT; i++)
        pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

    pWind->SetPen(RED, 2);
    pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

    DrawString(0, UI.ToolBarHeight, "Value Assign");
    DrawString(UI.MenuItemWidth, UI.ToolBarHeight, "Condition");
    DrawString(2 * UI.MenuItemWidth, UI.ToolBarHeight, "Exit");
    DrawString(3 * UI.MenuItemWidth, UI.ToolBarHeight, "Start");
    DrawString(4 * UI.MenuItemWidth, UI.ToolBarHeight, "End");
    DrawString(5 * UI.MenuItemWidth, UI.ToolBarHeight, "Read");
    DrawString(6 * UI.MenuItemWidth, UI.ToolBarHeight, "Write");
    DrawString(7 * UI.MenuItemWidth, UI.ToolBarHeight, "Connector");
}
//Drawing the simulation mode tool bar
void Output::CreateSimulationToolBar() {
    UI.AppMode = SIMULATION;

    string MenuItemImages[SIM_ITM_CNT];
    MenuItemImages[ITM_VALIDATE] = "images\\Validate.jpg";
    MenuItemImages[ITM_RUN] = "images\\Run.jpg";

    for (int i = 0; i < SIM_ITM_CNT; i++)
        pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

    pWind->SetPen(RED, 2);
    pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
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

void Output::DrawConditionalStat(Point Left, int Width, int Height, string Text, bool Selected) {
    if (Selected) pWind->SetPen(UI.HighlightColor, 3);
    else pWind->SetPen(UI.DrawColor, 3);

    //Drawing the diamond shape for a conditional statement
    int MidX = Left.x + Width / 2;
    int MidY = Left.y + Height / 2;

    pWind->DrawLine(MidX, Left.y, Left.x + Width, MidY);
    pWind->DrawLine(Left.x + Width, MidY, MidX, Left.y + Height);
    pWind->DrawLine(MidX, Left.y + Height, Left.x, MidY);
    pWind->DrawLine(Left.x, MidY, MidX, Left.y);

    //Writing the text inside of the shape
    pWind->SetPen(BLACK, 2);
    pWind->DrawString(MidX - Width / 4, MidY - Height / 4, Text);
}

void Output::DrawStart(Point Left, int Width, int Height, string Text, bool Selected) {
    if (Selected) pWind->SetPen(UI.HighlightColor, 3);
    else pWind->SetPen(UI.DrawColor, 3);

    //Drawing a circle for the start statement
    int MidX = Left.x + Width / 2;
    int MidY = Left.y + Height / 2;

    pWind->DrawCircle(MidX, MidY, Width / 2);

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

void Output::DrawRead(Point Left, int Width, int Height, string Text, bool Selected) {
    if (Selected) pWind->SetPen(UI.HighlightColor, 3);
    else pWind->SetPen(UI.DrawColor, 3);

    //Drawing a parallelogram for the read statement
    int MidX = Left.x + Width / 2;
    int MidY = Left.y + Height / 2;

    pWind->DrawLine(MidX, Left.y, Left.x + Width, Left.y);
    pWind->DrawLine(Left.x + Width, Left.y, Left.x + Width - Width / 4, Left.y + Height);
    pWind->DrawLine(Left.x + Width - Width / 4, Left.y + Height, Left.x - Width / 4, Left.y + Height);
    pWind->DrawLine(Left.x - Width / 4, Left.y + Height, MidX, Left.y);

    //Writing the text inside of the shape
    pWind->SetPen(BLACK, 2);
    pWind->DrawString(MidX - Width / 4, MidY - Height / 4, Text);
}

void Output::DrawWrite(Point Left, int Width, int Height, string Text, bool Selected) {
    if (Selected) pWind->SetPen(UI.HighlightColor, 3);
    else pWind->SetPen(UI.DrawColor, 3);

    //Drawing a parallelogram for the write statement
    int MidX = Left.x + Width / 2;
    int MidY = Left.y + Height / 2;

    pWind->DrawLine(Left.x - Width / 4, Left.y, MidX, Left.y + Height);
    pWind->DrawLine(MidX, Left.y + Height, Left.x + Width - Width / 4, Left.y + Height);
    pWind->DrawLine(Left.x + Width - Width / 4, Left.y + Height, Left.x, Left.y);
    pWind->DrawLine(Left.x, Left.y, Left.x - Width / 4, Left.y);

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

    double angle = atan2(End.y - Start.y, End.x - Start.x);
    double arrowLength = 15.0;
    double arrowAngle = PI / 6.0; // 30 degrees

    double arrowP1X = End.x - arrowLength * cos(angle - arrowAngle);
    double arrowP1Y = End.y - arrowLength * sin(angle - arrowAngle);

    double arrowP2X = End.x - arrowLength * cos(angle + arrowAngle);
    double arrowP2Y = End.y - arrowLength * sin(angle + arrowAngle);

    pWind->DrawLine(End.x, End.y, arrowP1X, arrowP1Y);
    pWind->DrawLine(End.x, End.y, arrowP2X, arrowP2Y);
}

Output::~Output() {
    delete pWind;
}