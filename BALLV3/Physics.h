#pragma once
#pragma once
#ifndef Physics_h
#define Physics_h
#include "Entities.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
class Physics {
public:
    static bool contact(const SDL_Rect& rectA, const SDL_Rect& rectB);

    static bool checkCollisions(std::vector<Entity>& entities, std::vector<Entity>& projectile);

};

#endif