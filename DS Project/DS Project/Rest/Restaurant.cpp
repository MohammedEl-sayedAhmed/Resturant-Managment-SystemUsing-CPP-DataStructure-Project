#include <cstdlib>
#include <time.h>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"
#include "..\Events\CancelEvent.h"
#include "..\Events\PromoteEvent.h"
#include "..\GUI\GUIDrawables\NormalGUIElement.h"
#include "..\GUI\GUIDrawables\VeganGUIElement.h"
#include "..\GUI\GUIDrawables\VIPGUIElement.h"
#include "..\GUI\GUI.h"


Restaurant::Restaurant() // the constructor for the restaurant class
{
	// initilaizing the constructor variables with 0
	pGUI = NULL; 
	autoProm = 0;  
	avgWait = 0;
	avgSrv = 0;
	startSrvNow = "";
	NWOrders = 0;
	GWOrders = 0;
	VWOrders = 0;
	NumDoneOrders = 0;

	string outputFileName;
	cout << "Please enter the desired name for the output file: ";
	cin >> outputFileName;

	outputFile.open(outputFileName + ".txt", ios::out); // opening the output file

	if (outputFile)
	{
		outputFile << "FT ID AT WT ST\n";
	}
	else // if the output file can't be opened
	{
		cout << "Could not generate an output file.\n"; // print error message on the screen
	}
}
bool Restaurant::isEmptyRest() {
	if (EventsQueue.isEmpty()) { // checking if the events queue is empty 
		if ((waitingNOrders.getCount() == 0) && (waitingGOrders.isEmpty()) && (waitingVIPOrders.isEmpty())) { // checking if all the waiting lists are empty 
			if ((inServiceNOrders.getCount() == 0) && (inServiceGOrders.isEmpty()) && (inServiceVOrders.isEmpty())) { // checking if all the in-service lists are empty
				return true;
			}
		}
	}
	return false;
}

void Restaurant::RunSimulation() // running the simulation according to the choosen mode
{
	pGUI = new GUI; // making a new object from GUI 
	PROG_MODE mode = pGUI->getProgramMode(); // getting the program mode 
	int timeStep = 1; // initialize timestep with 1 
	readInputFile(); // reading the input file 

	if ((mode - 1) == MODE_DEMO) {
		//pGUI->initSimMode();
	}
	else if ((mode - 1) == MODE_SLNT) {
		while (true) { // looping until all events are executed and all orders are finished		

			
			ExecuteEvents(timeStep); // execute events of the current timestep
			autoPromote(timeStep, AutoS); // Autopromotion
			prepareOrders(timeStep); // in phase 1: prepare one order from each type
			finishOrders(timeStep, BM);
			checkBreakEnd(timeStep);
			

			timeStep++; // incrementing the current timestep by 1

			if (isEmptyRest()) { // checking if all events are executed and all lists are empty
				printOutFileFooter();
				break;
			}
		}
	}
	else {
		pGUI->initSimMode(); // initializing the simulation mode 
		pGUI->updateInterface(); // updates the interface

		while (true) { // looping until all events are executed and all orders are finished		

			ExecuteEvents(timeStep); // execute events of the current timestep
			autoPromote(timeStep, AutoS); // Autopromotion
			prepareOrders(timeStep); // in phase 1: prepare one order from each type
			finishOrders(timeStep, BM);
			checkBreakEnd(timeStep);
		

			FillDrawingList(); // adds all the IDs for all orders and cooks to thier relevant quadrant in the GUI 
			printRestInfo(timeStep);

			pGUI->updateInterface(); // updates the interface
			pGUI->handleSimGUIEvents(); // handles the simulation GUI events

			if ((mode - 1) == MODE_INTR) {
				pGUI->waitForClick(); // waits for the user click
			}
			else if ((mode - 1) == MODE_STEP) {
				pGUI->sleep(1000);
			}

			timeStep++; // incrementing the current timestep by 1

			if (isEmptyRest()) { // checking if all events are executed and all lists are empty
				printOutFileFooter();
				break;
			}
		}
	}


}


void Restaurant::printRestInfo(int timeStep) {
	string toPrint = "Current Time: " + to_string(timeStep); // add thecurrent time step to string
	toPrint = toPrint + "\nWaiting Normal Orders: " + to_string(NWOrders); // add the number of current waiting orders to string
	toPrint = toPrint + ", Waiting Vegan Orders: " + to_string(GWOrders); // add the number of current waiting vegan orders to string
	toPrint = toPrint + ", Waiting VIP Orders: " + to_string(VWOrders); // add the number of current VIP waiting orders to string

	toPrint = toPrint + "\nAvailable Normal Cooks: " + to_string(AvlNCooks); // add the number of current available normal cooks to string
	toPrint = toPrint + ", Available Vegan Cooks: " + to_string(AvlGCooks); // add the number of current available vegan cooks to string
	toPrint = toPrint + ", Available VIP Cooks: " + to_string(AvlVCooks); // add the number of current VIP normal cooks to string

	toPrint = toPrint + "\nAssigned this Time Step: " + startSrvNow + ".";



	pGUI->printStringInStatusBar(toPrint); // print the relevant data of orders and cooks in the status bar
}

void Restaurant::printOutFileFooter() {
	outputFile << "...................................\n...................................\n";

	int totOrders = NOrders + GOrders + VOrders;
	outputFile << "Order: " << totOrders << " [Norm: " << NOrders << ", Veg: " << GOrders << ", VIP: " << VOrders << "]\n";

	int totCooks = NumNCooks + NumGCooks + NumVCooks;

	outputFile << "Cooks: " << totCooks << " [Norm: " << NumNCooks << ", Veg: " << NumGCooks << ", VIP: " << NumVCooks << "]\n";

	outputFile << "Avg Wait = " << avgWait << ", Avg Serv = " << avgSrv << endl;

	outputFile << "Auto-promoted: " << autoProm;
}


//////////////////////////////////  Event handling functions   /////////////////////////////

void Restaurant::addToCookDrawables() { // adds available cooks to the cook quadrant 

	int loopCounter; // holds the size of the cook lists
	Cook** p; // pointer to pointer (points to array) of type cook; used to print each cook ID in its cook quadrant with its corresponding color

	p = NCooks.toArray(loopCounter); // converting the normal cooks list to an array
	for (int i = 0; i < loopCounter; i++) { // looping over the whole array
		pGUI->addGUIDrawable(new NormalGUIElement(p[i]->getID(), GUI_REGION::COOK_REG)); // for each iteration, it prints each normal cook ID in the cook quadrant with its corresponding color
	}
	delete[] p; // delete the array

	p = GCooks.toArray(loopCounter); // converting the vegan cooks list to an array
	for (int i = 0; i < loopCounter; i++) { // looping over the whole array
		pGUI->addGUIDrawable(new VeganGUIElement(p[i]->getID(), GUI_REGION::COOK_REG)); // for each iteration, it prints each vegan cook ID in the cook quadrant with its corresponding color
	}
	delete[] p; // delete the array

	p = VCooks.toArray(loopCounter); // converting the VIP cooks list to an array
	for (int i = 0; i < loopCounter; i++) { // looping over the whole array
		pGUI->addGUIDrawable(new VIPGUIElement(p[i]->getID(), GUI_REGION::COOK_REG)); // for each iteration, it prints each VIP cook ID in the cook quadrant with its corresponding color
	}
	delete[] p; // delete the array
}

void Restaurant::addToWaitDrawables() { // adds waiting orders to the waiting quadrant 

	int loopCounter; // holds size of the waiting order list
	Order** p; // pointer to pointer -(points to array)- of type order; used to print each order ID in waiting quadrant with its corresponding color

	p = waitingVIPOrders.toArray(loopCounter); // converting the waiting VIP orders list to an array
	for (int i = 0; i < loopCounter; i++) { // looping over the whole array
		pGUI->addGUIDrawable(new VIPGUIElement(p[i]->getID(), GUI_REGION::ORD_REG)); // for each iteration, it prints each VIP order ID in waiting quadrant with its corresponding color
	}
	delete[] p; // delete the array

	p = waitingGOrders.toArray(loopCounter); // converting the waiting vegan orders list to an array
	for (int i = 0; i < loopCounter; i++) { // looping over the whole array
		pGUI->addGUIDrawable(new VeganGUIElement(p[i]->getID(), GUI_REGION::ORD_REG)); // for each iteration, it prints each normal cook ID in waiting quadrant with its corresponding color
	}
	delete[] p; // delete the array

	p = waitingNOrders.toArray(loopCounter); // converting the waiting normal orders list to an array 
	for (int i = 0; i < loopCounter; i++) { // looping over the whole array
		pGUI->addGUIDrawable(new NormalGUIElement(p[i]->getID(), GUI_REGION::ORD_REG)); // for each iteration, it prints each normal order ID in waiting quadrant with its corresponding color
	}
	delete[] p; // delete the array
}

void Restaurant::addToSrvDrawables() { // adds in-service orders to the in-service quadrant 

	int loopCounter; // holds size of in-service order list
	 // pointer to pointer -(points to array)- of type order; used to print each order ID in in-service quadrant with its corresponding color
	Order** p;
	p = inServiceVOrders.OrdertoArray(loopCounter); // converting the in-service VIP orders list to an array
	for (int i = 0; i < loopCounter; i++) { // looping over the whole array
		pGUI->addGUIDrawable(new VIPGUIElement(p[i]->getID(), GUI_REGION::SRV_REG)); // for each iteration, it prints each VIP order ID in in-service quadrant with its corresponding color
	}
	delete[] p; // delete the array

	p = inServiceGOrders.OrdertoArray(loopCounter); // converting the in-service vegan orders list to an array
	for (int i = 0; i < loopCounter; i++) { // looping over the whole array
		pGUI->addGUIDrawable(new VeganGUIElement(p[i]->getID(), GUI_REGION::SRV_REG)); // for each iteration, it prints each vegan order ID in in-service quadrant with its corresponding color
	}
	delete[] p; // delete the array

p = inServiceNOrders.toArray(loopCounter); // converting the in-service normal orders list to an array 
for (int i = 0; i < loopCounter; i++) { // looping over the whole array
	pGUI->addGUIDrawable(new NormalGUIElement(p[i]->getID(), GUI_REGION::SRV_REG)); // for each iteration, it prints each normal order ID in in-service quadrant with its corresponding color
}
delete[] p; // delete the array
}

void Restaurant::addToDoneDrawables() { // adds finished orders to the done quadrant 

	int loopCounter; // holds size of in-service order list
	Order** p; // pointer to pointer -(points to array)- of type order; used to print each order ID in done quadrant with its corresponding color
	
	p = finishedVOrders.toArray(loopCounter); // converting the finished VIP orders list to an array
	for (int i = 0; i < loopCounter; i++) { // looping over the whole array
		pGUI->addGUIDrawable(new VIPGUIElement(p[i]->getID(), GUI_REGION::DONE_REG)); // for each iteration, it prints each VIP order ID in done quadrant with its corresponding color
	}
	delete[] p; // delete the array

	p = finishedGOrders.toArray(loopCounter); // converting the finished vegan orders list to an array 
	for (int i = 0; i < loopCounter; i++) { // looping over the whole array
		pGUI->addGUIDrawable(new VeganGUIElement(p[i]->getID(), GUI_REGION::DONE_REG)); // for each iteration, it prints each vegan order ID in done quadrant with its corresponding color
	}
	delete[] p; // delete the array

	p = finishedNOrders.toArray(loopCounter); // converting the finished normal orders list to an array 
	for (int i = 0; i < loopCounter; i++) { // looping over the whole array
		pGUI->addGUIDrawable(new NormalGUIElement(p[i]->getID(), GUI_REGION::DONE_REG)); // for each iteration, it prints each normal order ID in done quadrant with its corresponding color
	}
	delete[] p; // delete the array
}

void Restaurant::prepareOrders(int TimeStep) { // in phase 1: prepares 1 order from each type // in phase 2: assigns relevant orders to available cooks
	///////////////                                 Re-write in phase 2                  ///////////////
	Order* currOrder; // pointer to current order
	Cook* currCook;
	int FT;
	int pr;
	bool i;
	startSrvNow = "";
	while (waitingVIPOrders.peek(currOrder)) {
		if (VCooks.peekFront(currCook)) {
			FT = TimeStep + ceil((double)currOrder->getDishes() / (double)currCook->getSpeed());
			currOrder->setWaitTime(TimeStep - currOrder->getArrTime());
			currOrder->setServTime(ceil((double)currOrder->getDishes() / (double)currCook->getSpeed()));
			currOrder->setFinishTime(FT);
			waitingVIPOrders.dequeue(currOrder);
			VCooks.dequeue(currCook);
			inServiceVOrders.enqueue(currCook, currOrder, FT);
			VWOrders--;
			AvlVCooks--;
			startSrvNow = startSrvNow + "\nV" + to_string(currCook->getID()) + "(V" + to_string(currOrder->getID()) + ")";

		}
		else if (NCooks.peekFront(currCook)) {
			FT = TimeStep + ceil((double)currOrder->getDishes() / (double)currCook->getSpeed());
			currOrder->setWaitTime(TimeStep - currOrder->getArrTime());
			currOrder->setServTime(ceil((double)currOrder->getDishes() / (double)currCook->getSpeed()));
			currOrder->setFinishTime(FT);
			waitingVIPOrders.dequeue(currOrder);
			NCooks.dequeue(currCook);
			inServiceVOrders.enqueue(currCook, currOrder, FT);
			VWOrders--;
			AvlNCooks--;
			startSrvNow = startSrvNow + "\nN" + to_string(currCook->getID()) + "(V" + to_string(currOrder->getID()) + ")";
		}
		else if (GCooks.peekFront(currCook)) {
			FT = TimeStep + ceil((double)currOrder->getDishes() / (double)currCook->getSpeed());
			currOrder->setWaitTime(TimeStep - currOrder->getArrTime());
			currOrder->setServTime(ceil((double)currOrder->getDishes() / (double)currCook->getSpeed()));
			currOrder->setFinishTime(FT);
			waitingVIPOrders.dequeue(currOrder);
			GCooks.dequeue(currCook);
			inServiceVOrders.enqueue(currCook, currOrder, FT);
			VWOrders--;
			AvlGCooks--;
			startSrvNow = startSrvNow + "\nG" + to_string(currCook->getID()) + "(V" + to_string(currOrder->getID()) + ")";
		}
		else
			break;

	}

	while (waitingGOrders.peekFront(currOrder)) {
		if (GCooks.peekFront(currCook)) {
			FT = TimeStep + ceil((double)currOrder->getDishes() / (double) currCook->getSpeed());
			currOrder->setWaitTime(TimeStep - currOrder->getArrTime());
			currOrder->setServTime(ceil((double)currOrder->getDishes() / (double)currCook->getSpeed()));
			currOrder->setFinishTime(FT);

			waitingGOrders.dequeue(currOrder);
			GCooks.dequeue(currCook);
			inServiceGOrders.enqueue(currCook, currOrder, FT);
			GWOrders--;
			AvlGCooks--;
			startSrvNow = startSrvNow + "\nG" + to_string(currCook->getID()) + "(G" + to_string(currOrder->getID()) + ")";
		}
		else 
			break;

	}
	while (waitingNOrders.ShowFirst(currOrder)) {
		if (NCooks.peekFront(currCook)) {
			waitingNOrders.DeleteFirst(currOrder);
			inServiceNOrders.InsertEnd(currOrder);
			NCooks.dequeue(currCook);
			currOrder->setCook(currCook);
			FT = TimeStep + ceil((double)currOrder->getDishes() / (double)currCook->getSpeed());
			currOrder->setWaitTime(TimeStep - currOrder->getArrTime());
			currOrder->setServTime(ceil((double)currOrder->getDishes() / (double)currCook->getSpeed()));
			currOrder->setFinishTime(FT);
			NWOrders--;
			AvlNCooks--;
			startSrvNow = startSrvNow + "\nN" + to_string(currCook->getID()) + "(N" + to_string(currOrder->getID()) + ")";
		}
		else if (VCooks.peekFront(currCook)) {
			waitingNOrders.DeleteFirst(currOrder);
			inServiceNOrders.InsertEnd(currOrder);
			VCooks.dequeue(currCook);
			currOrder->setCook(currCook);
			FT = TimeStep + ceil((double)currOrder->getDishes() / (double)currCook->getSpeed());
			currOrder->setWaitTime(TimeStep - currOrder->getArrTime());
			currOrder->setServTime(ceil((double)currOrder->getDishes() / (double)currCook->getSpeed()));
			currOrder->setFinishTime(FT);
			NWOrders--;
			AvlVCooks--;
			startSrvNow = startSrvNow + "\nV" + to_string(currCook->getID()) + "(V" + to_string(currOrder->getID()) + ")";
		}
		else
			break;
	}
	return;
}


void Restaurant::checkBreak(Cook* currCook, int BM, int CurrentTimeStep) {
	int pri;
	ORD_TYPE type;
	if (currCook->getNumOrders() < BM) {
		type = currCook->getType();
		switch (type)
		{
		case TYPE_NRM:
			NCooks.enqueue(currCook);
			AvlNCooks++;
			break;
		case TYPE_VEG:
			GCooks.enqueue(currCook);
			AvlGCooks++;
			break;
		case TYPE_VIP:
			VCooks.enqueue(currCook);
			AvlVCooks++;
			break;
		}
	}
	else {
		pri = CurrentTimeStep + currCook->getbreakDur();
		inBreakCooks.enqueue(currCook, pri);
		type = currCook->getType();
		switch (type)
		{
		case TYPE_NRM:
			NCooks.dequeue(currCook);
			break;
		case TYPE_VEG:
			GCooks.dequeue(currCook);
			break;
		case TYPE_VIP:
			VCooks.dequeue(currCook);
			break;
		}
	}
}
void Restaurant::checkBreakEnd(int CurrentTimeStep) {
	Cook* currCook;
	ORD_TYPE type;
	int FT;
	while (inBreakCooks.peek(currCook, FT)) {
		if (FT == CurrentTimeStep) {
			inBreakCooks.dequeue(currCook);
			type = currCook->getType();
			switch (type)
			{
			case TYPE_NRM:
				NCooks.enqueue(currCook);
				AvlNCooks++;
				break;
			case TYPE_VEG:
				GCooks.enqueue(currCook);
				AvlGCooks++;
				break;
			case TYPE_VIP:
				VCooks.enqueue(currCook);
				AvlVCooks++;
				break;
			}
		}
		else
			break;
	}
}
void Restaurant::updateAvgWait(Order* currOrder) {
	avgWait = ((avgWait * (NumDoneOrders - 1)) + currOrder->getWaitTime()) / NumDoneOrders;
}

void Restaurant::updateAvgSrv(Order* currOrder) {
	avgSrv = ((avgSrv * (NumDoneOrders - 1)) + currOrder->getServTime()) / NumDoneOrders;
}

void Restaurant::finishOrders(int CurrentTimeStep, int BM) { // in phase 1: finishes 1 order from each type every 5 timesteps // in phase 2: finishes the relevant orders
	///////////////                                 Re-write in phase 2                  ///////////////
	Order* currOrder; // pointer to current order
	Cook* currCook;
	LinkedPQueue<Order*> toPrint;
	int prior;
	Node<Order*>* p=inServiceNOrders.getHead();
	Order* currNormal;

	while (inServiceVOrders.peek(currCook, currOrder, prior)) {
		if (prior == CurrentTimeStep) {
			inServiceVOrders.dequeue(currCook, currOrder,prior);
			finishedVOrders.enqueue(currOrder);
			NumDoneOrders++;
			updateAvgWait(currOrder);
			updateAvgSrv(currOrder);
			toPrint.enqueue(currOrder, currOrder->getServTime());
			currCook->incNumOrders();
			checkBreak(currCook, BM, CurrentTimeStep);
		}
		else
			break;
	}
	while (inServiceGOrders.peek(currCook, currOrder, prior)) {
		if (prior == CurrentTimeStep) {
			inServiceGOrders.dequeue(currCook, currOrder, prior);
			finishedGOrders.enqueue(currOrder);
			NumDoneOrders++;
			updateAvgWait(currOrder);
			updateAvgSrv(currOrder);
			toPrint.enqueue(currOrder, currOrder->getServTime());
			currCook->incNumOrders();
			checkBreak(currCook, BM, CurrentTimeStep);
		}
		else {
			break;
		}
	}
	while (p) {
		currNormal = p->getItem();
		int currNormalID = currNormal->getID();
		if (currNormal->getFinishTime() == CurrentTimeStep) {
			inServiceNOrders.DeleteNode(currNormalID, currNormal);
			finishedNOrders.enqueue(currNormal);
			NumDoneOrders++;
			updateAvgWait(currNormal);
			updateAvgSrv(currNormal);
			toPrint.enqueue(currNormal, currNormal->getServTime());
			currCook = currNormal->getCook();
			currCook->incNumOrders();
			checkBreak(currCook, BM, CurrentTimeStep);

		}
		p = p->getNext();
	}

	while (!toPrint.isEmpty()) {
		toPrint.dequeue(currOrder);
		currOrder->outputInfoLine(outputFile);
	}
}

/*void Restaurant::genOutputFile() {
	string outputFileName; // the output file name
	cout << "Please enter the desired name of the output file: ";
	cin >> outputFileName; // prompting the user to enter the required output file name

	outputFileName = outputFileName + ".txt"; // adding .txt extension to the file name

	fstream outputFile;
	outputFile.open(outputFileName, ios::out); // opening the output file

	if (outputFile)
	{
		outputFile.close(); // close the input file
	}

	else // if the output file can't be opened
	{
		cout << "Error in loading file.\n"; // print error message on the screen
	}
}*/
void Restaurant::autoPromote(int TimeStep,int autoS){
	Order* toPromoteOrder;
	if (!waitingNOrders.ShowFirst(toPromoteOrder)) {
		cout << "There is no waiting" << endl;
		return;
	}
	while (waitingNOrders.ShowFirst(toPromoteOrder)) {
		int WT = TimeStep - toPromoteOrder->getArrTime();
		if (WT == autoS) {
			int toPromoteOrderID = toPromoteOrder->getID();
			if (removeWaitingNOrder(toPromoteOrderID, toPromoteOrder)) {
				toPromoteOrder->setType(TYPE_VIP);
				addWaitingVIPOrder(toPromoteOrder); // add it to the waiting VIP order list with its calculated priority
				autoProm++;
			}
		}
		else
	
			break;
	}
	return;
}


void Restaurant::ExecuteEvents(int CurrentTimeStep) { //executes aLL events that should take place at current timestep

	Event *pE; // pointer to event
	while( EventsQueue.peekFront(pE) ) // as long as there are more events
	{
		if(pE->getEventTime() > CurrentTimeStep )	// no more events at current timestep
			return;

		pE->Execute(this); 
		EventsQueue.dequeue(pE); // remove event from the queue
		cout << "event done at" << pE->getEventTime() << endl;
		cout << "event done for" << pE->getOrderID() << endl;
		delete pE; // deallocate event object from memory
	}
}


Restaurant::~Restaurant() // destruct all the members from restaurant.h
{ 
	outputFile.close();
	cout << "Output file saved.\n";
	while (!EventsQueue.isEmpty()) {
		Event* pEQ;
		EventsQueue.dequeue(pEQ);
		delete pEQ;
	}

	while (!NCooks.isEmpty()) {
		Cook* pC;
		NCooks.dequeue(pC);
		delete pC;
	}

	while (!GCooks.isEmpty()) {
		Cook* pC;
		GCooks.dequeue(pC);
		delete pC;
	}

	while (!VCooks.isEmpty()) {
		Cook* pC;
		VCooks.dequeue(pC);
		delete pC;
	}

	while (!inBreakCooks.isEmpty()) {
		Cook* pC;
		inBreakCooks.dequeue(pC);
		delete pC;
	}

	while (!waitingNOrders.getCount() == 0) {
		Order* pO;
		waitingNOrders.DeleteFirst(pO);
		delete pO;
	}

	while (!waitingGOrders.isEmpty()) {
		Order* pO;
		waitingGOrders.dequeue(pO);
		delete pO;
	}

	while (!waitingVIPOrders.isEmpty()) {
		Order* pO;
		waitingVIPOrders.dequeue(pO);
		delete pO;
	}

	while (!inServiceNOrders.getCount() ==0) {
		Order* pO;
		inServiceNOrders.DeleteFirst(pO);
		delete pO;
	}

	while (!inServiceGOrders.isEmpty()) {
		Cook* pO;
		Order* qO;
		int priO;
		inServiceGOrders.dequeue(pO,qO, priO);
		delete pO;
	}

	while (!inServiceVOrders.isEmpty()) {
		Cook* pO;
		Order* qO;
		int priO;
		inServiceVOrders.dequeue(pO,qO, priO);
		delete pO;
	}

	while (!finishedNOrders.isEmpty()) {
		Order* pO;
		finishedNOrders.dequeue(pO);
		delete pO;
	}

	while (!finishedGOrders.isEmpty()) {
		Order* pO;
		finishedGOrders.dequeue(pO);
		delete pO;
	}

	while (!finishedVOrders.isEmpty()) {
		Order* pO;
		finishedVOrders.dequeue(pO);
		delete pO;
	}


	delete pGUI;

}

void Restaurant::FillDrawingList()  // fills all the drawing lists
{
	addToCookDrawables(); // adds available cooks to the cook quadrant 
	addToWaitDrawables(); // adds waiting orders to the waiting quadrant 
	addToSrvDrawables(); // adds in-service orders to the in-service quadrant 
	addToDoneDrawables();  // adds finished orders to the done quadrant 
}

ORD_TYPE Restaurant::charToOrderType(char charOrderType) { // maps character of order type to order type enum 
	if (charOrderType == 'N') { // if the order type given in the input file is 'N' 
		return TYPE_NRM; // maps it to enum of type normal
	}

	if (charOrderType == 'G') { // if the order type given in the input file is 'G' 
		return TYPE_VEG;  // maps it to enum of type vegan
	}

	if (charOrderType == 'V') { // if the order type given in the input file is 'V' 
		return TYPE_VIP;  // maps it to enum of type VIP
	}
}

void Restaurant::readInputFile() { // read input file and populate relevant lists
	string inputFileName; // the input file name 
	cout << "Please enter the name of the file (in the current directory) to be loaded: ";
	cin >> inputFileName; // prompting the user to enter the required input file name 

	inputFileName = inputFileName + ".txt"; // adding .txt extension to the file name 

	fstream inputFile;
	inputFile.open(inputFileName, ios::in); // opening the input file 

	if (inputFile)
	{
		// declaring variables to be initiliazed from the input file.
		int SN, SG, SV; // SN = speed of normal cooks || SG = speed of vaegan cooks || SV = speed of VIP cooks
		int BN, BG, BV; // BN = break duration in timesteps for normal cooks || BG = break duration in timesteps for vegan cooks || BV = break duration in timesteps for VIP cooks
		int M; // the number of events following this line
		char eventType; // event type (arrival of a new order, cancellation of an existing order or promotion of an order to be a VIP order)

		inputFile >> SN >> SG >> SV >> AvlNCooks >> AvlGCooks >> AvlVCooks >> BM >> BN >> BG >> BV >> AutoS >> M; // reading the data from the input file and assigning it to its relevant variables

		NumNCooks = AvlNCooks;
		NumGCooks = AvlGCooks;
		NumVCooks = AvlVCooks;

		for (int i = 0; i < AvlNCooks; i++) { 
			Cook *p = new Cook(i+1, TYPE_NRM, SN, BN); // create a new cook object with type normal and a given speed and break duaration in timesteps, its ID is set uniquely
			NCooks.enqueue(p); // enqueueing the new normal cook in normal cooks list
		}
		
		for (int i = 0; i < AvlGCooks; i++) {
			Cook* p = new Cook(i + AvlNCooks + 1, TYPE_VEG, SG, BG); // create a new cook object with type normal and a given speed and break duaration in timesteps, its ID is set uniquely
			GCooks.enqueue(p); // enqueueing the new vegan cook in vegan cooks list
		}
		
		for (int i = 0; i < AvlVCooks; i++) {
			Cook* p = new Cook(i + AvlGCooks + AvlNCooks + 1 , TYPE_VIP, SV, BV); // create a new cook object with type normal and a given speed and break duaration in timesteps, its ID is set uniquely
			VCooks.enqueue(p); // enqueueing the new VIP cook in VIP cooks list
		}

		for (int i = 0; i < M; i++) // looping over the number of events in the input file 
		{
			inputFile >> eventType; 

			if (eventType == 'R') { // event type is arrival of a new order
				char oType; // arrival order type given from the input file
				int tStep; // timestep at which the order is arrived 
				int oID; // arrival order ID given from the input file
				int oDish; // arrival order size given from the input file
				double oMoney; // arrival order total money given from the input file

				inputFile >> oType >> tStep >> oID >> oDish >> oMoney;
				
				Event *p = new ArrivalEvent(charToOrderType(oType), tStep, oID, oDish, oMoney); // create a new event object with type arrival event and passing to it its relevant  parametrs from the input file
				EventsQueue.enqueue(p); // enqueueing the new arrival event in events queue list
			}
			else if (eventType == 'X') { // event type is cancellation of an existing normal order
				int tStep; // timestep at which the order will be cancelled
				int oID; // cancelled order ID given from the input file
			
				inputFile >> tStep >> oID;

				Event* p = new CancelEvent(tStep, oID);// create a new event object with type cancel event and passing to it its relevant parametrs from the input file
				EventsQueue.enqueue(p); // enqueueing the cancelled event in events queue list
			}
			else if (eventType == 'P') { // event type is promotion of a normal order to be a VIP order
				
				int tStep; // timestep at which the order will be promoted
				int oID; // promoted order ID given from the input file
				double oExtraMoney; // promoted order extra money

				inputFile >> tStep >> oID >> oExtraMoney;

				Event* p = new PromoteEvent(tStep, oID, oExtraMoney);// create a new event object with type promoted event and passing to it its relevant parametrs from the input file
				EventsQueue.enqueue(p); // enqueueing the promoted event in events queue list
			}
		}

		inputFile.close(); // close the input file
	}
	else // if the input file can't be opened 
	{
		cout << "Error in loading file.\n"; // print error message on the screen
	}
}
void Restaurant::addWaitingNOrder(Order*& toBeAddedOrder) { // adder function for adding order to waiting normal order list
	waitingNOrders.InsertEnd(toBeAddedOrder); // add it to the waiting normal order list
	NWOrders++; // incrementing number of normal waiting orders in the waiting normal order list
	NOrders++; // incrementing number of normal orders in the whole program
	return;
}

void Restaurant::addWaitingGOrder(Order*& toBeAddedOrder) { // adder function for adding order to waiting normal order list
	waitingGOrders.enqueue(toBeAddedOrder); // add it to the waiting vegan order list
	GWOrders++; // incrementing number of vegan waiting orders in the waiting vegan order list
	GOrders++; // incrementing number of vegan orders in the whole program
	return;
}


void Restaurant::addWaitingVIPOrder(Order*& toBeAddedOrder) { // adder function for adding order to waiting normal order list
	double priority = 0.5 * toBeAddedOrder->getArrTime() + 0.7 * toBeAddedOrder->getDishes() + 0.2 * toBeAddedOrder->getTotalMoney();
	waitingVIPOrders.enqueue(toBeAddedOrder, priority); // add it to the waiting VIP order list with its calculated priority
	VWOrders++; // incrementing number of VIP waiting orders in the waiting VIP order list
	VOrders++; // incrementing number of VIP orders in the whole program
	return;
}


bool Restaurant::removeWaitingNOrder(int toCancelOrderID, Order*& cancelledOrder) {
	bool deletedOrder = waitingNOrders.DeleteNode(toCancelOrderID, cancelledOrder);
	if (deletedOrder) {
		NWOrders--; // decrementing the number of normal orders in the normal waiting order list
		NOrders--; // decrementing the number of normal orders in the whole program
		cout << "removeNWorder" << endl;
	}
	return deletedOrder;
}

bool Restaurant::removeInserviceNOrder(int toCancelOrderID) {
	Order* cancelledOrder = new Order();
	Cook* cancelledCook;
	//ORD_TYPE type;
	bool deletedOrder = inServiceNOrders.DeleteNode(toCancelOrderID, cancelledOrder);
	cancelledCook = cancelledOrder->getCook();
	//type = cancelledCook->getType();
	NCooks.enqueue(cancelledCook);
	AvlNCooks++;
	if (deletedOrder) {
		NOrders--; // decrementing the number of normal orders in the whole program
		/*switch (type)
		{
		case TYPE_NRM:
			NCooks.enqueue(cancelledCook);
			AvlNCooks++;
			break;
		case TYPE_VEG:
			GCooks.enqueue(cancelledCook);
			AvlGCooks++;
			break;
		case TYPE_VIP:
			VCooks.enqueue(cancelledCook);
			AvlVCooks++;
			break;
		}*/
	}
	delete cancelledOrder;
	return deletedOrder;
}
