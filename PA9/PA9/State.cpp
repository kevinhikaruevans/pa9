#include "State.h"

GameState::GameState()
{
	this->m_CurrentScreen = nullptr;
	this->m_DefaultFont.loadFromFile("OpenSans-Regular.ttf");
}

GameState::~GameState() {
	if (this->m_CurrentScreen) {
		delete this->m_CurrentScreen;
	}
}
void GameState::setCurrentScreen(BaseScreen * nextScreen)
{
	BaseScreen *oldScreen = this->m_CurrentScreen;
	this->m_CurrentScreen = nextScreen;

	if (oldScreen != nullptr) {
		delete oldScreen;
	}
}

BaseScreen * GameState::getCurrentScreen()
{
	return m_CurrentScreen;
}

sf::Font GameState::getDefaultFont()
{
	return m_DefaultFont;
}
