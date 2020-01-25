#pragma once

#include "..\Defs.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\LinkedList.h"
#include "..\Generic_DS\LinkedQueue.h"
#include "..\Generic_DS\LinkedPQueue.h"
#include "..\Generic_DS\LinkedPQueuePair.h"
#include "..\Events\Event.h"
#include "Cook.h"
#include "Order.h"
#include <string.h>
using namespace std;

// it is the maestro of the project
class Restaurant  
{	
private:

	GUI *pGUI;  // pointer to GUI
		
	int BM;  // number of meals to be completed before taking a break
	int AutoS; // number of timesteps after which an order is automatically promoted to VIP
	
	int NumNCooks;
	int NumGCooks;
	int NumVCooks;

	int AvlNCooks; // number of available normal cooks
	int AvlGCooks; // number of available vegan cooks
	int AvlVCooks; // number of available VIP cooks

	int NOrders; // number of normal orders so far
	int GOrders; // number of vegan orders so far
	int VOrders; // number of VIP orders so far

	int NWOrders; // number of waiting normal orders
	int GWOrders; // number of waiting vegan orders 
	int VWOrders; // number of waiting VIP orders 

	int NumDoneOrders;
	
	int autoProm;  // number of auto-promoted orders so far
	double avgWait; // average of the waiting time so far
	double avgSrv; // average of the serving time so far
	string startSrvNow; // a string with the type and ID of all cooks and orders assigned in the LAST timestep
	ofstream outputFile;

	LinkedQueue<Event*> EventsQueue;	// queue of all events that will be loaded from file

	LinkedQueue<Cook*> NCooks; // queue of all available normal cooks 
	LinkedQueue<Cook*> GCooks; // queue of all available vegan cooks 
	LinkedQueue<Cook*> VCooks; // queue of all available VIP cooks 
	LinkedPQueue<Cook*> inBreakCooks; // priority queue of all in-break cooks with the ones that will finish first dequeued first 


	
	LinkedPQueuePair<Cook*, Order*> inServicePair;


	LinkedList<Order*> waitingNOrders; // linked list of all waiting normal orders 
	LinkedQueue<Order*> waitingGOrders; // queue of all waiting vegan orders 
	LinkedPQueue<Order*> waitingVIPOrders; // priority queue of all waiting VIP orders 

	// in phase 1
	/*LinkedList<Order*> inServiceNOrders; // linked list of all in-service normal orders 
	LinkedQueue<Order*> inServiceGOrders; // queue of all in-service vegan orders 
	LinkedQueue<Order*> inServiceVOrders; // queue of all in-service VIP orders */
	
	// in phase 2
	LinkedList<Order*> inServiceNOrders; // linked list of all in-service normal orders with the ones that will be finished first dequeued first 
	LinkedPQueuePair<Cook*,Order*> inServiceGOrders; // priority queue of all in-service vegan orders with the ones that will be finished first dequeued first 
	LinkedPQueuePair<Cook*,Order*> inServiceVOrders; // priority queue of all in-service VIP orders with the ones that will be finished first dequeued first 
	
	
	LinkedQueue<Order*> finishedNOrders; // queue of normal finished orders 
	LinkedQueue<Order*> finishedGOrders; // queue of vegan finished orders 
	LinkedQueue<Order*> finishedVOrders; // queue of VIP finished orders 

public:

	Restaurant(); // constructor
	~Restaurant(); // destructor

	void RunSimulation(); // runs the simulation 
	void readInputFile(); // read input file and populate relevant lists
	ORD_TYPE charToOrderType(char charOrderType); // maps character of order type to order type enum 
	void ExecuteEvents(int TimeStep); // executes all events at current timestep	
 

	void prepareOrders(int TimeStep); // in phase 1: prepares 1 order from each type // in phase 2: assigns relevant orders to available cooks
	void finishOrders(int CurrentTimeStep, int BM); // in phase 1: finishes 1 order from each type every 5 timesteps // in phase 2: finishes the relevant orders
	void checkBreak(Cook* currCook, int BM, int t);
	void checkBreakEnd(int CurrentTimeStep);
	void autoPromote(int TimeStep,int autoS);
	void addToCookDrawables(); // adds available cooks to the cook quadrant 
	void addToWaitDrawables(); // adds waiting orders to the waiting quadrant 
	void addToSrvDrawables(); // adds in-service orders to the in-service quadrant 
	void addToDoneDrawables(); // adds finished orders to the done quadrant 

	void FillDrawingList(); // fills all the drawing lists

	void addWaitingNOrder(Order*& toBeAddedOrder);
	void addWaitingGOrder(Order*& toBeAddedOrder);
	void addWaitingVIPOrder(Order*& toBeAddedOrder);

	bool removeWaitingNOrder(int toCancelOrder, Order*& cancelledOrder);
	bool removeInserviceNOrder(int toCancelOrder);

	bool isEmptyRest(); // checks if all events have been executed and all lists are empty
	void printRestInfo(int timeStep);
	void printOutFileFooter();
	
	void updateAvgWait(Order* currOrder);
	void updateAvgSrv(Order* currOrder);

};
