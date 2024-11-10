#pragma once
#ifndef Collisions_h
#define Collisions_h
#include "Entities.h"
#include "Player.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
class Collisions {
public:
    static bool contact(const SDL_Rect& rectA, const SDL_Rect& rectB);

    static bool checkCollisions(std::vector<Entity>& entities, std::vector<Entity>& projectile);

    static void bounceProjectile(Entity& projectile, const SDL_Rect& entityHitbox);

    static void applyGravity(std::vector<Entity>& projectiles, float gravityStrength);

private:

};

#endif