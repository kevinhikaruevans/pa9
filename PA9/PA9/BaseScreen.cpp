#include "BaseScreen.h"

BaseScreen::BaseScreen(std::string title) {
	this->m_Title = title;
}

BaseScreen::~BaseScreen() {
	for (std::vector<sf::Drawable *>::iterator i = layer0.begin(); i != layer0.end(); ++i) {
		delete *i;
	}
	for (std::vector<sf::Drawable *>::iterator i = layer1.begin(); i != layer1.end(); ++i) {
		delete *i;
	}
}