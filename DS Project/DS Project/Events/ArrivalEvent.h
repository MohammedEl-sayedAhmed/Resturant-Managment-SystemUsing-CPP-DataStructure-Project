#pragma once

#include "Event.h"
#include "../Rest/Order.h"

//class for the arrival event
class ArrivalEvent: public Event // class arrival event is inherted from the base class event
{
	//info about the order related to arrival event 

	ORD_TYPE orderType;	// order type: normal, vegan, VIP of the new order                
	int orderDishes; // order size of the new order
	double orderMoney; // total order money of the new order

public:
	
	ArrivalEvent(); // default constructor
	ArrivalEvent(ORD_TYPE oType, int tStep, int oID, int oDish, double oMoney); // non-default constructor initializing arrival event with its relevant arguments
	
	virtual void Execute(Restaurant *pRest); // override execute function

private:

	void addOrder(Restaurant* pRest, Order* newOrder); // adds order when executing arrival events to relevant waiting list 
};

