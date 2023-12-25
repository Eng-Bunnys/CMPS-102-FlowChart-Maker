#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "DEFS.h"

#include "Statements\Statement.h"
#include "Statements/Connector.h"
class Input;
class Output;


//Main class that manages everything in the application.
class ApplicationManager
{
	enum { MaxCount = 200 };	//Max no of statements/connectors in a single flowchart

private:
	int StatCount;		//Actual number of statements
	int ConnCount;		//Actual number of connectors
	Statement* StatList[MaxCount];	//List of all statements (Array of pointers)
	Connector* ConnList[MaxCount];	//List of all connectors (Array of pointers)
	Statement* SelectedStatements[MaxCount];

	Statement* pSelectedStat; //a pointer to the last selected statement
	//you can set and get this pointer
	Statement* pClipboard;    //a pointer to the last copied/cut statement
	//you can set and get this pointer

//Pointers to Input and Output classes
	Input* pIn;
	Output* pOut;

public:
	ApplicationManager();
	~ApplicationManager();

	// == Actions Related Functions ==
	ActionType GetUserAction() const; //Reads the input command from the user 
	//and returns the corresponding action type
	void ExecuteAction(ActionType);  //Creates an action and executes it

	// Adds a selected statement to the list of selected statements
	void AddSelected(Statement* pStat);
	// Removes a selected statement from the list of selected statements
	void RemoveSelected(Statement* pStat);
	// Clears the list of selected statements
	void EmptySelectedList();
	// Updates the interface to show the selected statements
	void UpdateSelectedInterface() const;

	// == Statements/Connector Management Functions ==
	void AddStatement(Statement* pStat);    //Adds a new Statement to the Flowchart
	Statement* GetStatement(Point P) const;	//Searches for a statement where point P belongs
	//TODO: Complete its implementation 
	//      WITHOUT breaking class responsibilities

	void AddConnector(Connector* pConn);    //Adds a new Connector to the Flowchart
	Connector* GetConnector(Point P) const;	//search for a Connector where point P belongs

	// Note: you should use the following 4 functions 
	//       in order not to break class responsibilities (especially in copy, cut and paste)
	Statement* GetSelectedStatement() const;	 //Returns the selected Statement
	void SetSelectedStatement(Statement* pStat); //Set the Statement selected by the user
	Statement* GetClipboard() const;	         //Returns the Clipboard
	void SetClipboard(Statement* pStat);         //Set the Clipboard

	// == Interface Management Functions ==
	Input* GetInput() const;        //Return pointer to the input
	Output* GetOutput() const;      //Return pointer to the output
	void UpdateInterface() const;	//Redraws all the drawing window

};

#endif