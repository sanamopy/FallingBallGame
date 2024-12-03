#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <stdio.h>

#include "FontManager.h"
#include "Player.h"
#include "Collisions.h"
#include "Entities.h"
#include "RenderWindow.h"
#include "Audio.h"
#include "PowerUp.h"
class Entity;
int main(int argc, char* args[]) {
    std::cout << "Hello world" << std::endl;

    //Image
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) > 0) {
        std::cout << "SDL initialization failed: " << SDL_GetError() << std::endl;
    }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cout << "Image initialization failed: " << SDL_GetError() << std::endl;
    }
    //Font
    if (TTF_Init() == -1) {
        std::cout << "TTF initialization failed: " << TTF_GetError() << std::endl;
    }

    Audio audio;

    // Initialize audio
    if (!audio.initialize()) {
        std::cerr << "Failed to initialize audio: " << Mix_GetError() << std::endl;
        return -1;
    }

    // Load audio files
    if (!audio.loadMp3("hitSound.wav", "deathSound.wav", "levelUpSound.wav")) {
        std::cerr << "Failed to load audio files: " << Mix_GetError() << std::endl;
        return -1;
    }


    const int maxFPS = 32;
    const int frame_time = 1000 / maxFPS;
    Uint32 framestart;
    int frame;
    const float gravityStrength = 6.0f;

    srand(static_cast<unsigned int>(time(0)));
    int windowHeight = 840;
    int windowWidth = 620;

    RenderWindow window("window", windowWidth, windowHeight);

    SDL_Texture* blueTexture = window.loadTexture("PNG1-PLAYER.png");
    SDL_Texture* projectileTexture = window.loadTexture("PNG1-PROJECTILE.png");

    //SDL_Texture* powerUpTexture = window.loadTexture("PNG1-PURPLE.png"); 
    //PowerUp::setTexture(powerUpTexture); 

    std::vector<Entity> entities;
    std::vector<Entity> projectile;
    std::vector<PowerUp> powerUps;

    SDL_Surface* mouse = IMG_Load("PNG1-PINK.png");
    SDL_Cursor* cursor = SDL_CreateColorCursor(mouse, 0, 0);
    SDL_FreeSurface(mouse);


    Player player(300, 300, blueTexture, windowWidth, windowHeight);

    window.addWalls(entities);

    FontManager::Instance().LoadFont("default", "HomeVideoBold-R90Dv.ttf", 24);

    bool gameRunning = true;
    SDL_Event event;

    //move texture choice into entities.cpp
    SDL_Texture* redTexture = window.loadTexture("PNG-RED.png");
    SDL_Texture* greenTexture = window.loadTexture("PNG-GREEN.png");
    SDL_Texture* magentaTexture = window.loadTexture("PNG-MAGENTA.png");
    SDL_Texture* purpleTexture = window.loadTexture("PNG-PURPLE.png");
    SDL_Texture* yellowTexture = window.loadTexture("PNG-YELLOW.png");

    SDL_Texture* textures[] = { redTexture, greenTexture, magentaTexture, purpleTexture, yellowTexture };

    static int spawnCounter = 0;


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

        Player::outOfBounds(projectile, windowWidth, windowHeight, &isOutOfBounds, audio);

        SDL_Texture* chosenTexture = textures[spawnCounter % 5];
        Entity::Spawn(event, entities, chosenTexture, windowWidth, windowHeight, &isOutOfBounds);
        spawnCounter++; // Move to the next texture

        Collisions::checkCollisions(entities, projectile, player, audio, audio);

        Collisions::applyGravity(projectile, gravityStrength);

        for (auto& proj : projectile) {
            proj.updatePosition();
        }

        SDL_SetRenderDrawColor(window.getRenderer(), 128, 128, 128, 255);
        SDL_RenderClear(window.getRenderer());

        for (auto& proj : projectile) {
            window.render(proj);
        }
        for (auto& entity : entities) {

            window.render(entity);
        }

        player.render(window.getRenderer());

        SDL_Color white = { 255, 255, 255 };
        FontManager::Instance().RenderScore("default", white, 60, 20, window.getRenderer(), player);

        window.display();
    }

    FontManager::Instance().CleanUp();
    audio.cleanup();
    window.cleanUp();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}
