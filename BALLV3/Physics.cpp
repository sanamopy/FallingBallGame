#include "Physics.h"
#include "Entities.h"

bool Physics::contact(const SDL_Rect& rectA, const SDL_Rect& rectB) {
    bool intersecting = SDL_HasIntersection(&rectA, &rectB);
    if (intersecting) {
        //std::cout << "Intersection detected!" << std::endl;
    }
    return intersecting;
}



bool Physics::checkCollisions(std::vector<Entity>& entities, std::vector<Entity>& projectiles) {
    //std::cout << "Checking collisions..." << std::endl; // Debug message

    bool collisionDetected = false;
    //std::cout << "Entities size: " << entities.size() << std::endl;
    //std::cout << "Projectiles size: " << projectiles.size() << std::endl;

    for (auto& projectile : projectiles) {
        const SDL_Rect projectileHitbox = projectile.getHitbox();

        for (auto entityIt = entities.begin(); entityIt != entities.end(); ) {
            const SDL_Rect entityHitbox = entityIt->getHitbox();

            // Debug: Print hitbox details
            //std::cout << "Projectile Hitbox - x: " << projectileHitbox.x << ", y: " << projectileHitbox.y
            //   << ", w: " << projectileHitbox.w << ", h: " << projectileHitbox.h << std::endl;
            //std::cout << "Entity Hitbox - x: " << entityHitbox.x << ", y: " << entityHitbox.y
            //    << ", w: " << entityHitbox.w << ", h: " << entityHitbox.h << std::endl;

            if (!entityIt->getisProjectile() && contact(projectileHitbox, entityHitbox)) {
                std::cout << "COLLISION MUY BUENO TRES BIEN" << std::endl;

                // Remove only the collided entity, not the projectile
                entityIt = entities.erase(entityIt);
                collisionDetected = true;
                break; // Exit inner loop since the entity has been erased
            }
            else {
                ++entityIt; // Move to the next entity if no collision
            }
        }
    }
    return collisionDetected;
}
