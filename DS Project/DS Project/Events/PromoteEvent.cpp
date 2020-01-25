#include "PromoteEvent.h"
#include "../Rest/Order.h"
#include "..\Rest\Restaurant.h"

PromoteEvent::PromoteEvent() // default constructor
{
	orderExtraMoney = 0;
}

PromoteEvent::PromoteEvent(int tStep, int oID, double oExtraMoney):Event(tStep, oID) // non-default constructor initializing the promote event with its relevant arguments
{
	orderExtraMoney = oExtraMoney; 	// order extra money
}

void PromoteEvent::Execute(Restaurant* pRest)
{
	int toPromoteOrderID = orderID;
	Order* toPromoteOrder;

	if ((pRest->removeWaitingNOrder(toPromoteOrderID, toPromoteOrder))) {
		toPromoteOrder->setTotalMoney(toPromoteOrder->getTotalMoney() + orderExtraMoney);
		toPromoteOrder->setType(TYPE_VIP);
		pRest->addWaitingVIPOrder(toPromoteOrder); // add it to the waiting VIP order list with its calculated priority
		cout << "promote done" << endl;
		return;
	}
	else
	    return;
}
