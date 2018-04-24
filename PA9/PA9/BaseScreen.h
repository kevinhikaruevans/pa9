#pragma once

#include <SFML/Graphics.hpp>
#include "ScreenType.h"
#include <vector>

class BaseScreen {
public:
	BaseScreen(std::string title);
	~BaseScreen();

	virtual ScreenType run(sf::RenderWindow &window) = 0;

private:
	std::string m_Title;

protected:
	std::vector<sf::Drawable *> layer0;
	std::vector<sf::Drawable *> layer1;
};
