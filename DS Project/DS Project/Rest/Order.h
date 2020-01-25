#pragma once

#include "..\Defs.h"
#include "Cook.h"
#include <fstream>
using namespace std;

class Order
{
protected:

	int ID; // each order has a unique ID (from 1 --> 999)
	ORD_TYPE type; // order type: Normal, Vegan, VIP
	int dishes;	// the number of dishes in that order              
	double totalMoney; // total order  money
	int arrTime; // arrival time for that order
	int waitTime; // waiting time for that order
	int finishTime;
	int servTime;
    Cook *itsCook; // pointer to the cook to which the order is assigned

public:

	Order(); // default constructor 
	Order(int id); // non-default constructor initializing order with its ID only (used while order cancellation) 
	Order(int id, ORD_TYPE orderType, int orderDishes, double orderTotalMoney, int orderArrTime); // non-default constructor initializing order with its relevant arguments
	virtual ~Order(); // order destructor 

	bool operator ==(Order toCompare); // operator overloading used in the cancellation event

	//Getters and Setters
	int getID() const; // get order ID
	double getTotalMoney() const; // get order total money
	int getArrTime() const; // get order arrival time 
	void setWaitTime(int t);
	void setFinishTime(int time);
	int getFinishTime()const;
	int getDishes() const; // get order size 
	ORD_TYPE getType() const; // get order type
	void setTotalMoney(int Money);
	void setType(ORD_TYPE otype);
	void setCook(Cook* c);
	Cook* getCook();
	void setServTime(int time);
	int getWaitTime()const;
	int getServTime()const;
	void outputInfoLine(ofstream& outputFile) const;
};
