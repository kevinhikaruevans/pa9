#pragma once
#include "SFML\System.hpp"

class Bounds {
public:
	static bool isBetween(float x, float min, float max) {
		return x <= max && x >= min;
	}
	static bool isHit(sf::Vector2f attacker, float radius, sf::Vector2f self) {
		return isBetween(self.x, attacker.x - radius, attacker.x + radius)
			&& isBetween(self.y, attacker.y - radius, attacker.y + radius);

	}
};
