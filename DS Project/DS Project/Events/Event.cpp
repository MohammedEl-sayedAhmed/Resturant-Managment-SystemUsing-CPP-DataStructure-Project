#include "Event.h"

Event::Event() {  // default constructor
}

Event::Event(int eTime, int ordID) // non-default constructor initializing event with its relevant arguments
{
	eventTime = eTime; // timestep when this event takes place
	orderID	= ordID; // each event is related to a certain order
}

int Event::getEventTime() // get event time; timestep when this event takes place
{
	return eventTime; 
}
int Event::getOrderID() // get order ID for its relevant event
{
	return orderID;
}

double Event::calculateVIPPriority(Order* VIPOrder) { // calculates the VIP order priority using a weighted priority equation
	return (0.5 * VIPOrder->getArrTime() + 0.7 * VIPOrder->getDishes() + 0.2 * VIPOrder->getTotalMoney()); // the weighted priority equation
}

Event::~Event() // event destructor 
{

}

