#pragma once
#include "SFML\Graphics.hpp"
#include "Quad.h"
#include <iostream>

#define DUR 800

class Button : public sf::Drawable {
public:
	Button(std::string text, sf::Font &font) : text(text, font) {
		setSize(sf::Vector2f(50, 100));
	}
	void setPosition(float x, float y) {
		setPosition(sf::Vector2f(x, y));
	}
	void setPosition(sf::Vector2f pos) {
		this->frame.setPosition(pos);
		this->text.setPosition(pos.x * 1.1, pos.y * 1.01);
	}
	void setSize(float x, float y) {
		setSize(sf::Vector2f(x, y));
	}
	void setSize(sf::Vector2f size) {
		this->size = size;
		this->frame.setSize(size);
		this->text.setCharacterSize(size.y * .7);
		setPosition(frame.getPosition());
	}
	void setBackgroundColor(sf::Color color) {
		frame.setFillColor(color);
	}
	void select() {
		if (!tweening) {
			clock.restart();
			tweening = true;
		}
	}
	void deselect() {
		if (tweening) {
			tweening = false;
			frame.setSize(sf::Vector2f(0, 0));
		}
	}
	void update() {
		if (tweening) {
			std::cout << "Tweening! " << size.x << "\n";
			int ms = clock.getElapsedTime().asMilliseconds();
			if (ms >= DUR) {
				ms = DUR;
			}
			float newX = _PENNER_QUAD::Quad::easeOut(ms, 0, size.x, DUR);
			frame.setSize(sf::Vector2f(newX,size.y));
		}
		else {
			tweening = false;
		}
	}
	void draw(sf::RenderTarget &target, sf::RenderStates states) const {
		target.draw(frame);
		target.draw(text);
	}
private:
	bool tweening;
	sf::Clock clock;
	sf::Vector2f size;
	sf::RectangleShape frame;
	sf::Text text;
};