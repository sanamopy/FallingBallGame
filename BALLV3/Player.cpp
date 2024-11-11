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

void Player::shoot(SDL_Event& event, std::vector<Entity>& projectile, SDL_Texture* projectileTexture, int velocity)
{
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
	{
		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);

		int playerCenterX = rect.x + rect.w/2;
		int playerCenterY = rect.y + rect.h/2;
		double deltaX = mouseX - playerCenterX;
		double deltaY = mouseY - playerCenterY;
		double angle = atan2(deltaY, deltaX);


		projectileX = playerCenterX;
		projectileY = playerCenterY;

		velocityX = velocity * cos(angle);
		velocityY = velocity * sin(angle);


		projectile.emplace_back(projectileX, projectileY, projectileTexture, velocityX, velocityY, true);
		//std::cout << "Projectile created at x: " << projectileX << ", y: " << projectileY << std::endl;

	}
}

//PITA
bool Player::outOfBounds(std::vector<Entity>& projectile, int& windowWidth, int& windowHeight, bool* detectOutOfBounds)
{
	*detectOutOfBounds = false;
	for (auto it = projectile.begin(); it != projectile.end(); )
	{
		if (it->getX() < 0 || it->getX() > windowWidth || it->getY() < 0 
			|| it->getY() > (windowHeight) || it->getY() < 64)
		{
			it = projectile.erase(it);
			*detectOutOfBounds = true;
		}
		else {
			it++;
		}
	}
	return *detectOutOfBounds;
}



void Player::setX(int x) { rect.x = x; }
void Player::setY(int y) { rect.y = y; }


void Player::incrementScore() {
	score += 1;
	std::cout << "SCORE: " << score << std::endl;
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

