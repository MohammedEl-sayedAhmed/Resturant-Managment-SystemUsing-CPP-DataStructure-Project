#include "ArrivalEvent.h"
#include "..\Rest\Restaurant.h"

ArrivalEvent::ArrivalEvent() { // default constructor

}

ArrivalEvent::ArrivalEvent(ORD_TYPE oType, int tStep, int oID, int oDish, double oMoney):Event(tStep, oID) // non-default constructor initializing arrival event with its relevant arguments
{
	orderType = oType; // order type: normal, vegan, VIP of the new order 
	orderDishes = oDish; // order size of the new order
	orderMoney = oMoney; // total order money of the new order
}

void ArrivalEvent::Execute(Restaurant* pRest)  // override execute function
{
        // create an order, fill its data then call the addOrder function of the restaurant object to add the order to the relevant waiting order list
	Order *p = new Order(orderID, orderType, orderDishes, orderMoney, eventTime); 
	addOrder(pRest, p);
}

void ArrivalEvent::addOrder(Restaurant* pRest, Order* newOrder) { // adds order when executing arrival events to relevant waiting list 

	if (newOrder->getType() == TYPE_NRM) { // if the executed arrival event is a normal order
		pRest->addWaitingNOrder(newOrder); // add it to the waiting normal order list
		
	}
	else if (newOrder->getType() == TYPE_VEG) { // if the executed arrival event is a vegan order
		pRest->addWaitingGOrder(newOrder); // add it to the waiting normal order list
	}
	else if (newOrder->getType() == TYPE_VIP) { // if the executed arrival event is a VIP order
		pRest->addWaitingVIPOrder(newOrder, calculateVIPPriority(newOrder)); // add it to the waiting VIP order list with its calculated priority

	}
	return;
}

