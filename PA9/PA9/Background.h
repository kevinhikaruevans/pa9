#include "Scenery.h"

class Background : public Scenery {

public:

	Background(float xPos, float yPos, float xSize, float ySize, std::string fileName) : Scenery(xPos, yPos, xSize, ySize, fileName) {};
	~Background();

	void draw(sf::RenderWindow &window) {
		window.draw(getImage());		
	}

	void setScale(float xScale, float yScale, sf::Sprite &spr)
	{
		spr.setScale({ xScale, yScale });
	}
};