#include "Scenery.h"

class Obstacle : public Scenery {

public:

	Obstacle(float xPos, float yPos, float xSize, float ySize, std::string fileName, float newHealth) : Scenery(xPos,yPos,xSize,ySize,fileName) {
		health = newHealth;
	};
	~Obstacle() {
	};

	void draw(sf::RenderWindow &window) {
		if (health <= 0) {
			this->~Obstacle();
			return;
		}
		else {
			window.draw(getImage());
		}
	};

	float getHealth() {
		return health;
	};

	void changeHealth(float changeBy) {
		this->health += changeBy;
	};

private:
	
	float health;

};
