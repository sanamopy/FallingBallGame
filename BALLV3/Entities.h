#pragma once
#ifndef Entity_h
#define Entity_h
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <random>
#include <ctime>
//const velocityY = 32
const int max_entities = 60;
class Entity //every entity in game
{
public:
	Entity(float p_x, float p_y, SDL_Texture* p_text, float velX = 0.0f, float velY = 0.0f, bool projectile = false);

	static void Spawn(SDL_Event& event, std::vector<Entity>& entities, SDL_Texture* entityTexture, int windowWidth, int windowHeight);


	void render(SDL_Renderer* renderer);
	void updatePosition();


	SDL_Texture* getTexture();
	SDL_Rect getCurrentFrame() const;
	SDL_Rect getHitbox() const;


	float getX(); //This makes it read only variables (less bugs)
	float getY();
	bool getisProjectile() const;
	float getVelocityY();
	float getVelocityX();


private:
	//int hp; //to be used later
	float velocityY;
	float velocityX;
	bool isProjectile;
	float x, y;
	SDL_Rect currentFrame;
	SDL_Texture* texture;

};



#endif // !Entity_h
