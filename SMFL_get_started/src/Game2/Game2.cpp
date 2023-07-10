#include "Game2.h"

void Game2::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600),
		"A window", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}


void Game2::initializeVariables()
{
	this->engame = false;
	this->balls_cant = 10;
	this->spawnTimer = 0;
	this->maxSpawnTime = 10.f;
	this->point = 0;
}

void Game2::initFont()
{
	if (!this->font.loadFromFile("fonts/joystix.ttf"))
	{
		std::cout << "ERROR::GAME::INITFONTS::Failed to load font" << std::endl;
	}
}

const int Game2::randBallType()
{
	int type = SwagBallTypes::DEFAULT;
	int randValue = rand() % 100 + 1;

	if (randValue > 60 && randValue <= 80)
		type = SwagBallTypes::DAMAGING;
	
	else if (randValue > 80 && randValue <= 100)
		type = SwagBallTypes::HEALING;
	

	return type;
	
}

void Game2::SpawnBalls(sf::RenderTarget& target)
{
	
	Swagball swagball(target,this->randBallType());
	this->swagballs.push_back(swagball);
	
}

void Game2::initText()
{
	this->UItext.setFont(this->font);
	this->UItext.setCharacterSize(20);
	this->UItext.setFillColor(sf::Color::White);
	this->UItext.setString("Test");
}

Game2::Game2()
{
	this->initializeVariables();
	this->initWindow();
	this->initFont();
	this->initText();
}

Game2::~Game2()
{
	delete this->window;
}

const bool Game2::getWindowsIsOpen() const
{
	return this->window->isOpen();
}

void Game2::pollEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		
		if (this->ev.type == sf::Event::Closed)

			this->window->close();

		if (this->ev.type == sf::Event::KeyPressed) {
			if (this->ev.key.code == sf::Keyboard::Escape)

				this->window->close();

		}
		
	}
}

void Game2::updateGui()
{
	std::stringstream ss;


	ss << "Points: " << this->point
		<<"\n"<<"Health: " << this->player.getHp()
		<<"/"<<this->player.getMaxHp();
	
	this->UItext.setString(ss.str());



}

void Game2::RenderGui(sf::RenderTarget& target)
{
	target.draw(this->UItext);
}

void Game2::update()
{
	this->pollEvents();
	this->player.UpdatePlayer(*this->window);
	this->updateGui();
	this->updateSwagballs(*this->window);;
	this->updateCollision();
}

void Game2::updateCollision()
{
	for (int i = 0; i < this->swagballs.size(); i++)
	{
		if (this->player.getShape().getGlobalBounds().intersects(this->swagballs[i].getshape().getGlobalBounds()))
		{

			switch (this->swagballs[i].getType())
			{
			case DAMAGING:
				this->swagballs.erase(this->swagballs.begin() + i);
				this->player.takeDamage(1);
				this->player.setColor(sf::Color::Red);
				break;

			case HEALING:
				this->swagballs.erase(this->swagballs.begin() + i);
				this->player.gainhealth(1);
				this->player.setColor(sf::Color::Yellow);
				break;

			case DEFAULT:
				this->swagballs.erase(this->swagballs.begin() + i);
				this->point += 1;

			}

		}

	}

}

void Game2::updateSwagballs(sf::RenderTarget& target)
{

	if (this->swagballs.size()<this->balls_cant)
	{
		if (this->spawnTimer >= this->maxSpawnTime)
		{
			this->SpawnBalls(target);
			this->spawnTimer = 0.f;
		}
		else
			this->spawnTimer += 0.3f;
	}

	for (int i = 0; i < this->swagballs.size(); i++)
	{
		swagballs[i].update(target);
	}
	
}

void Game2::renderSwagballs(sf::RenderTarget& target)
{
	for (auto& swagball : this->swagballs)
	{
		swagball.render(target);
	}
}

void Game2::render()
{
	this->window->clear();

	
	this->player.renderPlayer(*this->window);
	this->renderSwagballs(*this->window);
	this->RenderGui(*this->window);
	
	this->window->display();
}