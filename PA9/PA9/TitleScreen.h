#pragma once
#include "AboutScreen.h"
#include "Button.h"
//#include "State.h"

#define MENU_SIZE 3

#define MENU_OPTION_PLAY  0
#define MENU_OPTION_ABOUT 1
#define MENU_OPTION_EXIT  2

class TitleScreen
	: public BaseScreen
{
public:
	TitleScreen()
		: BaseScreen("Title Screen")
	{
		m_Font.loadFromFile("OpenSans-Regular.ttf");
		m_TitleFont.loadFromFile("OpenSans-Bold.ttf");

		m_SelectedMenuOption = 0;
		Button *b1 = createButton("Play");
		Button *b2 = createButton("Instructions");
		Button *b3 = createButton("Exit");

		for (int i = 0; i < layer1.size(); i++) {
			Button * thing = (Button *) layer1[i];
			thing->setPosition(25, 200 + 75 * i);
			thing->setSize(300, 60);
		}

		Text *titleText = new sf::Text("INFECTION", this->m_TitleFont, 60U);
		titleText->setPosition(25,100);
		
		layer1.push_back(titleText);
	}

	Button * createButton(std::string text) {
		Button *b = new Button(text, this->m_Font);
		b->setSize(sf::Vector2f(240, 80));
		b->setPosition(sf::Vector2f(60, 60));
		b->setBackgroundColor(sf::Color(255, 40, 51));
		this->layer1.push_back(b);
		return b;
	}

	ScreenType run(sf::RenderWindow &window) {
		while (window.isOpen()) {
			sf::Event e;
			while (window.pollEvent(e)) {
				if (e.type == sf::Event::KeyPressed) {
					switch (e.key.code) {
					case sf::Keyboard::Up: {
						if (m_SelectedMenuOption > 0)
							m_SelectedMenuOption--;
						else
							m_SelectedMenuOption = MENU_SIZE - 1;
							break;
						}
					case sf::Keyboard::Down: {
						if (m_SelectedMenuOption < MENU_SIZE - 1)
							m_SelectedMenuOption++;
						else
							m_SelectedMenuOption = 0;
							break;
						}
					case sf::Keyboard::Return: {
						switch (m_SelectedMenuOption) {
						case MENU_OPTION_PLAY:
							return Game;
							break;
						case MENU_OPTION_ABOUT:
							// update the screen to be a new instance of the AboutScreen
							return About;
							break;
						case MENU_OPTION_EXIT:
							// just exit out for this option
							window.close();
							break;
						}
						break;
					}
					}
			}
			}

			window.clear();

			((Button *)layer1[m_SelectedMenuOption])->select();

			for (int i = 0; i < 3; i++) {
				if (i != m_SelectedMenuOption) {
					((Button *)layer1[i])->deselect();
				}
				((Button *)layer1[i])->update();
			}

			for (std::vector<sf::Drawable *>::iterator i = layer1.begin(); i != layer1.end(); ++i) {
				Drawable * thing = *i;
				window.draw(*thing);
			}
			window.display();
		}
	}
private:
	sf::Font m_Font;
	sf::Font m_TitleFont;

	sf::Text m_MenuOptions[MENU_SIZE];

	int m_SelectedMenuOption;
};