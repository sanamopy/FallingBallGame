#include "Collisions.h"
#include "Entities.h"

bool Collisions::contact(const SDL_Rect& rectA, const SDL_Rect& rectB) {
    return SDL_HasIntersection(&rectA, &rectB);
}

bool Collisions::checkCollisions(std::vector<Entity>& entities, std::vector<Entity>& projectiles) {
    bool collisionDetected = false;

    for (auto& projectile : projectiles) {
        const SDL_Rect projectileHitbox = projectile.getHitbox();

        for (auto entityIt = entities.begin(); entityIt != entities.end(); ) {
            const SDL_Rect entityHitbox = entityIt->getHitbox();

            if (!entityIt->getisProjectile() && contact(projectileHitbox, entityHitbox)) {
                std::cout << "COLLISION MUY BUENO TRES BIEN" << std::endl;

                // Bounce the projectile instead of erasing
                bounceProjectile(projectile, entityHitbox);

                // Mark the projectile as having collided
                projectile.setHasCollided(true);

                if (entityIt->takeDamage()) {
                    entityIt = entities.erase(entityIt); // Erase if health is zero
                }
                else {
                    ++entityIt; // Move to the next entity if not erased
                }

                collisionDetected = true;
                continue; // Exit inner loop since the entity has been erased
            }
            else {
                ++entityIt; // Move to the next entity if no collision
            }
        }
    }

    return collisionDetected;
}

void Collisions::bounceProjectile(Entity& projectile, const SDL_Rect& entityHitbox) {
    SDL_Rect projectileHitbox = projectile.getHitbox();

    // funny amplify bouncy
    const float bounceMultiplier = 1.2f; // Increase for a stronger bounce

    if (projectileHitbox.x + projectileHitbox.w >= entityHitbox.x &&
        projectileHitbox.x <= entityHitbox.x + entityHitbox.w) {
        // Reverse and amplify the vertical velocity for a strong bounce
        projectile.setVelocityY(-projectile.getVelocityY() * bounceMultiplier);
    }
    if (projectileHitbox.y + projectileHitbox.h >= entityHitbox.y &&
        projectileHitbox.y <= entityHitbox.y + entityHitbox.h) {
        // Reverse and amplify the horizontal velocity for a strong bounce
        projectile.setVelocityX(-projectile.getVelocityX() * bounceMultiplier);
    }
}


void Collisions::applyGravity(std::vector<Entity>& projectiles, float gravityStrength) {
    for (auto& projectile : projectiles) {
        if (projectile.getisProjectile() && projectile.getHasCollided()) { // Apply only if the projectile has collided
            float newVelocityY = projectile.getVelocityY() + gravityStrength; // Increment velocityY
            projectile.setVelocityY(newVelocityY); // Update projectile's downward speed
        }
    }
}
