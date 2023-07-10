#include "Game3.h"


void Game3::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Game 3",
		sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(true);

}

void Game3::initVariables()
{

}

Game3::Game3()
{
	this->initWindow();
}

Game3::~Game3()
{
	delete this->window;
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

void Game3::update()
{
	this->pollEvents();
}

void Game3::render()
{
	this->window->clear();

	this->window->display();
}
