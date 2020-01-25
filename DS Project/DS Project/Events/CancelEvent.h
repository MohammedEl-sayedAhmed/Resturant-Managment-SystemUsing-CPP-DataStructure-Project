#pragma once

#include "Event.h"

// class for the cancel event
class CancelEvent : public Event // class cancel event is inherted from the base class event
{
public:

	CancelEvent(); // default constructor
	CancelEvent(int tStep, int oID); // non-default constructor initializing cancelled event with its relevant arguments

	virtual void Execute(Restaurant* pRest); // override execute function	
};
