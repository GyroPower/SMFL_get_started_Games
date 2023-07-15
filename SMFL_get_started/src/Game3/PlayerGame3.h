#pragma once
#include "../stdafx.h"

class PlayerGame3
{
private:

	sf::Sprite sprite;
	sf::Texture texture;
	sf::RectangleShape Playerhp;
	sf::RectangleShape outlineHp;

	sf::Vector2f direction;
	sf::Vector2f position;

	int MaxHp;
	int hp;
	float moveSpeed;

	//Privates functions
	void initTexture();
	void initSprite();
	void initVariables();
	void initShape();

public:

	PlayerGame3();
	~PlayerGame3();

	void input();
	void move();
	void update();
	void render(sf::RenderTarget& target);

	void DamagePlayer(int damage);

	const sf::Vector2f& getPosition() const;
	const sf::FloatRect getBounds() const;
	const int getHp() const;

	void setPosition(sf::Vector2f pos);
};