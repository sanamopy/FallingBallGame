#include "Entities.h"
//ENTITIES 


Entity::Entity(float p_x, float p_y, SDL_Texture* p_text, float velX, float velY, bool projectile)
	: x(p_x), y(p_y), texture(p_text), velocityX(velX), velocityY(velY), isProjectile(projectile)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 32;
	currentFrame.h = 32;
}
void Entity::updatePosition() {
	const float gravity = 0.2;  // Gravity constant

	if (isProjectile) {
		y += velocityY;  // Move the projectile by its velocity
		x += velocityX;
	}
	else {
		// Apply gravity to non-projectile entities
		velocityY = 0;
		velocityX = 0;
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


void Entity::Spawn(SDL_Event& event, std::vector<Entity>& entities, SDL_Texture* entityTexture, int windowWidth, int windowHeight)
{
	static int entitiesToSpawn = 3;
	static bool initialSpawn = false;
	int spawnWidth = windowWidth - 64;
	int spawnHeight = windowHeight / 5;
	int availableSpots = max_entities - entities.size();

	if (!initialSpawn)
	{
		for (int i = 0; i < 3; i++)
		{
			float randomX = static_cast<float>(rand() % spawnWidth);
			float randomY = static_cast<float>(windowHeight - spawnHeight + rand() % spawnHeight);

			entities.emplace_back(randomX, randomY, entityTexture, 0.0f, false);

		}
		initialSpawn = true;
	}

	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_n) {

		int spawnCount = std::min(entitiesToSpawn, availableSpots);
		for (int i = 0; i < spawnCount; ++i)
		{


			float randomX = static_cast<float>(rand() % spawnWidth);
			float randomY = static_cast<float>(windowHeight - spawnHeight + rand() % spawnHeight);

			entities.emplace_back(randomX, randomY, entityTexture, 0.0f, false);
		}

		if (entities.size() < max_entities) {
			entitiesToSpawn++;
		}
		//move up 
		//move out of this function later
		//when ball out of bound move up later
		for (auto& entity : entities) 
		{
			if (!entity.isProjectile) {
				entity.y -= 32.0f;
			}
		}
	}
}

SDL_Rect Entity::getHitbox() const
{
	SDL_Rect rect;
	rect.x = static_cast<int>(x);
	rect.y = static_cast<int>(y);
	rect.w = currentFrame.w;
	rect.h = currentFrame.h;
	return rect;
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

SDL_Texture* Entity::getTexture()
{
	return texture;
}

SDL_Rect Entity::getCurrentFrame() const //For animations
{
	return currentFrame;
}


