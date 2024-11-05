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

		int playerCenterX = rect.x + rect.w / 2;
		int playerCenterY = rect.y + rect.h / 2;
		double deltaX = mouseX - playerCenterX;
		double deltaY = mouseY - playerCenterY;
		double angle = atan2(deltaY, deltaX);


		float projectileX = playerCenterX;
		float projectileY = playerCenterY;

		float velocityX = velocity * cos(angle);
		float velocityY = velocity * sin(angle);


		projectile.emplace_back(projectileX, projectileY, projectileTexture, velocityX, velocityY, true);
		//std::cout << "Projectile created at x: " << projectileX << ", y: " << projectileY << std::endl;

	}
}




void Player::render(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

SDL_Rect Player::getRect() const
{
	return rect;
}



