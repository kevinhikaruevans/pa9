#include <SFML/Graphics.hpp>

#include "BaseScreen.h"
#include "TitleScreen.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "PA9");
	window.setFramerateLimit(60);

	BaseScreen *curScreen = new TitleScreen();
	ScreenType switchScreenTo = Title;

	do {
		switchScreenTo = curScreen->run(window);
		BaseScreen *prevScreen = curScreen;

		switch (switchScreenTo) {
		case Title:
			curScreen = new TitleScreen();
			break;
		case About:
			curScreen = new AboutScreen();
			break;
		}
	} while (switchScreenTo != 0);

	return 0;
}