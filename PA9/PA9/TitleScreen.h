#pragma once
#include "AboutScreen.h"
#include "BaseScreen.h"
#include "GameScreen.h"
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
		m_SelectedMenuOption = 0;
		m_TitleText = sf::Text("PA9", this->m_Font, 40U);

		m_MenuOptions[0] = sf::Text("Play", this->m_Font, 30U);
		m_MenuOptions[1] = sf::Text("About", this->m_Font, 30U);
		m_MenuOptions[2] = sf::Text("Exit", this->m_Font, 30U);

		m_MenuOptions[0].setPosition(10, 40);
		m_MenuOptions[1].setPosition(10, 70);
		m_MenuOptions[2].setPosition(10, 100);
	}
	ScreenType run(sf::RenderWindow &window) {
		while (window.isOpen()) {
			sf::Event e;
			while (window.pollEvent(e)) {
				if (e.type == sf::Event::KeyReleased) {
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
			window.draw(this->m_TitleText);
			// iterate through the whole menu array
			for (int i = 0; i < MENU_SIZE; i++) {
				sf::Text &menuOption = this->m_MenuOptions[i];

				// highlight the selected option...
				if (i == this->m_SelectedMenuOption)
					menuOption.setFillColor(sf::Color::Red);
				else
					menuOption.setFillColor(sf::Color::White);

				window.draw(this->m_MenuOptions[i]);
			}

			window.display();
		}
	}
	/*
	void handleEvents(sf::Event e, sf::RenderWindow &window) {
		if (e.type == sf::Event::KeyReleased) {
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
							// TODO
							state.setCurrentScreen(new GameScreen());
							break;
						case MENU_OPTION_ABOUT:
							// update the screen to be a new instance of the AboutScreen
							return;
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

	/*
	Draws the text onto the window
	void draw(sf::RenderWindow &window) {
		window.draw(this->m_TitleText);

		// iterate through the whole menu array
		for (int i = 0; i < MENU_SIZE; i++) {
			sf::Text &menuOption = this->m_MenuOptions[i];

			// highlight the selected option...
			if (i == this->m_SelectedMenuOption)
				menuOption.setFillColor(sf::Color::Red);
			else
				menuOption.setFillColor(sf::Color::White);

			window.draw(this->m_MenuOptions[i]);
		}
	}
	*/
private:
	sf::Font m_Font;

	sf::Text m_TitleText;

	sf::Text m_MenuOptions[MENU_SIZE];

	int m_SelectedMenuOption;
};