#include "VIPGUIElement.h"

// Violet
const sf::Color VIPGUIElement::textColor = sf::Color(138, 43, 226);


sf::Text* VIPGUIElement::getGUIElement(sf::Font* font, float positionX, float positionY) {
	sf::Text* text = new sf::Text();
	text->setFont(*font);
	text->setCharacterSize(getTextSize());
	text->setString(std::to_string(this->getID()));
	text->setFillColor(textColor);
	text->setPosition(positionX, positionY);

	return text;
}