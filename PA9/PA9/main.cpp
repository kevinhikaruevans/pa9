#include "BaseScreen.h"
#include "TitleScreen.h"
#include "GameScreen.h"
#include "DeathScreen.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "PA9");
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

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
		case Death:
			curScreen = new DeathScreen();
			break;
		}
	} while (switchScreenTo != 0);

	return EXIT_SUCCESS;
}