#pragma once

#include <SFML/Graphics.hpp>

class Animation
{
public:
	Animation() = default;
	Animation(int x, int y, int width, int height, std::string fileName, int frameAdjust)
	{
		texture.loadFromFile(fileName); //maybe throw exception/error checking
		
		for (int i = 0; i < nFrames - frameAdjust; i++)
		{
			frames[i] = { x + i * width, y, width, height };
		}
	}
	void applyToSprite(sf::Sprite &spr) const
	{
		spr.setTexture(texture);
		spr.setTextureRect(frames[iFrame]);
	}
	void update(float dt, int frameAdjust)
	{
		time += dt;
		while (time >= holdTime)
		{
			time -= holdTime;
			advance(frameAdjust);
		}
	}

	
	void setAnimationFrames(int frameAdjust)
	{
		frames[nFrames - frameAdjust];
	}

private:
	void advance(int frameAdjust)
	{
		if (++iFrame >= nFrames - frameAdjust)
		{
			iFrame = 0;
		}
	}
	
private:
	static constexpr int nFrames = 3;
	static constexpr float holdTime = 0.1f;
	sf::Texture texture;
	sf::IntRect frames[nFrames];
	int iFrame = 0;
	float time = 0.0f;
};
