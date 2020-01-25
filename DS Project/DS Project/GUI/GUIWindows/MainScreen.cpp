#include "MainScreen.h"

MainScreen::MainScreen(float windowSizeX, float windowSizeY, sf::Font* font) {
	this->windowSizeX = windowSizeX;
	this->windowSizeY = windowSizeY;
	this->font = font;

	createMainScreen();
}


void MainScreen::clearUserElements() {
	for(int i = 0; i < textElementsSize; i++) {
		delete textElements[i];
	}
	textElementsSize = 0;
	textElements = NULL;
}

void MainScreen::drawUserGUIElements(GUIDrawable** userDrawableElementsList, int userDrawableElementsListSize) {
	textElementsSize = userDrawableElementsListSize;
	textElements = new sf::Text * [textElementsSize];

	sf::FloatRect dim = this->regionLablesBoundingBox.getGlobalBounds();

	const float ELEMENT_SIZE = 30;
	const int MAX_ELEMENTS_PER_ROW = 10;

	const float ordRegBasePositionX = dim.left - 10;
	const float ordRegBasePositionY = dim.top;

	const float cookRegBasePositionX = dim.left + dim.width + 10;
	const float cookRegBasePositionY = dim.top;

	const float srvgRegBasePositionX = dim.left + dim.width + 10;
	const float srvgRegBasePositionY = dim.top + dim.height - ELEMENT_SIZE;

	const float doneRegBasePositionX = dim.left - 10;
	const float doneRegBasePositionY = dim.top + dim.height - ELEMENT_SIZE;

	int ordRegCurrentOrder, cookRegCurrentOrder, srvgRegCurrentOrder, doneRegCurrentOrder;
	ordRegCurrentOrder = cookRegCurrentOrder = srvgRegCurrentOrder = doneRegCurrentOrder = 0;


	for(int i = 0; i < textElementsSize; i++) {

		switch(userDrawableElementsList[i]->getCurrentRegion()) {
		case ORD_REG:
		{
			float posY = ordRegBasePositionY - (ELEMENT_SIZE * ( int) (ordRegCurrentOrder / MAX_ELEMENTS_PER_ROW));
			float posX = ordRegBasePositionX - (ELEMENT_SIZE * ((ordRegCurrentOrder % MAX_ELEMENTS_PER_ROW) + 1));

			textElements[i] = userDrawableElementsList[i]->getGUIElement(font, posX, posY);
			ordRegCurrentOrder++;
		}
		break;
		case COOK_REG:
		{
			float posY = cookRegBasePositionY - (ELEMENT_SIZE * ( int) (cookRegCurrentOrder / MAX_ELEMENTS_PER_ROW));
			float posX = cookRegBasePositionX + (ELEMENT_SIZE * (cookRegCurrentOrder % MAX_ELEMENTS_PER_ROW));

			textElements[i] = userDrawableElementsList[i]->getGUIElement(font, posX, posY);
			cookRegCurrentOrder++;
		}
		break;
		case SRV_REG:
		{
			float posY = srvgRegBasePositionY + (ELEMENT_SIZE * ( int) (srvgRegCurrentOrder / MAX_ELEMENTS_PER_ROW));
			float posX = srvgRegBasePositionX + (ELEMENT_SIZE * (srvgRegCurrentOrder % MAX_ELEMENTS_PER_ROW));

			textElements[i] = userDrawableElementsList[i]->getGUIElement(font, posX, posY);
			srvgRegCurrentOrder++;
		}
		break;
		case DONE_REG:
		{
			float posY = doneRegBasePositionY + (ELEMENT_SIZE * ( int) (doneRegCurrentOrder / MAX_ELEMENTS_PER_ROW));
			float posX = doneRegBasePositionX - (ELEMENT_SIZE * ((doneRegCurrentOrder % MAX_ELEMENTS_PER_ROW) + 1));

			textElements[i] = userDrawableElementsList[i]->getGUIElement(font, posX, posY);
			doneRegCurrentOrder++;
		}
		break;
		case REG_CNT:
			std::cerr << "Wrong Region Enum\n";
			break;
		default:
			break;
		}

	}
}

void MainScreen::createMainScreen() {
	vline.setPrimitiveType(sf::Lines);
	vline.append(sf::Vertex(sf::Vector2f(windowSizeX / 2, 0), sf::Color::Black));
	vline.append(sf::Vertex(sf::Vector2f(windowSizeX / 2, windowSizeY), sf::Color::Black));
	
	hline.setPrimitiveType(sf::Lines);
	hline.append(sf::Vertex(sf::Vector2f(0, windowSizeY / 2), sf::Color::Black));
	hline.append(sf::Vertex(sf::Vector2f(windowSizeX, windowSizeY / 2), sf::Color::Black));


	regionLabels.setCharacterSize(18);
	regionLabels.setString("WAIT\tCOOK\nDONE\tSRVG\n");
	regionLabels.setFont(*font);
	regionLabels.setFillColor(sf::Color::White);
	regionLabels.setOrigin(regionLabels.getLocalBounds().width / 2, regionLabels.getLocalBounds().height / 2);
	regionLabels.setPosition(windowSizeX / 2 + 3, windowSizeY / 2 + 3);

	sf::FloatRect r = regionLabels.getGlobalBounds();
	regionLablesBoundingBox.setFillColor(sf::Color::Red);
	regionLablesBoundingBox.setOutlineThickness(5);
	regionLablesBoundingBox.setOutlineColor(sf::Color::Black);
	regionLablesBoundingBox.setPosition(sf::Vector2f(r.left - 15, r.top - 15));
	regionLablesBoundingBox.setSize(sf::Vector2f(r.width + 30, r.height + 15));
}


void MainScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(regionLablesBoundingBox, states);
	target.draw(regionLabels, states);
	target.draw(vline, states);
	target.draw(hline, states);

	for(int i = 0; i < textElementsSize; i++) {
		target.draw(*(textElements[i]), states);
	}
}
