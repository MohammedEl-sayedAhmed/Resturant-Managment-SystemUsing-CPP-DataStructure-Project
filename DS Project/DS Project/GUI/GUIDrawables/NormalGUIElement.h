#pragma once
#include "GUIDrawable.h"
#include "..\GUIDefs.h"

class NormalGUIElement : public GUIDrawable {
private:
	static const sf::Color textColor;

public:
	NormalGUIElement(int id, GUI_REGION region) :GUIDrawable(id, region) {}
	virtual sf::Text* getGUIElement(sf::Font* font, float positionX, float positionY);
};

