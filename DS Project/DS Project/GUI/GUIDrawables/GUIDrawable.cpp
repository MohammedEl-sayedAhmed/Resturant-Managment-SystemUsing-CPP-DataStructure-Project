#include "GUIDrawable.h"

GUIDrawable::GUIDrawable(int id, GUI_REGION currentRegion) {
	this->ID = id;
	this->currentRegion = currentRegion;
}

int GUIDrawable::getID() {
	return ID;
}

GUI_REGION GUIDrawable::getCurrentRegion() {
	return currentRegion;
}

int GUIDrawable::getTextSize() {
	return textSize;
}
