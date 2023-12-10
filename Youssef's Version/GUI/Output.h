#ifndef OUPTUT_H
#define OUPTUT_H

#include "Input.h"

class Output	//The application manager should have a pointer to this class
{
private:	
	window* pWind;	//Pointer to the Graphics Window
	int ConnectorWidth;
public:
	Output();	

	window* CreateWind(int, int, int , int);
	Input* CreateInput(); //Creates a pointer to the Input object	

	void CreateStatusBar(); //Creates status bar

	void CreateStaticToolbar();

	void CreateDesignToolBar();	//Tool bar of the design mode
	void CreateSimulationToolBar(); //Tool bar of the simulation mode

	void ClearStatusBar();	//Clears the status bar
	void ClearDrawArea();	//Clears the drawing area
	void ClearOutputBar(); //Clears the Output bar
	
	void PrintMessage(string msg);	//Prints a message on Status bar
	void DrawString(const int, const int, const string);  //Writes a string in the specified location

	// -- Statements Drawing Functions
	void DrawAssign(Point Left, int width, int height, string Text, bool Selected=false);

	void DrawConditionalStat(Point Left, int width, int height, string Text, bool Selected = false);
	void DrawStart(Point Left, int width, int height, string Text, bool Selected = false);
	void DrawEnd(Point Left, int width, int height, string Text, bool Selected = false);
	void DrawRead(Point Left, int width, int height, string Text, bool Selected = false);
	void DrawWrite(Point Left, int width, int height, string Text, bool Selected = false);
	void DrawConnector(Point Start, Point End, bool Selected = false);

	~Output();
};

#endif