#pragma once
#ifndef Entity_h
#define Entity_h
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <random>
#include <ctime>
const int max_entities = 32;
class Entity //every entity in game
{
public:
	Entity(float p_x, float p_y, SDL_Texture* p_text,
		float velX = 0.0f, float velY = 0.0f,
		bool projectile = false, int hp = 1,
		bool is_wall = false);


	static void Spawn(SDL_Event& event, 
		std::vector<Entity>& entities, SDL_Texture* entityTexture,
		int windowWidth, int windowHeight, bool*detectOutOfBound);


	void render(SDL_Renderer* renderer);
	void updatePosition();
	bool takeDamage();

	SDL_Texture* getTexture();
	SDL_Rect getCurrentFrame() const;
	SDL_Rect getHitbox() const;


	void setVelocityX(float vx);
	void setVelocityY(float vy);

	float getX(); 
	float getY();
	bool getisProjectile() const;
	float getVelocityY();
	float getVelocityX();
	int getHealth();
	bool getHasCollided() const;
	void setHasCollided(bool state);
	SDL_Rect& getCurrentFrame();
	bool isWall;


private:

	bool hasCollided = false;
	int health;
	float velocityY;
	float velocityX;
	bool isProjectile;
	float x, y;
	SDL_Rect currentFrame;
	SDL_Texture* texture;

};



#endif // Entity_h
