#include "StartingScreen.h"


void StartingScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(logo);
	target.draw(ModeTextInputContainer);
	target.draw(ModeTextInput);
}

void StartingScreen::createLogo(std::string fileName) {
	sf::Texture* logoImage = new sf::Texture;
	if (!logoImage->loadFromFile(fileName)) {
		std::cerr << "Error: The logo image couldn't be found\n";
	}

	int logoSizeY = logoImage->getSize().y;
	int logoSizeX = logoImage->getSize().x;

	logo.setTexture(*logoImage);
	logo.setTextureRect(sf::IntRect(0, 0, logoSizeX, logoSizeY));

	logo.setOrigin(sf::Vector2f(logoSizeX / 2.0f, logoSizeY / 2.0f));
	logo.setPosition(sf::Vector2f(windowSizeX / 2.0f, logoSizeY / 2.0f));
}

void StartingScreen::createModeTextInput() {

	ModeTextInput.setFont(*font);

	ModeTextInput.setString(msg);
	ModeTextInput.setCharacterSize(18);

	ModeTextInput.setFillColor(sf::Color::Blue);
	ModeTextInput.setOutlineColor(sf::Color::Black);
	ModeTextInput.setPosition(25.0f, logo.getTexture()->getSize().y + 25.0f);

	sf::FloatRect dim = ModeTextInput.getGlobalBounds();

	ModeTextInputContainer.setFillColor(sf::Color::White);
	ModeTextInputContainer.setPosition(dim.left - 5, dim.top - 5);
	ModeTextInputContainer.setOutlineThickness(5);
	ModeTextInputContainer.setOutlineColor(sf::Color::Black);
	ModeTextInputContainer.setSize(sf::Vector2f(windowSizeX - ModeTextInputContainer.getPosition().x - 25, dim.height));
}

StartingScreen::StartingScreen(float windowSizeX, float windowSizeY, std::string logoFileName, sf::Font* font) {
	this->windowSizeX = windowSizeX;
	this->windowSizeY = windowSizeY;
	this->font = font;

	currentMode = PROG_MODE::MODE_CNT;

	createLogo(logoFileName);
	createModeTextInput();
}

void StartingScreen::showModeChoice(std::string userInput) {
	char numChar = userInput[0];
	int num = numChar - '0';
	if (num >= 0 && num < PROG_MODE::MODE_CNT) {
		currentMode = (PROG_MODE)num;
		ModeTextInput.setString(msg + "\nYour choice is " + userInput + ", Press enter to continue\n");
	}
	else {
		ModeTextInput.setString(msg + "\nYour choice is " + userInput + ", Choose proper value\n");
	}
}

PROG_MODE StartingScreen::getMode() {
	if (currentMode == PROG_MODE::MODE_CNT) {
		std::cerr << "Choose first\n";
		ModeTextInput.setString(msg + "\nChoose First\n");
	}
	return currentMode;
}

StartingScreen::~StartingScreen() {
	delete logo.getTexture();
}


