#pragma once
#include "../stdafx.h"

enum PLAYER_ANIMATION_STATES
{
	IDLE = 0, MOVING_LEFT , MOVING_RIGHT, JUMPING, FALLING
};

class PlayerGame4
{
private:
	//Sprite
	sf::Sprite sprite;
	sf::Texture texture;


	//Animation
	short animState;
	sf::IntRect currentFrame;
	sf::Clock animTime;
	bool AnimSwitch;
	
	//Physics
	sf::Vector2f velocity;
	float velocityMax;
	float velocityMin;
	float acceleration;
	float drag;
	float gravity;
	float velocityMaxY;

	//Init
	void InitVariables();
	void initTexture();
	void initSprite();
	void initAnimations();
	void initPhysics();

	//Core

public:
	PlayerGame4();
	~PlayerGame4();

	//getters
	const sf::Vector2f getPosition() const;
	const bool& getAnimSwitch();
	const sf::FloatRect getGlobalBounds();

	//Modifiers
	void setPosition(const float x, const float y);
	void resetVelocity();

	void Move(const float dir_x, const float dir_y);;
	void resetAnimationTimer();

	void updateMove();
	void updatePhisycs();
	void update();
	void updateAnimations();
	void render(sf::RenderTarget& target);

};