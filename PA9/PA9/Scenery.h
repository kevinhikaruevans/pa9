#pragma once

#include <SFML/Graphics.hpp>


class Scenery{

public:
	Scenery(float xPos, float yPos, float xSize, float ySize, std::string fileName){

		texture.loadFromFile(fileName);
		image.setTexture(texture);
		image.setPosition(xPos, yPos);

		bounds.setPosition(xPos, yPos);
		bounds.setSize(* new sf::Vector2f(xSize,ySize));

	};

	virtual void draw(sf::RenderWindow &window) = 0;

	sf::RectangleShape getBounds() {
		return bounds;
	};

	sf::Sprite getImage() {
		return image;
	}

private:

	sf::Texture texture;
	sf::Sprite image;
	sf::RectangleShape bounds;

};