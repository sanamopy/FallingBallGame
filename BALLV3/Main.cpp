#include <SDL.h>
#include <SDL_image.h>
#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <stdio.h>

#include "Player.h"
#include "Physics.h"
#include "Entities.h"
#include "RenderWindow.h"
int main(int argc, char* args[]) {
	std::cout << "Hello world" << std::endl;
	//If shit explodes, show error message
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
	{
		std::cout << "SDL EXPLODE MERDE. SDL_ERROR : " << SDL_GetError() << std::endl;
	}
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) //if diff image file, change _PNG
	{
		std::cout << "IMAGE EXPLODE MERDE. IMG ERROR: " << SDL_GetError() << std::endl;
	}

	const int maxFPS = 32;
	const int frame_time = 1000 / maxFPS;
	Uint32 framestart;
	int frame;

	srand(static_cast<unsigned int>(time(0)));
	int windowHeight = 640, windowWidth = 420;
	RenderWindow window("window", windowWidth, windowHeight);

	SDL_Texture* blueTexture = window.loadTexture("PNG1-BLUE.png");
	SDL_Texture* redTexture = window.loadTexture("PNG1-RED.png");
	SDL_Texture* projectileTexture = window.loadTexture("PNG1-GREEN.png");

	SDL_Surface* surface = IMG_Load("PNG1-PINK.png");
	std::vector<Entity> entities;
	std::vector<Entity> projectile;


	SDL_Cursor* cursor = SDL_CreateColorCursor(surface, 0, 0);


	Player player(300, 300, blueTexture, windowWidth, windowHeight);
	//player.Mouse(16, 16, mouseTexture);

	bool gameRunning = true;
	SDL_Event event;

	while (gameRunning)
	{
		framestart = SDL_GetTicks();
		SDL_SetCursor(cursor);

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT) {
				gameRunning = false;
			}

			//player.updatePosition();
			Entity::Spawn(event, entities, redTexture, windowWidth, windowHeight);//crash 
			player.shoot(event, projectile, projectileTexture, 16);
		}
		frame = SDL_GetTicks() - framestart;

		if (frame < frame_time) {
			SDL_Delay(frame_time - frame);
		}


		Physics::checkCollisions(entities, projectile);


		for (auto& proj : projectile) {
			proj.updatePosition();
		}
		//just keep for later
		/*for (auto& entity : entities) {
			entity.updatePosition();
		}*/
		
		window.clear();
		for (auto& proj : projectile) {
			window.render(proj);
		}

		for (auto& entity : entities)
		{
			window.render(entity);
		}

		player.render(window.getRenderer());
		window.display();

	}



	window.cleanUp();
	SDL_Quit();
	return 0;

}


