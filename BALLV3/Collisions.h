#pragma once
#ifndef Collisions_h
#define Collisions_h
#include "Entities.h"
#include "Player.h"
#include "Entities.h"
#include "Audio.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

class Entity;
class Player;
class PowerUp;

class Collisions{
public:
    static bool contact(const SDL_Rect& rectA, const SDL_Rect& rectB);

    static bool checkCollisions(std::vector<Entity>& entities, std::vector<Entity>& projectile, Player& player, Audio& audio);

    static void bounceProjectile(Entity& projectile, const SDL_Rect& entityHitbox);

    static void applyGravity(std::vector<Entity>& projectiles, float gravityStrength);

    static void setBounceMultiplier(float newMultiplier);

    static float getBounceMultiplier();



private:
    static float bounceMultiplier;
};

#endif