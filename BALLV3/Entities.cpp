#include "Entities.h"
//ENTITIES 


Entity::Entity(float p_x, float p_y, SDL_Texture* p_text, float velX, float velY, bool projectile, int hp, bool is_wall)
    : x(p_x), y(p_y), texture(p_text), velocityX(velX), velocityY(velY), isProjectile(projectile), health(hp), isWall(is_wall)
{
    currentFrame.x = 0;
    currentFrame.y = 0;
    if (isProjectile) {
        currentFrame.w = 32;
        currentFrame.h = 32;
    }
    else if (isWall) {
        currentFrame.w = 50;
        currentFrame.h = 840;

    }
    else {
        currentFrame.w = 64;
        currentFrame.h = 64;
    }
}


bool Entity::takeDamage()
{
    if (health > 0) {
        health -= 1;
    }
    return health <= 0;

}


void Entity::updatePosition() {
    if (isProjectile) {
        y += velocityY;
        x += velocityX;
    }
}


void Entity::render(SDL_Renderer* renderer)
{
    SDL_Rect destRect = {
        static_cast<int>(x),
        static_cast<int>(y),
        currentFrame.w,
        currentFrame.h
    };
    SDL_RenderCopy(renderer, texture, &currentFrame, &destRect);
}

//PITA
void Entity::Spawn(SDL_Event& event, std::vector<Entity>& entities, SDL_Texture* entityTexture, int windowWidth, int windowHeight, bool* detectOutOfBound)
{

    static int entitiesToSpawn = 3;
    static int placeholder = 2;
    static bool initialSpawn = false;
    int spawnWidth = windowWidth - 128;
    int spawnHeight = windowHeight / 6;
    float minimumDistance = 128.0f;
    int maxAttempts = 10;

    /*check spawning location spaced out
    if it doesn't find any, spawn randomly*/

    if (!initialSpawn)
    {
        for (int i = 0; i < 3; i++)
        {
            float randomX, randomY;
            bool positionFound = false;
            int attempts = 0;

            while (!positionFound && attempts < maxAttempts) {
                randomX = static_cast<float>(rand() % spawnWidth);
                randomY = static_cast<float>(windowHeight - spawnHeight - (rand() % spawnHeight));
                positionFound = true;

                for (const auto& entity : entities) {
                    float dx = entity.x - randomX;
                    float dy = entity.y - randomY;
                    if (std::sqrt(dx * dx + dy * dy) < minimumDistance) {
                        positionFound = false;
                        break;
                    }
                }
                attempts++;
            }

            if (!positionFound && !entities.empty()) {
                randomX = static_cast<float>(rand() % spawnWidth); 
                randomY = static_cast<float>(windowHeight - spawnHeight - (rand() % spawnHeight));
            }

            entities.emplace_back(randomX, randomY, entityTexture, 0.0f, false);
        }
        initialSpawn = true;
    }

    if ((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_n) || (*detectOutOfBound))
    {
        for (int i = 0; i < entitiesToSpawn; ++i)
        {
            float randomX, randomY;
            bool positionFound = false;
            int attempts = 0;

            while (!positionFound && attempts < maxAttempts) {
                randomX = static_cast<float>(rand() % spawnWidth);
                randomY = static_cast<float>(windowHeight + (rand() % spawnHeight));
                positionFound = true;

                for (const auto& entity : entities) {
                    float dx = entity.x - randomX;
                    float dy = entity.y - randomY;
                    if (std::sqrt(dx * dx + dy * dy) < minimumDistance) {
                        positionFound = false;
                        break;
                    }
                }
                attempts++;
            }

            if (!positionFound && !entities.empty()) {
                randomX = static_cast<float>(rand() % spawnWidth);
                randomY = static_cast<float>(windowHeight + spawnHeight - (rand() % spawnHeight));
            }

            entities.emplace_back(randomX, randomY, entityTexture, 0.0f, false);
        }

        if (placeholder % 2 == 0) {
            entitiesToSpawn++;
        }
        placeholder++;

        for (auto& entity : entities)
        {
            if (!entity.isProjectile && !entity.isWall)
            {
                entity.y -= 128.0f;
            }
        }
    }
}


SDL_Rect Entity::getHitbox() const
{
    SDL_Rect rect;
    if (isProjectile)
    {
        rect.x = static_cast<int>(x);
        rect.y = static_cast<int>(y);
        rect.w = currentFrame.w;
        rect.h = currentFrame.h;
        
    }
    else {
        rect.x = static_cast<int>(x);
        rect.y = static_cast<int>(y);
        rect.w = currentFrame.w + 10; //KEEP AT 10 to avoid jittering
        rect.h = currentFrame.h;
    }
    return rect;

}

void Entity::setVelocityX(float vx) {
    velocityX = vx;
}

void Entity::setVelocityY(float vy) {
    velocityY = vy;
}



float Entity::getX()
{
    return x;
}

float Entity::getY()
{
    return y;
}

bool Entity::getisProjectile() const
{
    return isProjectile;

}
float Entity::getVelocityY()
{
    return velocityY;
}
float Entity::getVelocityX()
{
    return velocityX;
}
int Entity::getHealth()
{
    return health;
}

SDL_Texture* Entity::getTexture()
{
    return texture;
}

SDL_Rect Entity::getCurrentFrame() const
{
    return currentFrame;
}


bool Entity::getHasCollided() const {
    return hasCollided;
}

void Entity::setHasCollided(bool state) {
    hasCollided = state;
}
SDL_Rect& Entity::getCurrentFrame() {
    return currentFrame;
}

void Entity::setX(float newX) {
    x = newX;
}

void Entity::setY(float newY) {
    y = newY;
}
