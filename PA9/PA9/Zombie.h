#pragma once

#include <SFML/Graphics.hpp>
#include "Character.h"

class Zombie : public Character
{

enum class AnimationIndex
{
	WalkingUp,
	WalkingDown,
	WalkingLeft,
	WalkingRight,
	Count
};

public:
	Zombie() : Character(this->position)
	{
		this->zombieTexture.loadFromFile("zombiespritesheet.jpg");	
		this->position = { 200.0f, 200.0f };
		this->sprite.setScale(1,1);
		this->sprite.setTextureRect({ 0,0, 32, 32 });
		this->sprite.setTexture(zombieTexture);	
		this->animations[0].setAnimationFrames(1);

		animations[int(AnimationIndex::WalkingUp)] = Animation(32, 96, 32, 32, "zombiespritesheet.jpg", 1);
		animations[int(AnimationIndex::WalkingDown)] = Animation(32, 0, 32, 32, "zombiespritesheet.jpg", 1);
		animations[int(AnimationIndex::WalkingLeft)] = Animation(32, 32, 32, 32, "zombiespritesheet.jpg", 1);
		animations[int(AnimationIndex::WalkingRight)] = Animation(32, 64, 32, 32, "zombiespritesheet.jpg", 1);

	}
	
	//void draw();
	void setDirection(const sf::Vector2f &dir)
	{
		
		if (dir.x == 0 || dir.y == 0) //prevent crash of zombie object if on the same position - might need some tweaking
		{
			curAnimation = AnimationIndex::WalkingDown;
			return;
		}

		float temp = (float)sqrt(dir.x * dir.x + dir.y * dir.y);
		sf::Vector2f normalized = { dir.x, dir.y };
		normalized = normalized / temp;
		

		velocity =  normalized * speed * 50.0f / 100.0f;

		if (dir.x > 0.0f && abs(dir.x) > abs(dir.y)) //if x is positive and the x component is > y component - face right
		{
			curAnimation = AnimationIndex::WalkingRight;
		}
		else if (dir.x < 0.0f && abs(dir.x) > abs(dir.y)) //if x is negative and x > y face left
		{
			curAnimation = AnimationIndex::WalkingLeft;
		}
		else if (dir.y < 0.0f && abs(dir.y) > abs(dir.x)) //if y is negative and y > x face up
		{
			curAnimation = AnimationIndex::WalkingUp;
		}
		else if (dir.y > 0.0f && abs(dir.y) > abs(dir.x)) //if y is positive and y > x face down
		{
			curAnimation = AnimationIndex::WalkingDown;
		}
	}

	void update(float dt)
	{
		position += velocity * dt;
		animations[int(curAnimation)].update(dt, 1);
		animations[int(curAnimation)].applyToSprite(sprite);
		sprite.setPosition(position);
	}

	
	
private:


private:
	//static constexpr float speed = 100.0f;
	//sf::Vector2f position;
	//sf::Vector2f velocity = { 0.0f, 0.0f };
	//sf::Sprite sprite;
	Animation animations[int(AnimationIndex::Count)];
	AnimationIndex curAnimation = AnimationIndex::WalkingDown;
	sf::Texture zombieTexture;

	
};