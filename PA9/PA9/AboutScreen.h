#pragma once

#include "BaseScreen.h"

class AboutScreen
	: public BaseScreen
{
public:
	AboutScreen()
		: BaseScreen("About Screen")
	{

	}

	void handleEvents(sf::Event e, sf::RenderWindow &window, GameState &state) {

	}

	void draw(sf::RenderWindow &window, GameState &currentState) {
		window.draw(sf::Text("about stuff can go here", currentState.getDefaultFont(), 10));
	}

};