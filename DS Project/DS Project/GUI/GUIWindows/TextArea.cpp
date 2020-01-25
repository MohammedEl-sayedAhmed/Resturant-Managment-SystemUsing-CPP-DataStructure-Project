#include "TextArea.h"

void TextArea::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();

	target.draw(textAreaContainer, states);
	target.draw(textArea, states);
}

void TextArea::createWindow() {
	textArea.setFont(*font);
	textArea.setFillColor(TEXT_COLOR);
	textArea.setCharacterSize(TEXT_SIZEtextSize);
	textArea.setString(INIT_TEXT);
	textArea.setPosition(5.0f, 5.0f);

	textAreaContainer.setFillColor(TEXT_CONTAINER_COLOR);
	textAreaContainer.setOutlineColor(TEXT_CONTAINER_BORDER_COLOR);
	textAreaContainer.setOutlineThickness(TEXT_CONTAINER_BORDER_THICKNESS);
	textAreaContainer.setPosition(0.0f, 0.0f);
	textAreaContainer.setSize(sf::Vector2f(windowSizeX, windowSizeY));
}

TextArea::TextArea(float windowSizeX, float windowSizeY, sf::Font* font) {
	this->windowSizeX = windowSizeX;
	this->windowSizeY = windowSizeY;
	this->font = font;

	createWindow();
}

void TextArea::printString(std::string text) {
	textArea.setString(text);
}
