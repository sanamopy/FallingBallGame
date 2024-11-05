#pragma once
#ifndef Player_h
#define Player_h
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <iostream>
#include "Entities.h"
#include "Physics.h"
class Player
{
public:
	Player(int width, int height, SDL_Texture* texture, int& windowWidth, int& windowHeight);

	void aiming() const;
	void render(SDL_Renderer* renderer);

	void shoot(SDL_Event& event, std::vector<Entity>& projectile, SDL_Texture* projectileTexture, int velocity);
	SDL_Rect getRect() const;

private:
	SDL_Rect rect;
	SDL_Texture* texture;
};

#endif // !Player_h
#pragma once
