#include "VeganGUIElement.h"

const sf::Color VeganGUIElement::textColor = sf::Color::Green;


sf::Text* VeganGUIElement::getGUIElement(sf::Font* font, float positionX, float positionY) {
	sf::Text* text = new sf::Text();
	text->setFont(*font);
	text->setCharacterSize(getTextSize());
	text->setString(std::to_string(this->getID()));
	text->setFillColor(textColor);
	text->setPosition(positionX, positionY);

	return text;
}