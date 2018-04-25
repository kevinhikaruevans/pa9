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
#define NUM_OBST 10

class GameScreen
	: public BaseScreen
{
	
public:
	GameScreen()
		: BaseScreen("Game Screen")
	{
		m_Font.loadFromFile("Creepster-Regular.ttf");
	}

	ScreenType run(sf::RenderWindow &window) {
		Cursor newCursor(window);
		Character player({ 100.0f, 100.0f });

		std::list<Projectile> projectiles;
		
		//Wave Count
		int curRound = 1;
		
		//List uses single Zombie object to spawn a new list of zombies
		heapZombies = spawnZombie.spawnWave(25); //int represents # of zombies - can tie into set 2D array of rounds/count
		

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
		//Obstacle *testObstacle = new Obstacle(50, 250, 140, 100, "barricade1.png", 100);
		Obstacle *testObstacles[NUM_OBST];
		for (int i = 0; i < NUM_OBST; i++) {
			i % 2 == 0 ?
				testObstacles[i] = new Obstacle(100 + 200 * (float)i, 150 + 10 * (float)i, 140, 100, "barricade1.png", 100)
				:
				testObstacles[i] = new Obstacle(50 + 20 * (float)i, 150 + 300 * (float)i, 140, 100, "barricade1.png", 100);
		}
		int activeObstacles = NUM_OBST;
		bool playerOnBoundry = false, zombieOnBoundry = false, projOnBoundry = false;
		//int boundscount = 0;
		sf::Vector2f playerFollowVector = *new sf::Vector2f(400, 300);
		sf::View * followPlayerView = new sf::View(playerFollowVector,*new sf::Vector2f(800,600));
		sf::Text levelText (sf::String("Level: " + std::to_string(curRound)), m_Font, 24);
		levelText.setOutlineColor(sf::Color::Red);
		levelText.setOutlineThickness(1.1);
		levelText.setFillColor(sf::Color::Black);
		levelText.setPosition({500, 500});

		sf::RectangleShape healthbg = *new sf::RectangleShape(*new sf::Vector2f(200, 25));
		healthbg.setPosition(*new sf::Vector2f(500, 500));
		healthbg.setFillColor(sf::Color::Black);
		sf::RectangleShape healthBar = *new sf::RectangleShape(healthbg);
		healthBar.setFillColor(sf::Color::Red);

		//Timepoint for delta time measurement
		auto timePoint = std::chrono::steady_clock::now();

		while (window.isOpen()) {

			// Process events
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::MouseButtonPressed) {
					sf::Vector2i target = { event.mouseButton.x + (int)window.getView().getCenter().x - 400, event.mouseButton.y + (int)window.getView().getCenter().y - 300 };
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

			playerOnBoundry = false;
			//Handle Input
			sf::Vector2f dir = { 0.0f, 0.0f };
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				for (int i = 0; i < activeObstacles; i++) {
					if (testObstacles[i]->playerOnBottomBound(player)) {
						playerOnBoundry = true;
					}
				}

				playerOnBoundry ? dir.y = 0.0f : dir.y -= 1.0f;

				if (player.getPosition().y <= 0) {
					dir.y = 0.0f;
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				for (int i = 0; i < activeObstacles; i++) {
					if (testObstacles[i]->playerOnTopBound(player)) {
						playerOnBoundry = true;
					}
				}
				playerOnBoundry ? dir.y = 0.0f : dir.y += 1.0f;

				if (player.getPosition().y >= 1080*3) {
					dir.y = 0.0f;
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				for (int i = 0; i < activeObstacles; i++) {
					if (testObstacles[i]->playerOnRightBound(player)) {
						playerOnBoundry = true;
					}
				}
				playerOnBoundry ? dir.x = 0.0f : dir.x -= 1.0f;
			
				if (player.getPosition().x <= 0) {
					dir.x = 0.0f;
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				for (int i = 0; i < activeObstacles; i++) {
					if (testObstacles[i]->playerOnLeftBound(player)) {
						playerOnBoundry = true;
					}
				}
				playerOnBoundry ? dir.x = 0.0f : dir.x += 1.0f;

				if (player.getPosition().x >= 1920*5) {
					dir.x = 0.0f;
				}
			}

			player.setDirection(dir);
			player.update(dt);


			if (player.getPosition().x >= 400 && player.getPosition().x <= 9200) {
				playerFollowVector.x = player.getPosition().x;
			}
			if (player.getPosition().y >= 300 && player.getPosition().y <= 2940) {
				playerFollowVector.y = player.getPosition().y;
			}

			followPlayerView->setCenter(playerFollowVector);
			window.setView(*followPlayerView);

			/*std::cout << "P: " << player.getPosition().x << "," << player.getPosition().y << '\t' << "PFV: " 
				<< playerFollowVector.x << "," << playerFollowVector.y << std::endl;*/

			for (auto it = projectiles.begin(); it != projectiles.end();) {
				auto & projectile = *it;
				projectile.update();
				projOnBoundry = false;

				for (int i = 0; i < activeObstacles; i++) {
					if (it->getPosition().x >= testObstacles[i]->getBounds().getPosition().x
						&& it->getPosition().x <= testObstacles[i]->getBounds().getPosition().x + testObstacles[i]->getBounds().getSize().x
						&& it->getPosition().y >= testObstacles[i]->getBounds().getPosition().y
						&& it->getPosition().y <= testObstacles[i]->getBounds().getPosition().y + testObstacles[i]->getBounds().getSize().y) {
						testObstacles[i]->changeHealth(-50);
						projOnBoundry = true;
						if (testObstacles[i]->getHealth() <= 0) {
							delete testObstacles[i];
							activeObstacles--;
							for (int j = i; j < activeObstacles; j++) {
								testObstacles[j] = testObstacles[j + 1];
							}
							testObstacles[activeObstacles] = nullptr;
						}
					}
				}

				if (projectile.shouldBeDeleted(window.getView()) || projOnBoundry) {
					it = projectiles.erase(it);
				}
				else
					it++;
			}

			for (auto it = heapZombies.begin(); it != heapZombies.end();) {
				Character *c = *it;
				sf::Vector2f direction = (player.getPosition() - c->getPosition());
				zombieOnBoundry = false;

				if (c->isTouchingCharacter(player)) {
					// zombie attacked the player...
					// player should probably take damage or something here.
					player.takeDamage((float)10);
					delete c;
					it = heapZombies.erase(it);
				}
				else if (c->getHealth() <= 0) {
					delete c;
					it = heapZombies.erase(it);
				}
				else {
					c->handleProjectiles(projectiles);
					c->setDirection(direction);

					for (int i = 0; i < activeObstacles; i++) {
						if (testObstacles[i]->playerOnTopBound(*c) && direction.y > 0) {
							zombieOnBoundry = true;
						}
						else if (testObstacles[i]->playerOnLeftBound(*c) && direction.x > 0) {
							zombieOnBoundry = true;
						}
						else if (testObstacles[i]->playerOnBottomBound(*c) && direction.y < 0) {
							zombieOnBoundry = true;
						}
						else if (testObstacles[i]->playerOnRightBound(*c) && direction.x < 0) {
							zombieOnBoundry = true;
						}
					}


					if(zombieOnBoundry){
						c->update(0);
					}
					else {
						c->update(dt);
					}
					it++;
				}

			}

			


			if (heapZombies.empty()) //if all zombies die
			{
				curRound++; //advance the round and spawn next wave
				levelText.setString(sf::String("Level: " + std::to_string(curRound)));
				heapZombies = spawnZombie.spawnWave(curRound * 20);
			}

			float xOffset = followPlayerView->getCenter().x - 400
				, yOffset = followPlayerView->getCenter().y - 300;
			levelText.setPosition(500 + xOffset, 540 + yOffset);
			healthbg.setPosition(500 + xOffset, 500 + yOffset);
			healthBar.setPosition(500 + xOffset, 500 + yOffset);
			healthBar.setSize(*new sf::Vector2f((float)200*player.getHealth()/MAX_HEALTH, 25));
			

			// Clear screen
			window.clear();
			for (int i = 0; i < 15; i++) {
				testBackgrounds[i]->draw(window);
			}
			//Scenery - always draw before characters
      
			//testBackground->draw(window);
			//testObstacle->draw(window);
			for (int i = 0; i < activeObstacles; i++) {
				testObstacles[i]->draw(window);
			}
			// Draw the sprite
			for (Character *c : heapZombies) {

				c->draw(window);
			}
			player.draw(window);
			window.draw(healthbg);
			window.draw(healthBar);
			window.draw(levelText);
			//enemy->draw(window);
			// Update the window
			newCursor.setPosition(window);

			for (Projectile &p : projectiles) {
				window.draw(p);
			}
			window.display();

			if (player.getHealth() <= 0) {
				return Death;
			}

		}

		return Title;
	}

private:
	sf::Font m_Font;
	std::list<Character*> heapZombies;
	Zombie spawnZombie;

};