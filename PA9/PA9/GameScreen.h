#pragma once

#include "BaseScreen.h"

class GameScreen
	: public BaseScreen
{
public:
	GameScreen()
		: BaseScreen("Game Screen")
	{

	}

	void handleEvents(sf::Event e, sf::RenderWindow &window, GameState &state) {

	}

	void draw(sf::RenderWindow &window, GameState &currentState) {
		window.draw(sf::Text("gameplay here", currentState.getDefaultFont(), 10));
	}


private:


};