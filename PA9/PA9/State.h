#pragma once

#include "BaseScreen.h"
#include <vector>

class GameState {
public:
	GameState();
	~GameState();


	void setCurrentScreen(BaseScreen *nextScreen);
	BaseScreen *getCurrentScreen();

	sf::Font getDefaultFont();
private:
	BaseScreen *m_CurrentScreen;
	sf::Font m_DefaultFont;
	
};