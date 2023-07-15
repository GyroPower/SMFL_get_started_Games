#include "PlayerGame3.h"




void PlayerGame3::initTexture()
{
	//Load a texture from file

	if (!this->texture.loadFromFile("textures/ship.png"))
	{
		std::cout << "ERROR::PLAYER::INITTEXTURE::could not load texture file" << "\n";
	}
}

void PlayerGame3::initSprite()
{
	//Set the texture to the sprite	
	this->sprite.setTexture(this->texture);

	//resize sprite
	this->sprite.scale(0.1f, 0.1f);
	this->sprite.setPosition(300.f,500.f);
}

void PlayerGame3::initVariables()
{
	this->direction = sf::Vector2f(0.f, 0.f);
	this->moveSpeed = 10.f;
	this->MaxHp = 30;
	this->hp = this->MaxHp;
}

void PlayerGame3::initShape()
{
	this->Playerhp.setSize(sf::Vector2f((static_cast<float>(this->hp) / this->MaxHp) * 200, 10.f));
	this->Playerhp.setPosition(10.f,50.f);
	this->Playerhp.setFillColor(sf::Color::Red);
	this->outlineHp.setSize(sf::Vector2f((static_cast<float>(this->hp) / this->MaxHp) * 200, 10.f));
	this->outlineHp.setPosition(10.f, 50.f);
	this->outlineHp.setFillColor(sf::Color::Black);
	this->outlineHp.setOutlineColor(sf::Color::White);
	this->outlineHp.setOutlineThickness(1.f);
}

PlayerGame3::PlayerGame3()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initShape();
}

PlayerGame3::~PlayerGame3()
{

}


void PlayerGame3::input()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		this->direction.x = 1;

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		this->direction.x = -1;

	else
		this->direction.x = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		this->direction.y = -1;

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		this->direction.y = 1;
	else
		this->direction.y = 0;
}

void PlayerGame3::move()
{
	this->sprite.move(this->direction * this->moveSpeed);
}

void PlayerGame3::update()
{
	this->input();
	this->move();
}

void PlayerGame3::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
	target.draw(this->outlineHp);
	target.draw(this->Playerhp);
}

void PlayerGame3::DamagePlayer(int damage)
{
	this->hp -= damage;
	if (this->hp <= 0)
		this->hp = 0;
	this->Playerhp.setSize(sf::Vector2f((static_cast<float>(this->hp) / this->MaxHp) * 200, 10.f));
	
}

const sf::Vector2f& PlayerGame3::getPosition() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect PlayerGame3::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const int PlayerGame3::getHp() const
{
	return this->hp;
}

void PlayerGame3::setPosition(sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}
