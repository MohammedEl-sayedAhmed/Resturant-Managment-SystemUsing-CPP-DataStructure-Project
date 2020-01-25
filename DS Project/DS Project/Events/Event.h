#pragma once

#include "..\Defs.h"
#include "../Rest/Order.h"

class Restaurant; // forward declaration

// The base class for all possible events in the system (abstract class)
class Event
{
protected:

	int eventTime; // timestep when this event takes place
	int orderID; // each event is related to certain order

public:

	Event(); // default constructor
	Event(int eTime, int ordID); // non-default constructor initializing event with its relevant arguments

	//Getters and Setters
	int getEventTime(); // get event time; timestep when this event takes place
	int getOrderID(); // get order ID for its relevant event
	virtual ~Event(); // event destructor 

	double calculateVIPPriority(Order* VIPOrder); // calculates the VIP order priority using a weighted priority equation
	virtual void Execute(Restaurant* pRest)=0; // a function that executes the event (it needds a pointer to "Restaurant")
};
