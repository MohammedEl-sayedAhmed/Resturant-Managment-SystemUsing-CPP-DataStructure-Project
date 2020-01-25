#include "CancelEvent.h"
#include "..\Rest\Restaurant.h"

CancelEvent::CancelEvent() { // default constructor

}

CancelEvent::CancelEvent(int tStep, int oID):Event(tStep, oID) // non-default constructor initializing cancelled event with its relevant arguments
{
	
}

void CancelEvent::Execute(Restaurant* pRest) // override execute function
{	// cancels normal order from waiting list or in-service list

	int toCancelOrderID = orderID;
	Order* cancelledOrder = new Order();
	Order* toCancelOrder = new Order(toCancelOrderID); // a new order with the same ID as the order to be cancelled from the waiting or in-service normal lists
	if (!(pRest->removeWaitingNOrder(toCancelOrder, cancelledOrder))) { // checks if the required order is not in the normal waiting order list
		pRest->removeInserviceNOrder(toCancelOrder); // checks if the required order is in the normal in-service order list
	}
	delete cancelledOrder;
	delete toCancelOrder;
}
