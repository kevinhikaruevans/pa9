#pragma once

#include <SFML/Graphics.hpp>

class Cursor
{
public:
	Cursor(sf::RenderWindow &window)
	{
		texture.loadFromFile("6crosshair.png");
		sprite.setTexture(texture);
		window.setMouseCursorVisible(false);		
	}

	void setPosition(sf::RenderWindow &window)
	{
		sprite.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)) + window.getView().getCenter() - sf::Vector2f(400,300));
		window.draw(sprite);
	}

private:
	sf::Texture texture;
	sf::Sprite sprite;
};
