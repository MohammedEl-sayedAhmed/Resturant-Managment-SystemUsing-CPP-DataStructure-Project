#pragma once

#include "Event.h"

// class for the promote event
class PromoteEvent : public Event // class promote event is inherted from the base class event
{
	double orderExtraMoney;	// order extra money

public:

	PromoteEvent(); // default constructor
	PromoteEvent(int tStep, int oID, double oExtraMoney); // non-default constructor initializing the promote event with its relevant arguments

	virtual void Execute(Restaurant* pRest);	// override execute function
};
