#pragma once
#include <SFML/Graphics.hpp>
#include <chrono>
#include <vector>
#include <list>
#include "Projectile.h"
#include "Character.h"
#include "Zombie.h"
#include "Cursor.h"
#include "Background.h"
#include "Obstacle.h"
#include "BaseScreen.h"
#include "Cursor.h"
#include <iostream>

class GameScreen
	: public BaseScreen
{
public:
	GameScreen()
		: BaseScreen("Game Screen")
	{
		m_Font.loadFromFile("OpenSans-Regular.ttf");
	}
	ScreenType run(sf::RenderWindow &window) {
		//TODO: move these into private variables probs
		Cursor newCursor(window);
		Character player({ 100.0f, 100.0f });

		std::list<Projectile> projectiles;
		std::list<Zombie> zombies;

		for (int i = 0; i < 25; ++i) {
			zombies.push_front(Zombie());
		}

		
		Background *testBackground = new Background(0, 0, 800, 600, "overcast.jpg");
		Obstacle *testObstacle = new Obstacle(50, 250, 140, 100, "barricade1.png",100);
		int boundscount = 0;

		//Timepoint for delta time measurement
		auto timePoint = std::chrono::steady_clock::now();
		
		while (window.isOpen()) {
			// Process events
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::MouseButtonPressed) {
					sf::Vector2i target = { event.mouseButton.x, event.mouseButton.y };
					sf::Vector2f source = player.getPosition();
					source.x += 10;
					source.y += 10;
					projectiles.push_front(Projectile(source, target));
				}
				// Close window: exit
				if (event.type == sf::Event::Closed)
					window.close();
			}

			//Get delta time
			float dt;
			{
				const auto newTimePoint = std::chrono::steady_clock::now();
				dt = std::chrono::duration<float>(newTimePoint - timePoint).count();
				timePoint = newTimePoint;
			}

			//Handle Input
			sf::Vector2f dir = { 0.0f, 0.0f };
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				if(!testObstacle->playerOnBottomBound(player)){
					dir.y -= 1.0f;
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				if (!testObstacle->playerOnTopBound(player)) {
					dir.y += 1.0f;
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				if (!testObstacle->playerOnRightBound(player)) {
					dir.x -= 1.0f;
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				if (!testObstacle->playerOnLeftBound(player)) {
					dir.x += 1.0f;
				}
			}

			player.setDirection(dir);
			player.update(dt);

			for (auto it = projectiles.begin(); it != projectiles.end();) {
				auto & projectile = *it;
				projectile.update();

				if (projectile.shouldBeDeleted(window)) {
					it = projectiles.erase(it);
				}
				else
					it++;
			}


			sf::Vector2f direction = { 0.0f, 0.0f };
			//direction = (player.getPosition() - enemy->getPosition());


			//enemy->setDirection(direction); //need different way to move towards character - position vector - get x,y?
			//enemy->update(dt);

			/*if (testObstacle->playerWithinBounds(player)) {
				std::cout << "player within barrier" <<boundscount<< std::endl;
				boundscount++;
				std::cout << "O:" << testObstacle->getBounds().getPosition().x << "," << testObstacle->getBounds().getPosition().y << std::endl
					<< "P:" << player.getPosition().x << "," << player.getPosition().y << std::endl;
			}*/
			for (Zombie &zombie : zombies)
			{
				direction = (player.getPosition() - zombie.getPosition());

				zombie.setDirection(direction);

				if (testObstacle->playerOnTopBound(zombie) && direction.y > 0) {
					zombie.update(0);
				}
				else if (testObstacle->playerOnLeftBound(zombie) && direction.x > 0) {
					zombie.update(0);
				}
				else if (testObstacle->playerOnBottomBound(zombie) && direction.y < 0) {
					zombie.update(0);
				}
				else if (testObstacle->playerOnRightBound(zombie) && direction.x < 0) {
					zombie.update(0);
				}
				else {
					zombie.update(dt);
				}

			}

			// Clear screen
			window.clear();
			//Scenery - always draw before characters
			testBackground->draw(window);
			testObstacle->draw(window);
			// Draw the sprite
			for (Zombie &zombie : zombies) {
				zombie.draw(window);
			}
			player.draw(window);
			//enemy->draw(window);
			// Update the window
			newCursor.setPosition(window);


			for (Projectile &p : projectiles) {
				window.draw(p);
			}
			window.display();
		}

		return Title;
	}

private:
	sf::Font m_Font;

};