#include "PowerUp.h"
#include <cstdlib> 

SDL_Texture* PowerUp::powerUpTexture = nullptr; 
int PowerUp::spawnCounter = 0; 

PowerUp::PowerUp(float x, float y, SDL_Texture* texture, int type)
    : x(x), y(y), texture(texture), type(type) {
    rect = { static_cast<int>(x), static_cast<int>(y), 32, 32 };
}

void PowerUp::setTexture(SDL_Texture* texture) {
    powerUpTexture = texture; 
}

void PowerUp::applyEffect(Player& player) {
    
    player.setMaxProjectiles(player.getMaxProjectiles() + 1);
    
}

void PowerUp::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

bool PowerUp::checkCollisionWithPlayer(const Player& player) {
    SDL_Rect playerRect = player.getRect();
    return SDL_HasIntersection(&rect, &playerRect);
}

bool PowerUp::shouldSpawn() {
    spawnCounter++;
    return spawnCounter % 4 == 0;
}

void PowerUp::resetSpawnCounter() {
    spawnCounter = 0;
}

SDL_Texture* PowerUp::getTexture() {
    return powerUpTexture;
}