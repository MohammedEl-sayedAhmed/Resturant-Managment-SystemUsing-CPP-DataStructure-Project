#include "Cook.h"

Cook::Cook() // default constructor
{
}

Cook::Cook(int cookID, ORD_TYPE cookOrderType, int cookSpeed, int cookBreakDur) // non-default constructor initializing cook with its relevant arguments
{
	ID = cookID; // each cook has a unique ID 
	type = cookOrderType; // for each order type there is a corresponding type (VIP, Normal, Vegan) cook
	speed = cookSpeed; // dishes it can prepared in one clock tick (in one timestep)
	breakDur = cookBreakDur;  // duration of the break in timesteps
	numOrdersSinceBreak = 0; // number of orders finished by the cook after his/her last break
	TStoTransition = -1;  // timestep at which the cook needs to be transitioned to the next list (from available to in-break OR in-break to available)
}

Cook::~Cook() // default constructor 
{
}

int Cook::getID() const // get cook ID
{
	return ID;
}

ORD_TYPE Cook::getType() const // get cook type
{
	return type;
}
int Cook::getSpeed() const {
	return speed;
}
int Cook::getNumOrders() const {
	return numOrdersSinceBreak;
}
void Cook::incNumOrders() {
	numOrdersSinceBreak++;
}
int Cook::getbreakDur() const {
	return breakDur;
}
