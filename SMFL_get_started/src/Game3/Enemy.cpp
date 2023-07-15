#include "Enemy.h"

void Enemy::initVariables()
{
	int val = rand() % 100;
	float enemyStats = 4.f;
	int hp = 3;

	if (val > 60 && val <= 80)
	{
		enemyStats = 2.f;
		hp = 8;

	}
	else if (val <= 60 && val > 10)
	{
		enemyStats = 3.f;
		hp = 7;
	}
	else if (val > 0 && val <= 10)
	{
		enemyStats = 5.f;
		hp = 3;
	}
	this->speed = enemyStats;
	this->hpMax = hp;
	this->hp = this->hpMax;
	this->damage = enemyStats;
	this->points = enemyStats;

	int x = rand() % 2;
	float dir_x = 1.f;

	if (x > 0)
		dir_x = -1.f;
	
	this->direction = sf::Vector2f(dir_x, 1.f);
	
}

void Enemy::initShape()
{
	this->shape.setRadius(rand() % 10 + 20);

	this->shape.setPointCount(rand() % 4  + 3);
	this->shape.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1));
}

Enemy::Enemy(float posX,float posY)
{
	this->initShape();
	this->initVariables();
	this->shape.setPosition(posX, posY);
}

Enemy::~Enemy()
{

}

sf::Vector2f Enemy::getPosition()
{
	return this->shape.getPosition();
}

sf::FloatRect Enemy::getBounds()
{
	return this->shape.getGlobalBounds();
}

void Enemy::move(sf::RenderTarget& target)
{
	if (this->shape.getPosition().x + this->shape.getGlobalBounds().width >= target.getSize().x)
		this->direction.x = -1;
	else if (this->shape.getPosition().x <= 0)
		this->direction.x = 1;

	this->shape.move(this->direction * this->speed);
}


void Enemy::update(sf::RenderTarget& target)
{
	this->move(target);
}

const int Enemy::getPoints() const
{
	return this->points;
}

const int& Enemy::getDamage() const
{
	return this->damage;
}

void Enemy::DamageEnemy()
{
	this->hp -= 1;
}

const int Enemy::getHp() const
{
	return this->hp;
}

const int Enemy::getMaxHp() const
{
	return this->hpMax;
}

void Enemy::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}
