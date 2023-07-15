#include "Bullet.h"


Bullet::Bullet()
{

}

Bullet::Bullet(sf::Texture* texture, float posX, float posY, float dirX, float dirY, float move_Speed)
{
	this->sprite.setTexture(*texture);
	this->sprite.setScale(0.8f, 0.8f);
	this->sprite.setPosition(posX, posY);

	this->direction.x = dirX;
	this->direction.y = dirY;
	this->moveSpeed = move_Speed;
}

Bullet::~Bullet()
{

}

const sf::FloatRect Bullet::getBound() const
{
	return this->sprite.getGlobalBounds();
}

void Bullet::update()
{
	//Movement
	this->sprite.move(this->direction * this->moveSpeed);
}

void Bullet::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
