#include "Order.h"

Order::Order() // default constructor 
{
}

Order::Order(int id) // initializing order with its ID only (used while order cancellation)
{
	ID = (id > 0 && id < 1000) ? id : 0; // order id ranged from 0 to 999  
}

Order::Order(int id, ORD_TYPE orderType, int orderDishes, double orderTotalMoney, int orderArrTime) // non-default constructor initializing order with its relevant arguments
{
	ID = (id> 0 && id < 1000) ? id : 0; // order id ranged from 0 to 999
	type = orderType; // order type: normal, vegan or VIP
	dishes = orderDishes; // order size
	totalMoney = orderTotalMoney; // total order money
	arrTime = orderArrTime; // order arrival time
	waitTime = 0; // order waiting time
    itsCook = nullptr; // pointer to the cook to which the order is assigned
}

Order::~Order() // default constructor
{
}

int Order::getID() const // get order ID
{
	return ID;
}

double Order::getTotalMoney() const // get order total money
{
	return totalMoney;
}

int Order::getArrTime() const// get order arrival time 
{
	return arrTime;
}

int Order::getDishes() const // get order size
{
	return dishes;
}

ORD_TYPE Order::getType() const // get order type
{
	return type;
}

void Order::setTotalMoney(double totMoney) { // get order total money 
	totalMoney = totMoney;
}

void Order::setType(ORD_TYPE otype) {
	type = otype;
}

bool Order::operator ==(Order toCompare) {
        // compare the IDs of the 2 orders
	return  (ID == toCompare.getID());
}
