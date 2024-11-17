#include "Player.h"
Player::Player(int width, int height, SDL_Texture* texture, int& windowWidth, int& windowHeight)
	:texture(texture)
{
	rect = { 0, 0, 32, 32 };
	rect.x = (windowWidth / 2) - (rect.w / 2);
	rect.y = 64;
}



void Player::aiming() const
{
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	int playerCenterX = rect.x + rect.w / 2;
	int playerCenterY = rect.y + rect.h / 2;

	double deltaX = mouseX - playerCenterX;
	double deltaY = mouseY - playerCenterY;
	double angle = atan2(deltaY, deltaX) * 180 / M_PI;
}

void Player::fireProjectile(std::vector<Entity>& projectile, SDL_Texture* projectileTexture, int velocity) const
{
	int mouseX;
	int mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	int playerCenterX = rect.x + rect.w / 2;
	int playerCenterY = rect.y + rect.h / 2;

	double deltaX = mouseX - playerCenterX;
	double deltaY = mouseY - playerCenterY;
	double angle = atan2(deltaY, deltaX);

	int projectileX = playerCenterX;
	int projectileY = playerCenterY;

	int velocityX = velocity * cos(angle);
	int velocityY = velocity * sin(angle);

	// Spawn the projectile
	projectile.emplace_back(projectileX, projectileY, projectileTexture, velocityX, velocityY, true);
	std::cout << projectile.size() << std::endl; 
	//projectile size not being done properly 

}

void Player::shoot(SDL_Event& event, std::vector<Entity>& projectiles, SDL_Texture* projectileTexture, int velocity) const
{
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
	{
		while (projectiles.size() < maxProjectiles)
		{
			fireProjectile(projectiles, projectileTexture, velocity);
			//ask prof for help cuz idfk 
		}

		if (!projectiles.empty())
		{
			std::cout << "Projectile size = " << projectiles.size() << std::endl;
		}
	}
}




void Player::setMaxProjectiles(int newMax) {
	maxProjectiles = newMax;
}
int Player::getMaxProjectiles() const
{
	return maxProjectiles;
}
//PITA
bool Player::outOfBounds(std::vector<Entity>& projectile, int& windowWidth, int& windowHeight, bool* detectOutOfBounds, Audio& audio2)
{
	*detectOutOfBounds = false;

	for (auto it = projectile.begin(); it != projectile.end(); )
	{
		if (it->getX() < 0 || it->getX() > windowWidth || it->getY() < 0
			|| it->getY() > windowHeight || it->getY() < 64)
		{
			it = projectile.erase(it);
			*detectOutOfBounds = true;
			audio2.play();
		}
		else {
			++it;
		}
	}

	// Debugging: Check remaining projectiles
	// std::cout << "Projectiles remaining: " << projectile.size() << "\n";
	// Debugging: Output shooting state


	return *detectOutOfBounds;
}



void Player::setX(int x) { rect.x = x; }
void Player::setY(int y) { rect.y = y; }


void Player::incrementScore() {
	score += 1;
	//std::cout << "SCORE: " << score << std::endl;
}

int Player::getScore() const {
	return score;
}

void Player::render(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

SDL_Rect Player::getRect() const
{
	return rect;
}

bool Player::getp_OutOfBounds() const
{
	return detectOutOfBounds;
}

float Player::getProjectileX() const
{
	return projectileX;
}

float Player::getProjectileY() const
{
	return projectileY;
}

float Player::getVelocityX() const
{
	return velocityX;
}

float Player::getVelocityY() const
{
	return velocityY;
}

/*void Player::shoot(SDL_Event& event, std::vector<Entity>& projectile, SDL_Texture* projectileTexture, int velocity) const
{
	// Static variables to manage shooting
	static Uint32 lastShotTime = 0;  // Time of the last shot
	static int shotsFired = 0;      // Number of shots fired in the current sequence
	static bool isShooting = false; // Whether a shooting sequence is active

	// Current time
	Uint32 currentTime = SDL_GetTicks();

	// Delay between shots
	const Uint32 shotInterval = 100; // 100ms delay between shots

	// Start a new shooting sequence if spacebar is pressed
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE && !isShooting)
	{
		isShooting = true;    // Begin shooting sequence
		shotsFired = 0;       // Reset shot counter
		lastShotTime = currentTime; // Set the initial timer

		fireProjectile(projectile, projectileTexture, velocity); // Fire the first shot
		shotsFired++;
	}

	// Handle subsequent shots in the sequence

	if (isShooting)
	{
		if (shotsFired < maxProjectiles && currentTime - lastShotTime >= shotInterval)
		{
			fireProjectile(projectile, projectileTexture, velocity); // Fire the next shot
			shotsFired++;
			lastShotTime = currentTime; // Update the last shot time
			std::cout << "Projectile size: " << projectile.size() << std::endl;
		}

		// End the shooting sequence if the max projectiles have been fired
		if (shotsFired >= maxProjectiles)
		{
			isShooting = false; // Reset shooting state
		}
	}


	if (isShooting && (shotsFired < maxProjectiles || !projectile.empty()) && (currentTime - lastShotTime >= shotInterval))
	{
		fireProjectile(projectile, projectileTexture, velocity); // Fire next shot
		shotsFired++;
		lastShotTime = currentTime; // Update the timer
		std::cout << "Projectil size: " << projectile.size() << std::endl;
	}

	// End the shooting sequence only after all shots have been fired
	if (shotsFired == maxProjectiles)
	{
		isShooting = false;
	}
	//std::cout << "Projectil size end of: " << projectile.size() << std::endl;

}*/