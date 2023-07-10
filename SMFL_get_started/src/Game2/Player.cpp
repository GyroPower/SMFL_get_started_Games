#include "Player.h"

void Player::initVariables()
{
	this->direction = sf::Vector2f(0.f,0.f);
	this->speed = 10.f;
	this->playerpos = this->shape.getPosition();
	this->maxHp = 10;
	this->hp = this->maxHp;
	this->changed = false;
	this->changeTimer = 0.f;
	this->maxChangeTimer = 5.f;
}

void Player::initShape()
{
	this->shape.setSize(sf::Vector2f(60.f, 60.f));
	this->shape.setFillColor(sf::Color::Green);
	this->shape.setPosition(300.f, 300.f);
}

Player::Player()
{
	this->initShape();
	this->initVariables();
}

Player::~Player()
{
	 
}

const sf::RectangleShape & Player::getShape() const
{
	return this->shape;
}

const int& Player::getHp() const
{
	return this->hp;
}

const int& Player::getMaxHp() const
{
	return this->maxHp;
}

void Player::takeDamage(const int damage)
{
	if (this->hp>0)
		this->hp -= damage;
	if (this->hp < 0)
		this->hp = 0;
}

void Player::gainhealth(const int health)
{
	if (this->hp < this->maxHp)
		this->hp += health;
	if (this->hp >= this->maxHp)
		this->hp = this->maxHp;
}

void Player::setColor(sf::Color color)
{
	this->changed = true;
	this->changeTimer = 0.f;
	this->shape.setFillColor(color);
}

void Player::renderPlayer(sf::RenderTarget& target)
{
	target.draw(this->shape);
}

void Player::updateColor()
{
	if (!this->changed)
		this->shape.setFillColor(sf::Color::Green);
	else
	{
		if (this->changeTimer > this->maxChangeTimer)
		{
			this->changed = false;
			this->changeTimer = 0;
		}
		else
		{
			this->changeTimer += 0.1f;
		}
	}
}

void Player::UpdatePlayer(sf::RenderWindow& target)
{
	this->Input();
	this->Move(target);
	this->Collision(target);
	this->updateColor();
}

void Player::Input()
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{

		this->direction.x = 1.f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->direction.x = -1.f;
	}
	else
	{
		this->direction.x = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->direction.y = -1.f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->direction.y = 1.f;
	}
	else
	{
		this->direction.y = 0;
	}
}

void Player::Collision( sf::RenderTarget& target)
{
	this->playerpos = this->shape.getPosition();

	if ((this->playerpos.x + this->shape.getSize().x) > target.getSize().x)
		this->shape.setPosition(target.getSize().x - this->shape.getSize().x,
			this->playerpos.y);

	else if (this->playerpos.x < 0)
		this->shape.setPosition(0, this->playerpos.y);

	this->playerpos = this->shape.getPosition();

	if (this->playerpos.y < 0)
		this->shape.setPosition(this->playerpos.x, 0);

	else if ((this->playerpos.y + this->shape.getSize().y) > target.getSize().y)
		this->shape.setPosition(this->playerpos.x,
			target.getSize().y - this->shape.getSize().y);

}

sf::Vector2f Player::playerPos_return()
{
	return this->playerpos;
}

void Player::Move(sf::RenderTarget& target)
{
	
	this->playerpos = this->shape.getPosition();
	
	
	this->shape.setPosition(this->playerpos.x + (this->direction.x * this->speed),
		this->playerpos.y);

	
	this->playerpos = this->shape.getPosition();

	this->shape.setPosition(this->playerpos.x,
		this->playerpos.y + (this->direction.y * this->speed));
	
	
	
}

	