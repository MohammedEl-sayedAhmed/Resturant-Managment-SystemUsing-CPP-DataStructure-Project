#include "Rest\Restaurant.h"

#include "GUI\GUIDrawables\NormalGUIElement.h"
#include "GUI\GUIDrawables\VeganGUIElement.h"
#include "GUI\GUIDrawables\VIPGUIElement.h"
#include "GUI\GUI.h"

/*int GUIDemo()
{
	GUI gui;
	gui.initSimMode();

	int steps = 1;

	while(true) {
		if(steps % 5 == 0) {
			gui.printStringInStatusBar("Current Time: " + std::to_string(steps));
		}

		for(int i = 0; i < steps; i++) {
			gui.addGUIDrawable(new VIPGUIElement(i, GUI_REGION::ORD_REG));
			gui.addGUIDrawable(new NormalGUIElement(i, GUI_REGION::COOK_REG));
			gui.addGUIDrawable(new VeganGUIElement(i, GUI_REGION::SRV_REG));
			gui.addGUIDrawable(new VIPGUIElement(i, GUI_REGION::DONE_REG));
		}

		gui.updateInterface();
		gui.handleSimGUIEvents();

		// For Interactive mode
		gui.waitForClick();
		// For step-by-step mode
		gui.sleep(100);
		steps++;
	}
	
	return 0;
}*/

int main() {

	Restaurant* pRest = new Restaurant; // new restaurant object
	pRest->RunSimulation(); // run the simulation
	
	delete pRest; // delete the restaurant object
	
	//GUIDemo();
}