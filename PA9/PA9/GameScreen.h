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

#define WINDOW_SCALE 0.39f

class GameScreen
	: public BaseScreen
{
private:
	std::list<Character *> enemies;
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

		for (int i = 0; i < 25; ++i) {
			enemies.push_front(new Zombie());
		}


		//Background *testBackground = new Background(0, 0, 1920, 1080, "background.jpg");
		//testBackground->setScale(WINDOW_SCALE, WINDOW_SCALE, (*testBackground).getImage()); //resize background image - could pass in ref to window to scale dynamically
		Background *testBackgrounds[15];
		for (int i = 0; i < 15; i++) {
			if (i < 5) {
				testBackgrounds[i] = new Background(1920 * (float)i, 0, 1920, 1080, "background.jpg");
			}
			else if (i < 10) {
				testBackgrounds[i] = new Background(1920 * ((float)i-5), 1080, 1920, 1080, "background.jpg");
			}
			else {
				testBackgrounds[i] = new Background(1920 * ((float)i-10), 1080*2, 1920, 1080, "background.jpg");
			}
		}
		Obstacle *testObstacle = new Obstacle(50, 250, 140, 100, "barricade1.png", 100);		
		//int boundscount = 0;
		sf::Vector2f playerFollowVector = *new sf::Vector2f(400, 300);
		sf::View * followPlayerView = new sf::View(playerFollowVector,*new sf::Vector2f(800,600));

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
				if (!testObstacle->playerOnBottomBound(player)) {
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


			if (player.getPosition().x >= 400) {
				playerFollowVector.x = player.getPosition().x;
			}
			if (player.getPosition().y >= 300) {
				playerFollowVector.y = player.getPosition().y;
			}

			followPlayerView->setCenter(playerFollowVector);
			window.setView(*followPlayerView);

			/*std::cout << "P: " << player.getPosition().x << "," << player.getPosition().y << '\t' << "PFV: " 
				<< playerFollowVector.x << "," << playerFollowVector.y << std::endl;*/

			for (auto it = projectiles.begin(); it != projectiles.end();) {
				auto & projectile = *it;
				projectile.update();

				if (projectile.shouldBeDeleted(window)) {
					it = projectiles.erase(it);
				}
				else
					it++;
			}

			for (auto it = enemies.begin(); it != enemies.end();) {
				Character *c = *it;
				sf::Vector2f direction = (player.getPosition() - c->getPosition());

				if (c->isTouchingCharacter(player)) {
					// zombie attacked the player...
					// player should probably take damage or something here.
					delete c;
					it = enemies.erase(it);
				}
				else if (c->getHealth() <= 0) {
					delete c;
					it = enemies.erase(it);
				}
				else {
					c->handleProjectiles(projectiles);
					c->setDirection(direction);

					if (testObstacle->playerOnTopBound(*c) && direction.y > 0) {
						c->update(0);
					}
					else if (testObstacle->playerOnLeftBound(*c) && direction.x > 0) {
						c->update(0);
					}
					else if (testObstacle->playerOnBottomBound(*c) && direction.y < 0) {
						c->update(0);
					}
					else if (testObstacle->playerOnRightBound(*c) && direction.x < 0) {
						c->update(0);
					}
					else {
						c->update(dt);
					}

					it++;
				}

			}

			
			//direction = (player.getPosition() - enemy->getPosition());


			//enemy->setDirection(direction); //need different way to move towards character - position vector - get x,y?
			//enemy->update(dt);

			/*if (testObstacle->playerWithinBounds(player)) {
			std::cout << "player within barrier" <<boundscount<< std::endl;
			boundscount++;
			std::cout << "O:" << testObstacle->getBounds().getPosition().x << "," << testObstacle->getBounds().getPosition().y << std::endl
			<< "P:" << player.getPosition().x << "," << player.getPosition().y << std::endl;
			}*/


			// Clear screen
			window.clear();
			for (int i = 0; i < 15; i++) {
				testBackgrounds[i]->draw(window);
			}
			//Scenery - always draw before characters
			//testBackground->draw(window);
			testObstacle->draw(window);
			// Draw the sprite
			for (Character *c : enemies) {
				c->draw(window);
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