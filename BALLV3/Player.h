#pragma once
#ifndef Player_h
#define Player_h
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <iostream>
#include "Entities.h"
#include "Collisions.h"
class Entity;
class PowerUp;

class Player
{
public:
	Player(int width, int height, SDL_Texture* texture, int& windowWidth, int& windowHeight);

	void aiming() const;
	void render(SDL_Renderer* renderer);

	void shoot(SDL_Event& event, std::vector<Entity>& projectile, SDL_Texture* projectileTexture, int velocity);	
	static bool outOfBounds(std::vector<Entity>& projectile, int& windowWidth, int& windowHeight, bool* detectOutOfBounds);
	void setMaxProjectiles(int newMax);

	SDL_Rect getRect() const;


	bool getp_OutOfBounds() const;
	float getProjectileX() const;
	float getProjectileY() const;
	float getVelocityX() const;
	float getVelocityY() const;
	int getMaxProjectiles() const;

	void setX(int x);
	void setY(int y);

	void incrementScore();
	int getScore() const;


private:
	int score = 0;
	int maxProjectiles = 1;
	bool detectOutOfBounds = false;
	float projectileX;
	float projectileY;
	float velocityX;
	float velocityY;
	SDL_Rect rect;
	SDL_Texture* texture;
};

#endif // !Player_h
#pragma once
