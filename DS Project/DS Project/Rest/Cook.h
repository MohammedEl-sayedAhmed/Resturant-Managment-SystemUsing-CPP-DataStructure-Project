#pragma once

#include "..\Defs.h"

class Cook
{
protected:

	int ID; // each cook has a unique ID 
	ORD_TYPE type;	// for each order type there is a corresponding cook type (VIP, Normal, Vegan)
	int speed;		// dishes the cook can prepare in one timestep
	int breakDur; // duration of the break in timesteps
	int numOrdersSinceBreak; // number of orders finished by the cook after his/her last break
	int TStoTransition; // timestep at which the cook needs to be transitioned to the next list (from available to in-break OR in-break to available) 

public:

	Cook(); // default constructor 
	Cook(int cookID, ORD_TYPE cookOrderType, int cookSpeed, int cookBreakDur); // non-default constructor initializing cook with its relevant arguments
	virtual ~Cook(); // cook destructor 

	//Getters and Setters 
	int getID() const; // get cook ID
	ORD_TYPE getType() const; // get cook type (normal, vegan or VIP)
};
