#include "Output.h"


Output::Output()
{
	//Initialize user interface parameters
	UI.width = 1200;
	UI.height = 620;
	UI.wx = 15;
	UI.wy =15;

	UI.AppMode = DESIGN;	//Design Mode is the default mode

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

	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("Programming Techniques Project");
	
	pWind->SetPen(RED,3);
	CreateDesignToolBar();
	CreateStatusBar();
	ClearDrawArea();
	ClearOutputBar();
}


Input* Output::CreateInput()
{
	Input* pIn = new Input(pWind);
	return pIn;
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int wd, int h, int x, int y)
{
	return new window(wd, h, x, y);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar()
{
	pWind->DrawLine(0, UI.height-UI.StatusBarHeight, UI.width, UI.height-UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
//TODO: Complete this function
void Output::CreateDesignToolBar() //Draws the Design Menu
{
	UI.AppMode = DESIGN;	//Design Mode
	
	//fill the tool bar 
		
	//You can draw the tool bar icons in any way you want.
	//Below is one possible way
	
	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in Defs.h ==> enum DrawMenuItem
	string MenuItemImages[DSN_ITM_CNT];
	MenuItemImages[ITM_VALUE_ASSIGN] = "images\\Assign.jpg";
	MenuItemImages[ITM_COND] = "images\\Condition.jpg";
	MenuItemImages[ITM_EXIT] = "images\\Exit.jpg";
	MenuItemImages[ITM_START] = "images\\Start.jpg";
	MenuItemImages[ITM_END] = "images\\End.jpg";
	MenuItemImages[ITM_READ] = "images\\Read.jpg";
	MenuItemImages[ITM_WRITE] = "images\\Write.jpg";
	MenuItemImages[ITM_CONNECTOR] = "images\\Connector.jpg";
	//TODO: Prepare images for each menu item and add it to the list

	//Draw menu item one image at a time
	for(int i=0; i<DSN_ITM_CNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

	//Draw a line under the toolbar
	pWind->SetPen(RED, 2);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

	// Draw labels for each item (you can customize the positions and text):
	DrawString(0, UI.ToolBarHeight, "Value Assign");
	DrawString(UI.MenuItemWidth, UI.ToolBarHeight, "Condition");
	DrawString(2 * UI.MenuItemWidth, UI.ToolBarHeight, "Exit");
	DrawString(3 * UI.MenuItemWidth, UI.ToolBarHeight, "Start");
	DrawString(4 * UI.MenuItemWidth, UI.ToolBarHeight, "End");
	DrawString(5 * UI.MenuItemWidth, UI.ToolBarHeight, "Read");
	DrawString(6 * UI.MenuItemWidth, UI.ToolBarHeight, "Write");
	DrawString(7 * UI.MenuItemWidth, UI.ToolBarHeight, "Connector");
}
//////////////////////////////////////////////////////////////////////////////////////////
//TODO: Complete this function
void Output::CreateSimulationToolBar()
{
	UI.AppMode = SIMULATION; // Simulation Mode

	// Fill the toolbar

	// You can draw the toolbar icons in any way you want.
	// Below is one possible way

	// First prepare List of images for each menu item
	// To control the order of these images in the menu,
	// reorder them in DEFS.h ==> enum SimMenuItem
	string MenuItemImages[SIM_ITM_CNT];
	MenuItemImages[ITM_VALIDATE] = "images\\Validate.jpg";
	MenuItemImages[ITM_RUN] = "images\\Run.jpg";
	// TODO: Add more images for additional simulation menu items

	// Draw menu item one image at a time
	for (int i = 0; i < SIM_ITM_CNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

	// Draw a line under the toolbar
	pWind->SetPen(RED, 2);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}

//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar()
{
	//Clear Status bar by drawing a filled white rectangle
	pWind->SetPen(RED, 2);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearDrawArea()
{
	pWind->SetPen(RED, 2);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.DrawingAreaWidth, UI.height - UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearOutputBar()
{
	//Create output bar by drawing a filled rectangle
	pWind->SetPen(RED, 2);
	pWind->SetBrush(LIGHTBLUE);
	pWind->DrawRectangle(UI.DrawingAreaWidth, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::PrintMessage(string msg)	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar
	
	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(10, UI.height - (int) (UI.StatusBarHeight/1.5), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::DrawString(const int iX, const int iY, const string Text)
{
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(iX, iY, Text);
}
//////////////////////////////////////////////////////////////////////////////////////////

//======================================================================================//
//								Statements Drawing Functions								//
//======================================================================================//

//Draw assignment statement and write the "Text" on it
void Output::DrawAssign(Point Left, int width, int height, string Text, bool Selected)
{
	if(Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HighlightColor,3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawColor,3);	//use normal color

	//Draw the statement block rectangle
	pWind->DrawRectangle(Left.x, Left.y, Left.x + width, Left.y + height);
		
	//Write statement text
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(Left.x+width/4, Left.y + height/4, Text);
}

// Draw conditional statement and write the "Text" on it
void Output::DrawConditionalStat(Point Left, int width, int height, string Text, bool Selected)
{
	if (Selected)
		pWind->SetPen(UI.HighlightColor, 3);
	else
		pWind->SetPen(UI.DrawColor, 3);

	// Draw the diamond shape for a conditional statement
	int midX = Left.x + width / 2;
	int midY = Left.y + height / 2;

	pWind->DrawLine(midX, Left.y, Left.x + width, midY);
	pWind->DrawLine(Left.x + width, midY, midX, Left.y + height);
	pWind->DrawLine(midX, Left.y + height, Left.x, midY);
	pWind->DrawLine(Left.x, midY, midX, Left.y);

	// Write statement text
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(midX - width / 4, midY - height / 4, Text);
}

// Draw start statement and write the "Text" on it
void Output::DrawStart(Point Left, int width, int height, string Text, bool Selected)
{
	if (Selected)
		pWind->SetPen(UI.HighlightColor, 3);
	else
		pWind->SetPen(UI.DrawColor, 3);

	// Draw a circle for the start statement
	int midX = Left.x + width / 2;
	int midY = Left.y + height / 2;

	pWind->DrawCircle(midX, midY, width / 2);

	// Write statement text
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(midX - width / 4, midY - height / 4, Text);
}

// Draw end statement and write the "Text" on it
void Output::DrawEnd(Point Left, int width, int height, string Text, bool Selected)
{
	if (Selected)
		pWind->SetPen(UI.HighlightColor, 3);
	else
		pWind->SetPen(UI.DrawColor, 3);

	// Draw an ellipse for the end statement
	int midX = Left.x + width / 2;
	int midY = Left.y + height / 2;

	pWind->DrawEllipse(Left.x, Left.y, Left.x + width, Left.y + height);

	// Write statement text
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(midX - width / 4, midY - height / 4, Text);
}

// Draw read statement and write the "Text" on it
void Output::DrawRead(Point Left, int width, int height, string Text, bool Selected)
{
	if (Selected)
		pWind->SetPen(UI.HighlightColor, 3);
	else
		pWind->SetPen(UI.DrawColor, 3);

	// Draw a parallelogram for the read statement
	int midX = Left.x + width / 2;
	int midY = Left.y + height / 2;

	pWind->DrawLine(midX, Left.y, Left.x + width, Left.y);
	pWind->DrawLine(Left.x + width, Left.y, Left.x + width - width / 4, Left.y + height);
	pWind->DrawLine(Left.x + width - width / 4, Left.y + height, Left.x - width / 4, Left.y + height);
	pWind->DrawLine(Left.x - width / 4, Left.y + height, midX, Left.y);

	// Write statement text
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(midX - width / 4, midY - height / 4, Text);
}

// Draw write statement and write the "Text" on it
void Output::DrawWrite(Point Left, int width, int height, string Text, bool Selected)
{
	if (Selected)
		pWind->SetPen(UI.HighlightColor, 3);
	else
		pWind->SetPen(UI.DrawColor, 3);

	// Draw a parallelogram for the write statement
	int midX = Left.x + width / 2;
	int midY = Left.y + height / 2;

	pWind->DrawLine(Left.x - width / 4, Left.y, midX, Left.y + height);
	pWind->DrawLine(midX, Left.y + height, Left.x + width - width / 4, Left.y + height);
	pWind->DrawLine(Left.x + width - width / 4, Left.y + height, Left.x, Left.y);
	pWind->DrawLine(Left.x, Left.y, Left.x - width / 4, Left.y);

	// Write statement text
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(midX - width / 4, midY - height / 4, Text);
}

// Draw connector line between two points
void Output::DrawConnector(Point Start, Point End, bool Selected)
{
	if (Selected)
		pWind->SetPen(UI.HighlightColor, 3);
	else
		pWind->SetPen(UI.DrawColor, 3);

	// Draw a line between Start and End
	pWind->DrawLine(Start.x, Start.y, End.x, End.y);
}

Output::~Output()
{
	delete pWind;
}
