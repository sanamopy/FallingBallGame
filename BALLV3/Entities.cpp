#include "Entities.h"
//ENTITIES 


Entity::Entity(float p_x, float p_y, SDL_Texture* p_text, float velX, float velY, bool projectile, int hp)
	: x(p_x), y(p_y), texture(p_text), velocityX(velX), velocityY(velY), isProjectile(projectile), health(hp)
{
	health = 1; // hitbox issues
	currentFrame.x = 0;
	currentFrame.y = 0;
	if (isProjectile) {
		currentFrame.w = 32;
		currentFrame.h = 32;
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
		y += velocityY;  // Move the projectile by its velocity
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
	static bool initialSpawn = false;
	int spawnWidth = windowWidth - 64;
	int spawnHeight = windowHeight / 5;
	int availableSpots = max_entities - entities.size();

	// Initial spawn
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

	// Handle spawning when the 'N' key is pressed or if an entity is out of bounds
	if ((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_n) || (*detectOutOfBound))
	{
		float randomX, randomY;

		int spawnCount = std::min(entitiesToSpawn, availableSpots);
		for (int i = 0; i < spawnCount; ++i)
		{
			randomX = static_cast<float>(rand() % spawnWidth);
			randomY = static_cast<float>(windowHeight - spawnHeight + rand() % spawnHeight);

			entities.emplace_back(randomX, randomY, entityTexture, 0.0f, false);
		}

		if (entities.size() < max_entities)
		{
			entitiesToSpawn++;
		}

		// Move non-projectile entities up
		for (auto& entity : entities)
		{
			if (!entity.isProjectile)
			{
				entity.y -= 64.0f;
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

SDL_Rect Entity::getCurrentFrame() const //For animations
{
	return currentFrame;
}


bool Entity::getHasCollided() const {
	return hasCollided;
}

void Entity::setHasCollided(bool state) {
	hasCollided = state;
}
