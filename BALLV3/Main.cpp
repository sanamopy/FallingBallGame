#include <SDL.h>
#include <SDL_image.h>
#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <stdio.h>

#include "Player.h"
#include "Collisions.h"
#include "Entities.h"
#include "RenderWindow.h"

int main(int argc, char* args[]) {
    std::cout << "Hello world" << std::endl;

    if (SDL_Init(SDL_INIT_VIDEO) > 0) {
        std::cout << "SDL EXPLODE MERDE. SDL_ERROR : " << SDL_GetError() << std::endl;
    }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cout << "IMAGE EXPLODE MERDE. IMG ERROR: " << SDL_GetError() << std::endl;
    }

    const int maxFPS = 32;
    const int frame_time = 1000 / maxFPS;
    Uint32 framestart;
    int frame;
    const float gravityStrength = 6.0f;

    srand(static_cast<unsigned int>(time(0)));
    int windowHeight = 840, windowWidth = 620;

    RenderWindow window("window", windowWidth, windowHeight);

    SDL_Texture* blueTexture = window.loadTexture("PNG1-BLUE.png");
    SDL_Texture* redTexture = window.loadTexture("PNG1-RED.png");
    SDL_Texture* projectileTexture = window.loadTexture("PNG1-GREEN.png");

    SDL_Surface* mouse = IMG_Load("PNG1-PINK.png");
    std::vector<Entity> entities;
    std::vector<Entity> projectile;

    SDL_Cursor* cursor = SDL_CreateColorCursor(mouse, 0, 0);

    Player player(300, 300, blueTexture, windowWidth, windowHeight);

    // Add walls to the entities vector
    window.addWalls(entities);

    bool gameRunning = true;
    SDL_Event event;

    while (gameRunning) {
        framestart = SDL_GetTicks();
        SDL_SetCursor(cursor);

        bool isOutOfBounds = false;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                gameRunning = false;
            }
            player.shoot(event, projectile, projectileTexture, 32);
        }
        frame = SDL_GetTicks() - framestart;

        if (frame < frame_time) {
            SDL_Delay(frame_time - frame);
        }

        Player::outOfBounds(projectile, windowWidth, windowHeight, &isOutOfBounds);

        Entity::Spawn(event, entities, redTexture, windowWidth, windowHeight, &isOutOfBounds);

        Collisions::checkCollisions(entities, projectile, player);
        Collisions::applyGravity(projectile, gravityStrength);

        for (auto& proj : projectile) {
            proj.updatePosition();
        }

        window.clear();


        for (auto& proj : projectile) {
            window.render(proj);
        }

        for (auto& entity : entities) {
            window.render(entity);
        }

        player.render(window.getRenderer());
        window.display();
    }

    window.cleanUp();
    SDL_Quit();
    return 0;
}

