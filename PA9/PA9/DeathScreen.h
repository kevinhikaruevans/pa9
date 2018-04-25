#pragma once

#include "BaseScreen.h"
#include <vector>
#define NUM_ELEMENTS 2

using sf::Text;
using std::vector;
using sf::Drawable;

class DeathScreen
	: public BaseScreen
{
public:
	DeathScreen()
		: BaseScreen("Death Screen")
	{
		m_Font.loadFromFile("OpenSans-Regular.ttf");
		Text *buffer;

		buffer = new sf::Text("You are dead! Press RETURN to continue.", this->m_Font, 24U);
		buffer->setPosition(10, 50);
		elements.push_back(buffer);
	}

	ScreenType run(sf::RenderWindow &window) {
		while (window.isOpen()) {
			sf::Event e;
			int ret = 0;
			while (window.pollEvent(e)) {
				if (e.type == sf::Event::KeyPressed) {
					if (e.key.code == sf::Keyboard::Return) {
						return Title;
					}
				}
			}
			window.setView(window.getDefaultView());
			window.clear();
			for (vector<Drawable *>::iterator i = elements.begin(); i != elements.end(); ++i) {
				window.draw(**i);
			}
			window.display();
		}
	}
private:
	sf::Font m_Font;
	vector<Drawable *> elements;
};