#include "Game3.h"

void Game3::initPlayer()
{
	this->player = new PlayerGame3();
	
}

void Game3::initWorldBack()
{
	if (!this->worldBackTex.loadFromFile("textures/background1.jpg"))
	{
		std::cout << "ERROR::GAME3::INITWORLDBACK::CAN'T LOAD TEXTURE" << "\n";
	}
	
	this->worldBackground.setTexture(this->worldBackTex);

}

void Game3::initTextures()
{
	this->textures["Bullet"] = new sf::Texture();
	this->textures["Bullet"]->loadFromFile("textures/bullet.png");
}

void Game3::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Game 3",
		sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);

}

void Game3::initEnemies()
{
	this->spawnTimer = 0;
	this->spawnTimerMax = 10.f;
}

void Game3::initFont()
{
	if (!this->font.loadFromFile("fonts/joystix.ttf"))
	{
		std::cout << "ERROR::GAME3.CPP::INITFONT::Could not initialize font" << "\n";
	}
}

void Game3::initText()
{
	this->UItext.setFont(this->font);
	this->UItext.setCharacterSize(20);
	this->UItext.setFillColor(sf::Color::White);
	this->UItext.setString("Test");
}

void Game3::initVariables()
{
	this->canShoot = true;
	this->shootTimer = 0;
	this->shootTimerMax = 0.7f;
	this->points = 0;
	this->endgame = false;
	this->playerDamaged = false;
	this->invecibleTime = 0.f;
	this->MaxinvencibleTime = 15.f;
	this->pointCount = 0;
}

Game3::Game3()
{
	this->initWindow();
	this->initTextures();
	this->initPlayer();
	this->initEnemies();
	this->initWorldBack();
	this->initFont();
	this->initText();
	this->initVariables();
}

Game3::~Game3()
{
	delete this->window;
	delete this->player;
	
	
	//delete all textures
	for (auto& texture : this->textures)
	{
		delete texture.second;
	}

	//Delete bullest
	for (auto& bullet : this->bullets)
	{
		delete bullet;
	}

	for (auto& enemy : this->enemies)
	{
		delete enemy;
	}
}

void Game3::pollEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
		}

	}
}

void Game3::run()
{
	while (this->window->isOpen())
	{
		
		this->update();
		this->render();
	}
}


void Game3::updateGui()
{
	std::stringstream ss;

	
	if (this->endgame)
	{
		ss << "GAMEOVER" << "\n" << "Points: " << this->points << "\n";
		this->UItext.setString(ss.str());
		this->UItext.setPosition(this->window->getSize().x / 2.f - (this->UItext.getGlobalBounds().width / 2.f),
			this->window->getSize().y / 2.f - (this->UItext.getGlobalBounds().height / 2.f));
		this->UItext.setCharacterSize(30);
	}
	else
		ss << "Points: " << this->points;


	this->UItext.setString(ss.str());
}

void Game3::renderGui()
{
	this->window->draw(this->UItext);
}

void Game3::InputMouse()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->canShoot)
	{
		this->canShoot = false;
		this->bullets.push_back(new Bullet(this->textures["Bullet"],
			this->player->getPosition().x + (this->player->getBounds().width / 2) - 3,
			this->player->getPosition().y - (this->player->getBounds().height / 2) + 20,
			0.f, -1.f, 5.f));
	}
	else
	{
		if (this->shootTimer > this->shootTimerMax)
		{
			this->shootTimer = 0.f;
			this->canShoot = true;
		}
		else
		{
			this->shootTimer += 0.1f;
		}
	}
}
 
void Game3::renderBullet()
{
	for (auto* bullet : this->bullets)
	{
		bullet->render(*this->window);
	}
}

void Game3::spawnEnemies()
{
	this->enemies.push_back(new Enemy(rand() % (this->window->getSize().x-10), -100.f));
}

void Game3::updateEnemiesAndCombat()
{
	this->spawnTimer += 0.1f;
	
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->spawnTimer = 0.f;

		if (this->enemies.size() < 10)
			this->spawnEnemies();
	}
		
	

	for (int i = 0; i < this->enemies.size(); i++)
	{
		bool removed = false;
		this->enemies[i]->update(*this->window);

		//Collision with the player
		if (!this->playerDamaged && this->enemies[i]->getBounds().intersects(this->player->getBounds()))
		{
			this->player->DamagePlayer(this->enemies[i]->getDamage());
			this->playerDamaged = true;
			
			delete this->enemies[i];
			this->enemies.erase(this->enemies.begin() + i);
			removed = true;
			if (this->player->getHp() <= 0)
				this->endgame = true;
		}
		else
		{	//Timer to make invencible the player after get a collision with an enemy
			//this not allow to drop all the hp for multiple collisions in diferents frames
			if (this->invecibleTime >= this->MaxinvencibleTime)
			{
				this->playerDamaged = false;
				this->invecibleTime = 0.f;
			}
			else
				this->invecibleTime += 0.1f;
		}

		//Cheking collision of the bullet with the enemies
		for (int j = 0; j < this->bullets.size() && !removed; j++)
		{
			if (this->bullets[j]->getBound().intersects(this->enemies[i]->getBounds()))
			{
				delete this->bullets[j];
				this->bullets.erase(this->bullets.begin() + j);

				this->enemies[i]->DamageEnemy();

				if (this->enemies[i]->getHp() <= 0)
				{
					this->points += this->enemies[i]->getPoints();
					this->pointCount = this->enemies[i]->getPoints();
					delete this->enemies[i];
					this->enemies.erase(this->enemies.begin() + i);
					removed = true;
				}
				
			}
		}

		//Removing the enemies when reach the bottom of the screen
		if (!removed)
		{

			if ( this->enemies[i]->getBounds().top > this->window->getSize().y)
			{
				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin() + i);
				removed = true;
			}
		}
	}
}

void Game3::renderEnemies()
{
	for (auto* enem : this->enemies)
	{
		enem->render(*this->window);
	}
}

void Game3::updateSpawnTimer()
{
	if (this->pointCount >= 50)
	{
		this->spawnTimerMax -= 0.4f;
		this->pointCount = 0;
	}
}

void Game3::updateCollision()
{
	if (this->player->getBounds().left < 0.f)
		this->player->setPosition(sf::Vector2f(0.f, this->player->getPosition().y));

	else if (this->player->getPosition().x + this->player->getBounds().width >
		this->window->getSize().x)
		this->player->setPosition(sf::Vector2f(
			this->window->getSize().x - this->player->getBounds().width,
			this->player->getPosition().y));

	if (this->player->getBounds().top < 0.f)
		this->player->setPosition(sf::Vector2f(this->player->getPosition().x, 0.f));

	else if (this->player->getPosition().y + this->player->getBounds().height >
		this->window->getSize().y)
		this->player->setPosition(sf::Vector2f(this->player->getPosition().x,
			this->window->getSize().y - this->player->getBounds().height));
}

void Game3::updateBullet()
{
	unsigned int counter = 0;
	for (auto* bullet : this->bullets)
	{
		bullet->update();

		if (bullet->getBound().top + 10 < 0.f)
		{
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
		}
		++counter;
	}
}

void Game3::renderBackGround()
{
	this->window->draw(this->worldBackground);
}

void Game3::update()
{ 
	this->pollEvents();

	if (!this->endgame)
	{
		this->player->update();
		this->updateCollision();
		this->InputMouse();
		this->updateBullet();
		this->updateEnemiesAndCombat();
		this->updateSpawnTimer();
	}
	this->updateGui();
}

 
void Game3::render()
{
	this->window->clear();
	this->renderBackGround(); 
	this->player->render(*this->window);
	this->renderEnemies();
	this->renderBullet(); 
	this->renderGui();
	this->window->display();
}

