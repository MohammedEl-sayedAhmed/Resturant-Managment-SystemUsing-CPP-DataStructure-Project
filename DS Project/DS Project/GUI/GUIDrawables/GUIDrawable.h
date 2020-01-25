#pragma once
#include<SFML\Graphics.hpp>

#include"..\GUIDefs.h"

class GUIDrawable
{
private:
	// LOGIC paramters
	int ID;
	GUI_REGION currentRegion;

	// GUI parameters
	const int textSize = 18;

public:
	GUIDrawable(int id, GUI_REGION currentRegion);
	virtual sf::Text* getGUIElement(sf::Font* font, float positionX, float positionY) = 0;

	int getID();
	GUI_REGION getCurrentRegion();
	int getTextSize();
};

