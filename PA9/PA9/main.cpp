#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(10);
	shape.setFillColor(sf::Color::Red);
	float i = 0;
	while (window.isOpen())
	{
		sf::Event event;
		sf::Color c(
			(int)(cos(i * 10) * 100 + 155),
			0,
			0
		);
		shape.setFillColor(c);
		shape.setPosition(
			cos(i) * 100 + 100,
			sin(i) * 100 + 100
		);
		i += 0.001;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::TextEntered) {
				std::cout << (char)event.text.unicode << std::endl;
			}
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}