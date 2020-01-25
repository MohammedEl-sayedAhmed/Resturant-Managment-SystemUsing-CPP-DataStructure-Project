#pragma once
#include "GUIDrawable.h"
#include "..\GUIDefs.h"

class VIPGUIElement : public GUIDrawable {

private:
	static const sf::Color textColor;

public:
	VIPGUIElement(int id, GUI_REGION region) :GUIDrawable(id, region) {}
	virtual sf::Text* getGUIElement(sf::Font* font, float positionX, float positionY);
};

