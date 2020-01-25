#pragma once
#include<iostream>

#include<SFML/Graphics/Drawable.hpp>
#include<SFML/Graphics/Transformable.hpp>
#include<SFML/Graphics.hpp>

#include"../../Defs.h"


class StartingScreen : public sf::Drawable, public sf::Transformable {

private:
	float windowSizeX, windowSizeY;
	sf::Font* font;

	sf::Sprite logo;

	sf::RectangleShape ModeTextInputContainer;
	sf::Text ModeTextInput;

	const std::string msg = "Choose the mode\n\t1-interactive mode\n\t2-Step-by-step mode\
			\n\t3-Silent mode\n\t4-Demo mode (for introductory phase only, should be removed in phases 1&2)\n";

	PROG_MODE currentMode;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void createLogo(std::string fileName);
	void createModeTextInput();

public:
	StartingScreen(float windowSizeX, float windowSizeY, std::string logoFileName, sf::Font* font);
	void showModeChoice(std::string userInput);
	PROG_MODE getMode();
	~StartingScreen();
};

