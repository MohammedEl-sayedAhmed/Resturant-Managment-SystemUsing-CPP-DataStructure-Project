#pragma once
#include<iostream>

#include<SFML\Graphics\Drawable.hpp>
#include<SFML\Graphics\Transformable.hpp>
#include<SFML\Graphics.hpp>

#include"..\GUIDrawables\GUIDrawable.h"

class MainScreen : public sf::Drawable, public sf::Transformable {

private:
	float windowSizeX, windowSizeY;
	sf::Font* font;

	sf::VertexArray vline, hline;

	sf::Text regionLabels;
	sf::RectangleShape regionLablesBoundingBox;

	// User LOGIC parameters
	sf::Text** textElements = NULL;
	int textElementsSize = 0;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void createMainScreen();

public:
	
	MainScreen(float windowSizeX, float windowSizeY, sf::Font* font);
	void clearUserElements();
	void drawUserGUIElements(GUIDrawable** userDrawableElementsList, int userDrawableElementsListSize);

};

