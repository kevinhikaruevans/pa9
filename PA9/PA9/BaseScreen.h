#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"

class GameState;

class BaseScreen {
public:
	BaseScreen(std::string title) {
		this->m_Title = title;
	}
	~BaseScreen() { }

	virtual void handleEvents(sf::Event e, sf::RenderWindow &window, GameState &state) = 0;
	virtual void draw(sf::RenderWindow &window, GameState &state) = 0;

private:
	std::string m_Title;
};