/*
WSU | CPT_S 122 | Spring 2018
PA 9 - A Graphical Game or Application
Due: April 25, 2018
Group Names:
	David
	Jonathan
	Kevin
	Riley Chase
*/

#include "BaseScreen.h"
#include "TitleScreen.h"
#include "GameScreen.h"


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
		case Game:
			curScreen = new GameScreen();
			break;
		}
	} while (switchScreenTo != 0);

	return EXIT_SUCCESS;
}