#pragma once
#include "../stdafx.h"



class Enemy
{
private:
	
	sf::CircleShape shape;

	sf::Vector2f direction;


	int hp;
	int hpMax;
	int damage;
	int points;
	float speed;

	void initVariables();
	void initShape();

public:


	Enemy(float posX, float posY);
	~Enemy();

	sf::Vector2f getPosition();
	sf::FloatRect getBounds();

	void move(sf::RenderTarget& target);
	void update(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);

	const int getPoints() const;
	const int& getDamage() const;
	void DamageEnemy();
	const int getHp() const;
	const int getMaxHp() const;
};