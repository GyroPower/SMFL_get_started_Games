#include "swagball.h"

void Swagball::initShape(const sf::RenderTarget& target)
{
	this->shape.setRadius(static_cast<float>(rand() % 10 + 10));
	sf::Color color;
	switch (this->type)
	{
	case DEFAULT:
		color = sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);
		break;

	case DAMAGING:
		color = sf::Color::Red;
		this->shape.setOutlineColor(sf::Color::White);
		this->shape.setOutlineThickness(2.f);
		break;

	case HEALING:
		color = sf::Color::Green;
		this->shape.setOutlineColor(sf::Color::White);
		this->shape.setOutlineThickness(2.f);
		break;
	}

	this->shape.setFillColor(color);

	sf::Vector2f pos(rand() % target.getSize().x, rand() % target.getSize().y);

	if ((pos.x + shape.getRadius() * 2) > target.getSize().x)
	{
		pos.x -= (shape.getRadius() * 2);
	}
	if ((pos.y + shape.getRadius() * 2) > target.getSize().y)
	{
		pos.y -= (shape.getRadius() * 2);
	}

	this->shape.setPosition(pos);
	this->position = this->shape.getPosition();
}

void Swagball::initVariables()
{
	
	this->direction = sf::Vector2f(1.f, 1.f);
	this->speed = 5;
}

Swagball::Swagball(sf::RenderTarget& target,int type)
	:type(type)
{
	this->initShape(target);
	this->initVariables();
}

Swagball::~Swagball()
{

}

const sf::CircleShape Swagball::getshape() const
{
	return this->shape;
}

const int& Swagball::getType() const
{
	return this->type;
}

void Swagball::update(sf::RenderTarget& target)
{
	//this->Move();
	//this->Collisions(target);
}

void Swagball::Collisions(sf::RenderTarget& target)
{
	this->position = this->shape.getPosition();
	if (this->position.x < 0)
	{
		this->shape.setPosition(0, this->position.y);
		this->direction.x = 1;
	}
	else if ((this->position.x + (this->shape.getRadius() * 2)) > target.getSize().x)
	{
		this->shape.setPosition(target.getSize().x - (this->shape.getRadius() * 2), this->position.y);
		this->direction.x = -1;
	}

	this->position = this->shape.getPosition();

	if (this->position.y < 0)
	{
		this->shape.setPosition(this->position.x, 0);
		this->direction.y = 1;
	}
	else if ((this->position.y+(this->shape.getRadius() * 2)) > target.getSize().y)
	{
		this->shape.setPosition(this->position.x,
			target.getSize().y - (this->shape.getRadius() * 2));
		this->direction.y = -1;
	}
}

void Swagball::Move()
{
	this->position = this->shape.getPosition();

	this->position.x += this->direction.x * this->speed;
	this->shape.setPosition(this->position.x, this->position.y);

	this->position = this->shape.getPosition();

	this->position.y += this->direction.y * this->speed;
	this->shape.setPosition(this->position.x, this->position.y);
}

void Swagball::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}
