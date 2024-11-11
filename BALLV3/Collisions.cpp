#include "Collisions.h"
#include "Entities.h"

bool Collisions::contact(const SDL_Rect& rectA, const SDL_Rect& rectB) 
{
    return SDL_HasIntersection(&rectA, &rectB);
}

//PITA
bool Collisions::checkCollisions(std::vector<Entity>& entities, std::vector<Entity>& projectiles, Player& player)
{
    bool collisionDetected = false;

    for (auto& projectile : projectiles) {
        const SDL_Rect projectileHitbox = projectile.getHitbox();

        for (auto entityIt = entities.begin(); entityIt != entities.end();) {
            const SDL_Rect entityHitbox = entityIt->getHitbox();

            if (!entityIt->getisProjectile() && contact(projectileHitbox, entityHitbox)) {
                //std::cout << "COLLISION TRES BIEN!" << std::endl;

                bounceProjectile(projectile, entityHitbox);

                projectile.setHasCollided(true);

                if (!entityIt->isWall && entityIt->takeDamage()) {
                    entityIt = entities.erase(entityIt);
                    player.incrementScore();              // Increment score here


                }
                else {
                    ++entityIt;
                }

                collisionDetected = true;
                break;
            }
            else {
                ++entityIt;
            }
        }
    }
    return collisionDetected;
}

void Collisions::bounceProjectile(Entity& projectile, const SDL_Rect& entityHitbox) 
{
    SDL_Rect projectileHitbox = projectile.getHitbox();

    // funny amplify bouncy
    const float bounceMultiplier = 1.0f; 

    if (projectileHitbox.x + projectileHitbox.w >= entityHitbox.x &&
        projectileHitbox.x <= entityHitbox.x + entityHitbox.w) 
    {
        projectile.setVelocityY(-projectile.getVelocityY() * bounceMultiplier);
    }
    if (projectileHitbox.y + projectileHitbox.h >= entityHitbox.y &&
        projectileHitbox.y <= entityHitbox.y + entityHitbox.h) 
    {
        projectile.setVelocityX(-projectile.getVelocityX() * bounceMultiplier);
    }
}

//PITA
void Collisions::applyGravity(std::vector<Entity>& projectiles, float gravityStrength) 
{
    for (auto& projectile : projectiles) {
        if (projectile.getisProjectile() && projectile.getHasCollided()) { 
            float newVelocityY = projectile.getVelocityY() + gravityStrength; 
            projectile.setVelocityY(newVelocityY); 
        }
    }
}
