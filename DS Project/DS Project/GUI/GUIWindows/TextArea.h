#pragma once
#include<iostream>

#include<SFML/Graphics/Drawable.hpp>
#include<SFML/Graphics/Transformable.hpp>
#include<SFML/Graphics.hpp>


class TextArea : public sf::Drawable, public sf::Transformable {
private:
	float windowSizeX, windowSizeY;
	sf::Font* font;

	sf::RectangleShape textAreaContainer;
	sf::Text textArea;

	const std::string INIT_TEXT = "Welcome, this is the text area\n";
	const sf::Color TEXT_COLOR = sf::Color::Blue;
	const sf::Color TEXT_CONTAINER_COLOR = sf::Color::White;
	const sf::Color TEXT_CONTAINER_BORDER_COLOR = sf::Color::Black;
	const float TEXT_CONTAINER_BORDER_THICKNESS = 5.0f;
	const int TEXT_SIZEtextSize = 16;
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void createWindow();

public:
	TextArea(float windowSizeX, float windowSizeY, sf::Font* font);
	void printString(std::string text);
};

