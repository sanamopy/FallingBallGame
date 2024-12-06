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

class Entity
{
public:
	/**
	 * Constructs a new Entity object with the given parameters.
	 *
	 * @param p_x: The initial x-coordinate of the entity.
	 * @param p_y: The initial y-coordinate of the entity.
	 * @param p_text: The SDL_Texture object representing the entity's image.
	 * @param velX: The initial horizontal velocity of the entity (default: 0.0f).
	 * @param velY: The initial vertical velocity of the entity (default: 0.0f).
	 * @param projectile: Indicates whether the entity is a projectile (default: false).
	 * @param hp: The initial health points of the entity (default: 1).
	 * @param is_wall: Indicates whether the entity is a wall (default: false).
	 * @param is_powerUp: Indicates whether the entity is a power-up (default: false).
	 */
	Entity(float p_x, float p_y, SDL_Texture* p_text,
		float velX = 0.0f, float velY = 0.0f,
		bool projectile = false, int hp = 1,
		bool is_wall = false, bool is_powerUp = false);

	/**
	 * Spawns a new entity based on user input and game conditions.
	 *
	 * This function handles the creation of new entities in the game, such as projectiles or power-ups.
	 * It checks for user input events, verifies the entity count, and determines the entity's initial position
	 * and velocity based on the game state.
	 *
	 * @param event: The SDL_Event object representing the user input event.
	 * @param entities: A reference to the std::vector<Entity> container holding all existing entities in the game.
	 * @param entityTexture: The SDL_Texture object representing the image to be used for the new entity.
	 * @param windowWidth: The width of the game window.
	 * @param windowHeight: The height of the game window.
	 * @param detectOutOfBound: A pointer to a boolean variable indicating whether an entity has gone out of bounds.
	 *
	 * @return void: This function does not return any value.
	 */
	static void Spawn(SDL_Event& event,
		std::vector<Entity>& entities, SDL_Texture* entityTexture,
		int windowWidth, int windowHeight, bool* detectOutOfBound);

	/**
	 * Renders the entity on the specified SDL_Renderer.
	 *
	 * This function uses the entity's texture and current frame rectangle to render the entity on the given SDL_Renderer.
	 * The rendering is done at the entity's current position (x, y) within the game world.
	 *
	 * @param renderer: A pointer to the SDL_Renderer object on which the entity will be rendered.
	 *
	 * @return void: This function does not return any value.
	 */
	void render(SDL_Renderer* renderer);

	/**
	 * Updates the position of the entity based on its current velocity.
	 *
	 * This function calculates the new position of the entity by adding the current velocity components (velocityX and velocityY)
	 * to the entity's current coordinates (x and y). The updated position is then stored in the entity's x and y variables.
	 *
	 * @return void: This function does not return any value.
	 */
	void updatePosition();

	/**
	 * Reduces the entity's health by one point.
	 *
	 * This function decreases the entity's health by one point. If the entity's health reaches zero or below,
	 * the function returns true to indicate that the entity has been defeated. Otherwise, it returns false.
	 *
	 * @return bool: Returns true if the entity's health reaches zero or below, indicating that the entity has been defeated.
	 *               Returns false if the entity's health is still greater than zero.
	 */
	bool takeDamage();

	/**
	 * Retrieves the SDL_Texture object associated with the entity.
	 *
	 * This function returns a pointer to the SDL_Texture object that represents the image
	 * of the entity. The texture is used for rendering the entity on the SDL_Renderer.
	 *
	 * @return SDL_Texture*: A pointer to the SDL_Texture object associated with the entity.
	 */
	SDL_Texture* getTexture();

	/**
	 * Retrieves the current frame rectangle of the entity.
	 *
	 * This function returns a reference to the SDL_Rect object that represents the current frame
	 * of the entity's animation. The current frame is used to determine which part of the texture
	 * should be rendered on the screen.
	 *
	 * @return SDL_Rect&: A reference to the current frame rectangle of the entity.
	 *                     The returned SDL_Rect object contains the position and dimensions of the current frame.
	 */
	SDL_Rect& getCurrentFrame() const;

	/**
	 * Retrieves the hitbox rectangle of the entity.
	 *
	 * The hitbox represents the area of the entity that can be collided with other entities.
	 * This function returns a SDL_Rect object that contains the position and dimensions of the hitbox.
	 *
	 * @return SDL_Rect: A SDL_Rect object representing the hitbox of the entity.
	 *                   The returned SDL_Rect object contains the position (x, y) and dimensions (w, h) of the hitbox.
	 *                   The position and dimensions are relative to the game world.
	 */
	SDL_Rect Entity::getHitbox() const;

	/**
	 * Sets the horizontal velocity of the entity.
	 *
	 * This function updates the velocityX member variable of the entity to the specified value.
	 * The velocityX represents the horizontal speed of the entity in the game world.
	 *
	 * @param vx: The new horizontal velocity value for the entity. A positive value indicates
	 *             movement to the right, while a negative value indicates movement to the left.
	 *
	 * @return void: This function does not return any value.
	 */
	void setVelocityX(float vx);

	/**
	 * Sets the vertical velocity of the entity.
	 *
	 * This function updates the velocityY member variable of the entity to the specified value.
	 * The velocityY represents the vertical speed of the entity in the game world.
	 *
	 * @param vy: The new vertical velocity value for the entity. A positive value indicates
	 *             movement downwards, while a negative value indicates movement upwards.
	 *
	 * @return void: This function does not return any value.
	 */
	void setVelocityY(float vy);

	/**
	 * Sets the collision delay for the entity.
	 *
	 * This function updates the 'collisionDelay' member variable of the entity to the specified value.
	 * The collision delay is used to prevent immediate collisions between entities, such as projectiles and other game objects.
	 *
	 * @param delay: The new collision delay value for the entity. A positive value indicates the duration for which the entity
	 *                should not be able to collide with other entities. A value of 0.0f indicates that the entity can collide immediately.
	 *
	 * @return void: This function does not return any value.
	 */
	void setCollisionDelay(double);

	/**
	 * Checks whether the entity can collide with other entities.
	 *
	 * This function determines whether the entity is allowed to collide with other entities in the game world.
	 * The entity can collide if it is not a projectile and if the collision delay has expired.
	 *
	 * @return bool: Returns true if the entity can collide with other entities.
	 *               Returns false if the entity cannot collide due to being a projectile or due to the collision delay not having expired.
	 */
	bool canCollide() const;

	/**
	 * Updates the collision delay for the entity.
	 *
	 * This function updates the 'collisionDelay' member variable of the entity to the specified value.
	 * The collision delay is used to prevent immediate collisions between entities, such as projectiles and other game objects.
	 *
	 * @param delay: The new collision delay value for the entity. A positive value indicates the duration for which the entity
	 *                should not be able to collide with other entities. A value of 0.0f indicates that the entity can collide immediately.
	 *
	 * @return void: This function does not return any value.
	 */
	void updateDelay(double);

	/**
	 * Sets the y-coordinate of the entity.
	 *
	 * This function updates the y-coordinate of the entity to the specified value.
	 * The y-coordinate represents the vertical position of the entity within the game world.
	 *
	 * @param y: The new y-coordinate value for the entity. It should be a float value representing the vertical position.
	 *            The value should be within the bounds of the game world, otherwise, it may result in unexpected behavior.
	 *
	 * @return void: This function does not return any value. It directly updates the y-coordinate of the entity.
	 */
	void setPositionY(float);

	/**
	 * Sets the x-coordinate of the entity.
	 *
	 * This function updates the x-coordinate of the entity to the specified value.
	 * The x-coordinate represents the horizontal position of the entity within the game world.
	 *
	 * @param x: The new x-coordinate value for the entity. It should be a float value representing the horizontal position.
	 *            The value should be within the bounds of the game world, otherwise, it may result in unexpected behavior.
	 *
	 * @return void: This function does not return any value. It directly updates the x-coordinate of the entity.
	 */
	void setPositionX(float);

	/**
	 * Retrieves the current x-coordinate of the entity.
	 *
	 * This function returns the x-coordinate of the entity, which represents its horizontal position within the game world.
	 *
	 * @return float: The current x-coordinate of the entity. The value is a float representing the horizontal position.
	 *                The returned value should be within the bounds of the game world, otherwise, it may result in unexpected behavior.
	 */
	float getX();

	/**
	 * Retrieves the current y-coordinate of the entity.
	 *
	 * This function returns the y-coordinate of the entity, which represents its vertical position within the game world.
	 *
	 * @return float: The current y-coordinate of the entity. The value is a float representing the vertical position.
	 *                The returned value should be within the bounds of the game world, otherwise, it may result in unexpected behavior.
	 */
	float getY();

	/**
	 * Retrieves a boolean value indicating whether the entity is a projectile.
	 *
	 * This function checks the 'isProjectile' member variable of the entity and returns its value.
	 * The 'isProjectile' variable is set during the entity's construction and indicates whether the entity is a projectile.
	 *
	 * @return bool: Returns true if the entity is a projectile.
	 *               Returns false if the entity is not a projectile.
	 */
	bool getisProjectile() const;

	/**
	 * Retrieves the current vertical velocity of the entity.
	 *
	 * This function returns the current vertical velocity of the entity, which represents its speed in the vertical direction.
	 * The velocityY is a float value that indicates the entity's movement upwards (negative value) or downwards (positive value).
	 *
	 * @return float: The current vertical velocity of the entity.
	 *                 The returned value is a float representing the vertical speed.
	 *                 A positive value indicates movement downwards, while a negative value indicates movement upwards.
	 */
	float getVelocityY();

	/**
	 * Retrieves the current horizontal velocity of the entity.
	 *
	 * This function returns the current horizontal velocity of the entity, which represents its speed in the horizontal direction.
	 * The velocityX is a float value that indicates the entity's movement to the left (negative value) or to the right (positive value).
	 *
	 * @return float: The current horizontal velocity of the entity.
	 *                 The returned value is a float representing the horizontal speed.
	 *                 A positive value indicates movement to the right, while a negative value indicates movement to the left.
	 */
	float getVelocityX();

	/**
	 * Retrieves the current health points of the entity.
	 *
	 * This function returns the current health points of the entity.
	 * The health points represent the entity's vitality and determine whether it can continue to interact with other entities in the game.
	 *
	 * @return int: The current health points of the entity.
	 *              The returned value is an integer representing the entity's remaining health.
	 *              A value greater than zero indicates that the entity is alive and can continue to interact with other entities.
	 *              A value of zero or less indicates that the entity has been defeated and should be removed from the game world.
	 */
	int getHealth();

	/**
	 * Retrieves a boolean value indicating whether the entity has collided with another entity.
	 *
	 * This function checks the 'hasCollided' member variable of the entity and returns its value.
	 * The 'hasCollided' variable is updated whenever the entity collides with another entity in the game world.
	 *
	 * @return bool: Returns true if the entity has collided with another entity.
	 *               Returns false if the entity has not collided with any other entity.
	 */
	bool getHasCollided() const;

	/**
	 * Sets the 'hasCollided' member variable of the entity.
	 *
	 * This function updates the 'hasCollided' member variable to the specified boolean value.
	 * The 'hasCollided' variable is used to indicate whether the entity has collided with another entity in the game world.
	 *
	 * @param collided: The new boolean value for the 'hasCollided' member variable.
	 *                   - true: Indicates that the entity has collided with another entity.
	 *                   - false: Indicates that the entity has not collided with any other entity.
	 *
	 * @return void: This function does not return any value. It directly updates the 'hasCollided' member variable.
	 */
	void setHasCollided(bool);

	/**
	 * Retrieves the current frame rectangle of the entity.
	 *
	 * This function returns a reference to the SDL_Rect object that represents the current frame
	 * of the entity's animation. The current frame is used to determine which part of the texture
	 * should be rendered on the screen.
	 *
	 * @return SDL_Rect&: A reference to the current frame rectangle of the entity.
	 */
	SDL_Rect& getCurrentFrame();

	bool isWall;

	/**
	 * Sets the x-coordinate of the entity.
	 *
	 * This function updates the x-coordinate of the entity to the specified value.
	 * The x-coordinate represents the horizontal position of the entity within the game world.
	 *
	 * @param x: The new x-coordinate value for the entity.
	 *
	 * @return void: This function does not return any value.
	 */
	void setX(float);

	/**
	 * Sets the y-coordinate of the entity.
	 *
	 * This function updates the y-coordinate of the entity to the specified value.
	 * The y-coordinate represents the vertical position of the entity within the game world.
	 *
	 * @param y: The new y-coordinate value for the entity.
	 *
	 * @return void: This function does not return any value.
	 */
	void setY(float);

	/**
	 * Sets the base health of the entity to its initial value.
	 *
	 * This function resets the health of the entity to its initial value,
	 * which is stored in the 'baseHealth' member variable.
	 *
	 * @return void: This function does not return any value.
	 */
	void setBaseHealth();

private:
	int baseHealth;
	int health;
	bool ispowerUp;
	bool hasCollided = false;
	float velocityY;
	float velocityX;
	bool isProjectile;
	float x, y;
	SDL_Rect currentFrame;
	SDL_Texture* texture;

	double collisionDelay = 0.0f;

};



#endif // Entity_h