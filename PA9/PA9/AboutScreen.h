#pragma once

#include "BaseScreen.h"
#include <vector>
#define NUM_ELEMENTS 2

using sf::Text;
using std::vector;
using sf::Drawable;

class AboutScreen
	: public BaseScreen
{
public:
	AboutScreen()
		: BaseScreen("About Screen")
	{
		m_Font.loadFromFile("OpenSans-Regular.ttf");
		Text *buffer;

		buffer = new sf::Text("How to play the game\nPress ENTER to return to the menu\n", this->m_Font, 24U);
		buffer->setPosition(10, 50);
		elements.push_back(buffer);
	}

	ScreenType run(sf::RenderWindow &window) {
		while (window.isOpen()) {
			sf::Event e;
			while (window.pollEvent(e)) {
				if (e.type == sf::Event::KeyPressed) {
					if (e.key.code == sf::Keyboard::Return) {
						return Title;
					}
				}
			}
			window.clear();
			for (vector<Drawable *>::iterator i = elements.begin(); i != elements.end(); ++i) {
				window.draw(**i);
			}
			window.display();
		}
	}
private:
	sf::Font m_Font;
	Text m_Title;
	Text m_Description;
	vector<Drawable *> elements;	
	int numElements = 0;
};