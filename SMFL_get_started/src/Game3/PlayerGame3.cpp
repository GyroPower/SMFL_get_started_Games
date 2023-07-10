#include "PlayerGame3.h"




void PlayerGame3::initTexture()
{
	//Load a texture from file
}

void PlayerGame3::initSprite()
{
	//Set the texture to the sprite	
	this->sprite.setTexture(this->texture);
}

PlayerGame3::PlayerGame3()
{
	this->initTexture();
	this->initSprite();
}

PlayerGame3::~PlayerGame3()
{

}

void PlayerGame3::update()
{

}

void PlayerGame3::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
