#include "PlayerGame4.h"

void displayVelocity(sf::RenderTarget& target,std::string objectToRender)
{

}

void PlayerGame4::initTexture()
{
	if (!this->texture.loadFromFile("textures/player_sheet.png"))
	{
		std::cout << "ERROR::PLAYERGAME4::INITEXTURE::Could not init texture" << "\n";
	}
}


void PlayerGame4::initSprite()
{
	this->sprite.setTexture(this->texture);
	this->currentFrame = sf::IntRect(0, 0, 40, 50);
	this->sprite.setTextureRect(this->currentFrame);
	this->sprite.scale(sf::Vector2f(2.f, 2.f));
}

void PlayerGame4::InitVariables()
{
	this->animState = PLAYER_ANIMATION_STATES::IDLE;
}

void PlayerGame4::initAnimations()
{
	this->animTime.restart();
	this->AnimSwitch = true;
}

void PlayerGame4::initPhysics()
{
	this->velocityMax = 15.f;
	this->acceleration = 3.f;
	this->drag = 0.84f;
	this->velocityMin = 1.f;
	this->gravity = 4.f;
	this->velocityMaxY = 15.f;
}

PlayerGame4::PlayerGame4()
{
	this->initTexture();
	this->initSprite();
	this->InitVariables();
	this->initAnimations();
	this->initPhysics();
}

PlayerGame4::~PlayerGame4()
{
}

const sf::Vector2f PlayerGame4::getPosition() const
{
	return this->sprite.getPosition();
}

const bool& PlayerGame4::getAnimSwitch()
{
	bool anim_switch = this->AnimSwitch;
	if (this->AnimSwitch)
		this->AnimSwitch = false;

	return anim_switch;
}

const sf::FloatRect PlayerGame4::getGlobalBounds()
{
	return this->sprite.getGlobalBounds();
}

void PlayerGame4::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void PlayerGame4::resetVelocity()
{
	this->velocity.y = 0.f;
}

void PlayerGame4::Move(const float dir_x, const float dir_y)
{

	this->velocity.y += 1.0f * this->gravity;
	if (std::abs(this->velocity.y) > this->velocityMaxY)
	{
		this->velocity.y = this->velocityMaxY * ((this->velocity.y < 0.f) ? -1.f : 1.f);
	}

	//Acceleration
	this->velocity.x += dir_x * this->acceleration;
	//this->velocity.y += dir_y * this->acceleration;

	//Limit velocity
	if (std::abs(this->velocity.x) > this->velocityMax)
	{
		this->velocity.x = this->velocityMax * ((this->velocity.x < 0.f) ? -1.f : 1.f);
	}

}

void PlayerGame4::resetAnimationTimer()
{
	this->animTime.restart();
	this->AnimSwitch = true;
}

void PlayerGame4::updatePhisycs()
{
	this->velocity.y += 1.0f * this->gravity;

	//Deceleration
	this->velocity *= this->drag;

	//Limit deceleration
	if (std::abs(this->velocity.x) < this->velocityMin)
		this->velocity.x = 0.f;
	if (std::abs(this->velocity.y) < this->velocityMin)
		this->velocity.y = 0.f;

	this->sprite.move(this->velocity);

}

void PlayerGame4::updateMove()
{
	this->animState = PLAYER_ANIMATION_STATES::IDLE;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		this->Move(-2.f,0.f);
		this->animState = PLAYER_ANIMATION_STATES::MOVING_LEFT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		this->Move(2.f, 0.f);
		this->animState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;
	}

	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		this->sprite.move(0.f, -2.f);
		this->moving = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		this->sprite.move(0.f, 2.f);
		this->moving = true;
	}*/
}


void PlayerGame4::update()
{
	this->updateMove();
	this->updatePhisycs();
	this->updateAnimations();
}

void PlayerGame4::updateAnimations()
{
	
	if (this->animState == PLAYER_ANIMATION_STATES::IDLE)
	{
		if (this->animTime.getElapsedTime().asSeconds() >= 0.2f || this->getAnimSwitch())
		{
			this->currentFrame.top = 0;
			this->currentFrame.left += 40;
			if (this->currentFrame.left >= 160.f)
				this->currentFrame.left = 0.f;

			this->animTime.restart();
		}
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_RIGHT || this->getAnimSwitch())
	{
		if (this->animTime.getElapsedTime().asSeconds() >= 0.07f)
		{
			this->currentFrame.top = 50;
			this->currentFrame.left += 40;
			if (this->currentFrame.left >= 360.f)
				this->currentFrame.left = 0.f;

			this->animTime.restart();
		}
			this->sprite.setScale(2.f, 2.f);
			this->sprite.setOrigin(0.f,0.f);
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_LEFT || this->getAnimSwitch())
	{
		if (this->animTime.getElapsedTime().asSeconds() >= 0.07f)
		{
			this->currentFrame.top = 50;
			this->currentFrame.left += 40;
			if (this->currentFrame.left >= 360.f)
				this->currentFrame.left = 0.f;

			this->animTime.restart();
		}
			this->sprite.setScale(-2.f, 2.f);
			this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, 0.f);
	}
	else
		this->animTime.restart();

	this->sprite.setTextureRect(this->currentFrame);
}

void PlayerGame4::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
	sf::CircleShape circ;
	circ.setFillColor(sf::Color::Red);
	circ.setRadius(2.f);
	circ.setPosition(this->sprite.getPosition());
	target.draw(circ);
}
