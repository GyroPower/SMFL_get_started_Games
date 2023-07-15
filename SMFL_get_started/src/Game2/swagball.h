#pragma once
#include "../stdafx.h"

enum SwagBallTypes { DEFAULT = 0, DAMAGING, HEALING, NROFTYPES };

class Swagball
{
private:
	sf::CircleShape shape;
	sf::Vector2f position;
	sf::Vector2f direction;
	float speed;

	int type;

	void initShape(const sf::RenderTarget& target);
	void initVariables();


public:

	Swagball(sf::RenderTarget& target,int type);
	~Swagball();

	const sf::CircleShape getshape() const;
	const int& getType() const;

	void Collisions(sf::RenderTarget& target);
	void Move();
	void update(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);

};
