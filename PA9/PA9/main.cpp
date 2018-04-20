#include <SFML/Graphics.hpp>
#include "State.h"
#include "BaseScreen.h"

#include "TitleScreen.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "PA9");
	GameState state;

	window.setFramerateLimit(60);
	state.setCurrentScreen(new TitleScreen());

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			state.getCurrentScreen()->handleEvents(event, window, state);
		}

		window.clear();

		state.getCurrentScreen()->draw(window, state);

		window.display();
	}

	return 0;
}