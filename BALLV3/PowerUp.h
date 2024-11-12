#pragma once
#include <SDL.h>
#include <vector>
#include "Player.h"
class Entity;
class Player;
class PowerUp;
class PowerUp {
public:
    PowerUp(float x, float y, SDL_Texture* texture, int type);

    void applyEffect(Player& player);
    void render(SDL_Renderer* renderer);
    bool checkCollisionWithPlayer(const Player& player);

    static void setTexture(SDL_Texture* texture);
    static bool shouldSpawn();    
    static void resetSpawnCounter(); 
    static SDL_Texture* getTexture(); 


private:
    float x, y;
    SDL_Texture* texture;
    SDL_Rect rect;
    int type;

    static SDL_Texture* powerUpTexture;
    static int spawnCounter; 
};
