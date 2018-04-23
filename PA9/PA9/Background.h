#include "Scenery.h"

class Background : public Scenery {

public:

	Background(float xPos, float yPos, float xSize, float ySize, std::string fileName) : Scenery(xPos, yPos, xSize, ySize, fileName) {};
	~Background();

	void draw(sf::RenderWindow &window) {
		window.draw(getImage());
	}
};