#pragma once

#include <SFML/Graphics.hpp>


class Scenery{

public:
	Scenery(float xPos, float yPos, float xSize, float ySize, std::string fileName){

		texture.loadFromFile(fileName);
		image.setTexture(texture);
		image.setPosition(xPos, yPos);

		bounds.setPosition(xPos, yPos);
		bounds.setSize(*new sf::Vector2f(xSize, ySize));		

	};

	virtual void draw(sf::RenderWindow &window) = 0;

	sf::RectangleShape getBounds() {
		return bounds;
	};

	sf::Sprite & getImage() {
		return image;
	}

	bool playerWithinBounds(Character & p) {
		if (p.getPosition().y >= bounds.getPosition().y -24 && p.getPosition().y <= bounds.getPosition().y + bounds.getSize().y -24) {
			if (p.getPosition().x >= bounds.getPosition().x - 20 && p.getPosition().x <= bounds.getPosition().x + bounds.getSize().x -20) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}

	bool playerOnTopBound(Character & p){
		if (this->playerWithinBounds(p)) {
			if (p.getPosition().y < this->getBounds().getPosition().y) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	bool playerOnLeftBound(Character & p) {
		if (this->playerWithinBounds(p)) {
			if (p.getPosition().x < this->getBounds().getPosition().x) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	bool playerOnBottomBound(Character & p) {
		if (this->playerWithinBounds(p)) {
			if (p.getPosition().y > this->getBounds().getPosition().y + this->getBounds().getSize().y - 48) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	bool playerOnRightBound(Character & p) {
		if (this->playerWithinBounds(p)) {
			if (p.getPosition().x > this->getBounds().getPosition().x + this->getBounds().getSize().x - 40) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}

	

private:

	sf::Texture texture;
	sf::Sprite image;
	sf::RectangleShape bounds;

};