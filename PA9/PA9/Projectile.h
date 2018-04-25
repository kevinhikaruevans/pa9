#pragma once
#include "SFML\System.hpp"
#include "SFML\Graphics.hpp"
#include <cmath>

class Projectile
	: public sf::CircleShape
{
public:
	Projectile(sf::Vector2f position, sf::Vector2i target)
		: CircleShape(5), m_Speed(5.0), m_Target(target)
	{
		float y = (float)m_Target.y - position.y;
		float x = (float)m_Target.x - position.x;

		m_Direction = atan2f(y, x);

		this->setPosition(position);
		this->setFillColor(sf::Color::Magenta);
	}


	void update() {
		sf::Vector2f position = this->getPosition();

		position.x += cos(m_Direction) * m_Speed;
		position.y += sin(m_Direction) * m_Speed;

		this->setPosition(position);
	}

	bool shouldBeDeleted(sf::View windowView) {
		sf::Vector2f position = this->getPosition();
		return (position.x < windowView.getCenter().x - windowView.getSize().x/2)
			|| (position.y < windowView.getCenter().y - windowView.getSize().y / 2)
			|| (position.x > windowView.getCenter().x + windowView.getSize().x / 2)
			|| (position.y > windowView.getCenter().y + windowView.getSize().y / 2);
	}
private:
	sf::Vector2i m_Target;
	float m_Speed;
	float m_Direction;
};