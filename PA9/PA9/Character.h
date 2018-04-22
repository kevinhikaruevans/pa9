#pragma once

#include <SFML/Graphics.hpp>
#include "Animation.h"

#define MAX_HEALTH 100


class Character
{
private:
	enum class AnimationIndex
	{
		WalkingUp,
		WalkingDown,
		WalkingLeft,
		WalkingRight,
		Count
	};

public:
	Character() = default;
	Character(const sf::Vector2f &pos)
		:
		position(pos)		
	{		
		sprite.setTextureRect({ 0, 0, 20, 24 });
		sprite.setScale(2, 2);
		mHealth = MAX_HEALTH;
		animations[int(AnimationIndex::WalkingUp)] = Animation(20, 0, 20, 24, "spritesheet.png", 0);
		animations[int(AnimationIndex::WalkingDown)] = Animation(20, 48, 20, 24, "spritesheet.png", 0);
		animations[int(AnimationIndex::WalkingLeft)] = Animation(20, 24, 20, 24, "spritesheet.png", 0);
		animations[int(AnimationIndex::WalkingRight)] = Animation(20, 72, 20, 24, "spritesheet.png", 0);
	}
	void draw(sf::RenderTarget & rt) const
	{
		rt.draw(sprite);
	}
	virtual void setDirection(const sf::Vector2f & dir)
	{
		velocity = dir * speed;

		if (dir.x > 0.0f)
		{
			curAnimation = AnimationIndex::WalkingRight;
		}
		else if (dir.x < 0.0f)
		{
			curAnimation = AnimationIndex::WalkingLeft;
		}
		else if (dir.y < 0.0f)
		{
			curAnimation = AnimationIndex::WalkingUp;
		}
		else if (dir.y > 0.0f)
		{
			curAnimation = AnimationIndex::WalkingDown;
		}
	}
	virtual void update(float dt)
	{
		position += velocity * dt;
		animations[int(curAnimation)].update(dt, 0);
		animations[int(curAnimation)].applyToSprite(sprite);
		sprite.setPosition(position);
	}

	virtual void takeDamage()
	{

	}

	sf::Vector2f getPosition()
	{
		return this->position;
	}

	int getHealth()
	{
		return this->mHealth;
	}

	void setHealth(int newHealth)
	{
		this->mHealth += newHealth;
		if (this->mHealth > MAX_HEALTH)
		{
			mHealth = MAX_HEALTH;
		}
	}
		
protected:
	static constexpr float speed = 100.0f;
	sf::Vector2f position;
	sf::Vector2f velocity = { 0.0f, 0.0f };	
	sf::Sprite sprite;
	Animation animations[int(AnimationIndex::Count)];
	AnimationIndex curAnimation = AnimationIndex::WalkingDown;

private:
	int mHealth;
};
