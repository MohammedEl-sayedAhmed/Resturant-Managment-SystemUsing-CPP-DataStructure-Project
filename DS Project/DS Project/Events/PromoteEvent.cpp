#include "PromoteEvent.h"
#include "../Rest/Order.h"
#include "..\Rest\Restaurant.h"

PromoteEvent::PromoteEvent() // default constructor
{
}

PromoteEvent::PromoteEvent(int tStep, int oID, double oExtraMoney):Event(tStep, oID) // non-default constructor initializing the promote event with its relevant arguments
{
	orderExtraMoney = oExtraMoney; 	// order extra money
}

void PromoteEvent::Execute(Restaurant* pRest)
{
	int toPromoteOrderID = orderID;
	Order* tempOrder = new Order(toPromoteOrderID);
	Order* toPromoteOrder = new Order(toPromoteOrderID);

	if ((pRest->removeWaitingNOrder(tempOrder, toPromoteOrder))) {

		toPromoteOrder->setTotalMoney(toPromoteOrder->getTotalMoney() + orderExtraMoney);
		toPromoteOrder->setType(TYPE_VIP);

		pRest->addWaitingVIPOrder(toPromoteOrder, calculateVIPPriority(toPromoteOrder)); // add it to the waiting VIP order list with its calculated priority
	}

	delete tempOrder; // delete the temporarily created order
	return;
}
