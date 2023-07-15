#include "Game4.h"

void Game4::initFont()
{
	if (!this->font.loadFromFile("fonts/joystix.ttf"))
	{
		std::cout << "ERROR::INITFONT::Could not init font" << "\n";
	}
}

void Game4::initText()
{
	this->UItext.setFont(this->font);
	this->UItext.setCharacterSize(20);
	this->UItext.setFillColor(sf::Color::White);
}

void Game4::initPlayer()
{
	this->Player = new PlayerGame4();
}

void Game4::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Game 3",
		sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

Game4::Game4()
{
	this->initWindow();
	this->initPlayer();
	this->initFont();
	this->initText();
}

Game4::~Game4()
{
	delete this->window;
	delete this->Player;
}

void Game4::run()
{
	while (this->window->isOpen())
	{
		this->update();
		this->render();
	}
}

void Game4::renderGUI()
{
	this->window->draw(this->UItext);
}

void Game4::updateCollisions()
{
	//Collision with the bottom of the screen
	if (this->Player->getPosition().y + this->Player->getGlobalBounds().height >= this->window->getSize().y)
	{
		this->Player->resetVelocity();
		this->Player->setPosition(this->Player->getPosition().x,
			this->window->getSize().y - this->Player->getGlobalBounds().height);
	}
}

void Game4::updateGUI()
{
	std::stringstream ss;

	sf::Vector2f vel = this->Player->getPosition();

	ss << "X: " << vel.x << "\n" << "Y: " << vel.y;
	this->UItext.setString(ss.str());
}

void Game4::UpdatePlayer()
{
	this->Player->update();

	
}

void Game4::RenderPlayer()
{
	this->Player->render(*this->window);
}

void Game4::pollEvents()
{
	
	while (this->window->pollEvent(this->ev))
	{
		if (this->ev.type == sf::Event::Closed)
		{
			this->window->close();
		}
		if (this->ev.type == sf::Event::KeyReleased &&
			(this->ev.key.code == sf::Keyboard::A ||
				this->ev.key.code == sf::Keyboard::D ||
				this->ev.key.code == sf::Keyboard::W ||
				this->ev.key.code == sf::Keyboard::S ))
			this->Player->resetAnimationTimer();
	}


}

void Game4::render()
{
	this->window->clear();
	this->RenderPlayer();
	this->renderGUI();
	this->window->display();
}

void Game4::update()
{
	this->pollEvents();
	this->UpdatePlayer();
	this->updateCollisions();
	this->updateGUI();
}
