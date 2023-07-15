#pragma once
#include "../stdafx.h"


class Bullet
{
private:
	sf::Sprite sprite;

	sf::Vector2f direction;
	float moveSpeed;

public:
	Bullet();
	Bullet(sf::Texture* texture, float posX,float posY,float dirX,float dirY, float move_Speed);
	~Bullet();

	const sf::FloatRect getBound() const;

	void update();
	void render(sf::RenderTarget& target);
};