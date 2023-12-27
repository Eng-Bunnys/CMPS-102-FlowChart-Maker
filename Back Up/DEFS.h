#ifndef DEFS_H
#define DEFS_H

// This file contains some global constants and definitions to be used in the project.

enum ConnectorType {
	InletType,
	OutletType,
	BothConnectors
};

enum MODE // Modes of operation
{
	DESIGN,
	SIMULATION
};

enum ActionType // The actions supported
{
	ADD_START,		  // Add start statement
	ADD_END,		  // Add end statement
	ADD_VALUE_ASSIGN, // Add value assignment statement
	ADD_VAR_ASSIGN,	  // Add variable assignment statement
	ADD_OPER_ASSIGN,  // Add operator assignment statement
	ADD_CONDITION,	  // Add a conditional statement (for if and while-loop statements)
	ADD_READ,		  // Add read statement
	ADD_WRITE,		  // Add write statement

	ADD_CONNECTOR, // Add a connector between two statements

	SELECT,	   // Select a statement, a connector
	EDIT_STAT, // Edit a statement

	DEL,   // Delete a figure
	COPY,  // Copy a figure
	CUT,   // Cut a figure
	PASTE, // Paste a figure

	SAVE, // Save the whole graph to a file
	LOAD, // Load a graph from a file

	// SIMULATION MODE

	SWITCH_DSN_MODE, // Switch to Design mode
	SWITCH_SIM_MODE, // Switch to simulation mode

	SIM_VALIDATE,
	SIM_RUN,

	EXIT, // Exit the application

	DRAWING_AREA, // A click on the drawing area
	OUTPUT_AREA,  // A click on the output area
	DSN_TOOL,	  // A click on an empty place in the design tool bar
	STATUS		  // A click on the status bar
};

enum DesignMenuItem
{
	ITM_SELECT,
	ITM_EDIT,
	ITM_SAVE,
	ITM_LOAD,
	ITM_READ,
	ITM_WRITE,
	ITM_VALUE_ASSIGN,
	ITM_VAR_ASSIGN,
	ITM_OP_ASSIGN,
	ITM_COND,
	ITM_START,
	ITM_END,
	ITM_CONNECTOR,
	ITM_PASTE,
	ITM_COPY,
	ITM_DELETE,
	ITM_CHANGE_TO_SIM,
	ITM_EXIT,

	DSN_ITM_CNT
};

enum SimMenuItem // The items of the simulation menu
{
	// Note: Items are ordered here as they appear in menu
	ITM_SELECT_SIM,
	ITM_EDIT_SIM,
	ITM_SAVE_SIM,
	ITM_LOAD_SIM,
	ITM_VALIDATE, // Validate
	ITM_RUN,	  // Run
	ITM_CHANGE_TO_DSN_SIM,
	ITM_EXIT_SIM,

	SIM_ITM_CNT // no. of simulation menu items ==> This should be the last line in this enum

};

#ifndef NULL
#define NULL 0
#endif

#endif