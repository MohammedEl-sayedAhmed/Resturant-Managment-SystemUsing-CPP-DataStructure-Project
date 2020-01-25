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
	Order* cancelledOrder;
	if (!(pRest->removeWaitingNOrder(toCancelOrderID, cancelledOrder))) { // checks if the required order is not in the normal waiting order list
		pRest->removeInserviceNOrder(toCancelOrderID); // checks if the required order is in the normal in-service order list
		cout<<"cancel done"<<endl;
		return;
	}
	else
		cout << "cancel done" << endl;
		return;
}
