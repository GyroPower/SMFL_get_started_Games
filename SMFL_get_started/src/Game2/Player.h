#pragma once
#include "../stdafx.h"


class Player
{
private:
	//Shape of the player
	sf::RectangleShape shape;

	//movement variables
	sf::Vector2f direction;
	sf::Vector2f playerpos;
	float speed;

	//Hp
	int hp;
	int maxHp;

	//Change Color
	float changeTimer;
	float maxChangeTimer;
	bool changed;

	void initVariables();
	void initShape();

public:
	Player();
	~Player();
	
	
	//getAttributes
	const sf::RectangleShape& getShape()const;
	const int& getHp() const;
	const int& getMaxHp() const;

	//Functions
	void takeDamage(const int damage);
	void gainhealth(const int health);
	void setColor(sf::Color color);


	void renderPlayer(sf::RenderTarget& target);
	void UpdatePlayer(sf::RenderWindow& target);
	void updateColor();

	void Input();
	void Collision(sf::RenderTarget& target);
	void Move(sf::RenderTarget& target);
	sf::Vector2f playerPos_return();
	
};