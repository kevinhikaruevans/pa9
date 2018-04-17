#pragma once
#include "AboutScreen.h"
#include "BaseScreen.h"
#include "State.h"

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

		m_TitleText = sf::Text("PA9", this->m_Font, 40U);

		m_MenuOptions[0] = sf::Text("Play", this->m_Font, 30U);
		m_MenuOptions[1] = sf::Text("About", this->m_Font, 30U);
		m_MenuOptions[2] = sf::Text("Exit", this->m_Font, 30U);

		m_MenuOptions[0].setPosition(10, 40);
		m_MenuOptions[1].setPosition(10, 70);
		m_MenuOptions[2].setPosition(10, 100);
	}

	void handleEvents(sf::Event e, sf::RenderWindow &window, GameState &state) {
		if (e.type == sf::Event::KeyReleased) {
			switch (e.key.code) {
				case sf::Keyboard::Up: {
					if (m_SelectedMenuOption > 0) {
						m_SelectedMenuOption--;
					}
					else {
						m_SelectedMenuOption = MENU_SIZE - 1;
					}

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
							// TODO
							break;
						case MENU_OPTION_ABOUT:
							state.setCurrentScreen(new AboutScreen());
							break;
						case MENU_OPTION_EXIT:
							window.close();
							break;
					}
					break;
				}
			}
		}
	}


	void draw(sf::RenderWindow &window, GameState &currentState) {
		window.draw(this->m_TitleText);

		for (int i = 0; i < MENU_SIZE; i++) {
			sf::Text &menuOption = this->m_MenuOptions[i];
			if (i == this->m_SelectedMenuOption) {
				menuOption.setColor(sf::Color::Red);
			}
			else {
				menuOption.setColor(sf::Color::White);
			}
			window.draw(this->m_MenuOptions[i]);
		}
	}

private:
	sf::Font m_Font;

	sf::Text m_TitleText;

	sf::Text m_MenuOptions[MENU_SIZE];

	int m_SelectedMenuOption;
};