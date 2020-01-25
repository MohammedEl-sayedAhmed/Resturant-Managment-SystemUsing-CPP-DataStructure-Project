#include "GUI.h"

GUI::GUI() {
	for (int i = 0; i < MAX_DRAWABLES_COUNT; i++){
		drawablesList[i] = NULL;
	}

	calibre = new sf::Font;
	if (!calibre->loadFromFile(FONT_FILE_PATH)) {
		std::cerr << "The font wasn't loaded\n";
		exit(1);
	}
}

GUI::~GUI() {
	delete calibre;
	delete simWindow;
	delete drawingScreen;
	delete statusBar;
}

PROG_MODE GUI::getProgramMode() {

	sf::RenderWindow window(sf::VideoMode((int)STARTING_WINDOW_SIZE_X, (int)STARTING_WINDOW_SIZE_Y), "Resturant, Starting Window");
	StartingScreen screen(STARTING_WINDOW_SIZE_X, STARTING_WINDOW_SIZE_Y, LOGO_FILE_PATH, calibre);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			std::string userInput = "";

			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				break;
			case sf::Event::TextEntered:
				if (event.text.unicode < 128) {
					userInput += static_cast<char>(event.text.unicode);
					if (userInput[0] == '\r') {
						PROG_MODE mode = screen.getMode();
						if (mode != PROG_MODE::MODE_CNT) {
							window.close();
							return mode;
						}
					} else {
						screen.showModeChoice(userInput);
					}
				}
				break;
			default:
				break;
			}
		}

		window.clear(sf::Color::Yellow);
		window.draw(screen);
		window.display();
	}
	// If something went wrong
	exit(1);
}

void GUI::initSimMode(){
	simWindow = new sf::RenderWindow(sf::VideoMode((int)DRAWING_WINDOW_SIZE_X, (int) (DRAWING_WINDOW_SIZE_Y + STATUS_BAR_SIZE_Y)), "Resturant, Simulation Window");
	
	drawingScreen = new MainScreen(DRAWING_WINDOW_SIZE_X, DRAWING_WINDOW_SIZE_Y, calibre);
	statusBar = new TextArea(STATUS_BAR_SIZE_X, STATUS_BAR_SIZE_Y, calibre);
	statusBar->setPosition(0.0f, DRAWING_WINDOW_SIZE_Y);
}

void GUI::updateInterface(){
	drawingScreen->drawUserGUIElements(drawablesList, drawablesListSize);

	simWindow->clear(this->MAIN_WINDOW_BACKGROUND_COLOR);
	simWindow->draw(*drawingScreen);
	simWindow->draw(*statusBar);
	simWindow->display();

	drawingScreen->clearUserElements();

	// Cleaning up the current Drawables
	for (int i = 0; i < drawablesListSize; i++)	{
		delete drawablesList[i];
		drawablesList[i] = NULL;
	}
	drawablesListSize = 0;
}

void GUI::sleep(int milliseconds) {
	sf::sleep(sf::milliseconds(milliseconds));
}

void GUI::addGUIDrawable(GUIDrawable* drawable){
	if(drawablesListSize + 1 < MAX_DRAWABLES_COUNT) {
		drawablesList[drawablesListSize++] = drawable;
	} else {
		std::cerr << "Too Many drawables on the screen\n";
	}
}

void GUI::printStringInStatusBar(std::string text) {
	statusBar->printString(text);
}

void GUI::handleSimGUIEvents() {
	sf::Event event;
	while(simWindow->pollEvent(event)) {
		switch(event.type) {
		case sf::Event::Closed:
			simWindow->close();
			break;
		default:
			break;
		}
	}
}

void GUI::waitForClick() {
	sf::Event event;
	while(true) {
		while(simWindow->pollEvent(event)) {
			switch(event.type) {
			case sf::Event::Closed:
				simWindow->close();
				break;
			case sf::Event::MouseButtonPressed:
				if(event.mouseButton.button == sf::Mouse::Left) { 
					return;
				}
				break;
			default:
				break;
			}
		}
	}
}

