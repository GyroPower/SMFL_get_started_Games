#include "Game.h"


//Private functions
void Game::initializeVariables()
{
	this->window = nullptr;

	//Game logic
	this->points = 0;
	this->enemySpawnTimerMax = 50.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 7;
	this->mouse_is_pressed = false;
	this->health = 100;
	this->endgame = false;
	
}

void Game::initFonts()
{
	if (!this->font.loadFromFile("fonts/joystix.ttf"))
	{
		std::cout << "ERROR::GAME::INITFONTS::Failed to load font" << std::endl;
	}
}

void Game::initText()
{
	this->UItext.setFont(this->font);
	this->UItext.setCharacterSize(20);
	this->UItext.setFillColor(sf::Color::White);
	this->UItext.setString("Test");
}

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "A window", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

void Game::initEnemies(sf::Vector2f size, sf::Color color)
{
	
	this->enemy.setSize(size);
	
	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		0.f
	);
	this->enemy.setFillColor(color);
}

//Constructors
Game::Game()
{
	this->initializeVariables();
	this->initWindow();
	this->initFonts();
	this->initText();
}

Game::~Game()
{
	delete this->window;
}




//Accesors
const bool Game::getWindowsIsOpen() const 
{
	return this->window->isOpen();
}

//functions

void Game::spawnEnemies()
{
	/*
		@return void

		Spawns enemies and sets their colors and positions
		- Sets a random position
		- sets a random color
		- Adds enemy to the vector
	*/

	

	int type = rand() % 5;

	if (type == 0)
	{
		this->initEnemies(sf::Vector2f(30.f, 30.f), sf::Color::Magenta);	
	}
	else if (type == 1)
	{
		this->initEnemies(sf::Vector2f(50.f, 50.f), sf::Color::Blue);
	}
	else if (type == 2)
	{
		this->initEnemies(sf::Vector2f(60.f, 60.f), sf::Color::Cyan);
	}
	else if (type == 3)
	{
		this->initEnemies(sf::Vector2f(70.f, 70.f), sf::Color::Red);
	}
	else if (type == 4)
	{
		this->initEnemies(sf::Vector2f(80.f, 80.f), sf::Color::Yellow);
	}

	//Spawn enemy
	this->enemies.push_back(this->enemy); 
}

void Game::updateEnemies()
{
	
	//Updating the timer for enemy spawning
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			this->spawnEnemies();
			this->enemySpawnTimer = 0.f;
		}
		else
			this->enemySpawnTimer += 1.f;
	}

	

	for (int i = 0; i < this->enemies.size(); i++) {
			
		bool can_delete = true;

		//Move the enemies
		this->enemies[i].move(0.f, 4.f);

		//check if clicked upon

		if (!this->mouse_is_pressed && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->mouse_is_pressed = true;
			if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
			{
				this->enemies.erase(this->enemies.begin() + i);
				this->points += 1;
				can_delete = false;
			}


		}
		
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
			this->mouse_is_pressed = false;

		
		//Checking if goes outside of the limits
		if (can_delete && this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);
			this->health -= 10;
		}
		
	}
}

void Game::renderEnemies(sf::RenderTarget& target)
{
	for (auto& en : this->enemies) {
		target.draw(en);
	}
}

void Game::pollEvents()
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

void Game::update()
{
	this->pollEvents();

	if (!this->endgame)
	{
		this->updateMousePos();
		this->updateEnemies();
		

	}
	if (this->health <= 0)
		this->endgame = true;

	this->updateText();
}

void Game::render()
{
	/*
	@return void
	- clear old frames 
	- render objects
	- display frame in window
	Render the game objects
	*/
	this->window->clear();
	
	this->renderEnemies(*this->window);
	this->renderText(*this->window);
	//Draw the game
	this->window->display();
}

void Game::updateMousePos()
{
	/*
		@return void

		Updates the mouse position:
			- Mouse position relative to the window (vector2i) 	
	*/
	this->mousPosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousPosWindow);
}

void Game::renderText(sf::RenderTarget& target)
{
	target.draw(this->UItext);
}

void Game::updateText()
{
	std::stringstream ss;

	if (!this->endgame)
	{
		ss << "Points: " << this->points << "\n"
			<< "Health: " << this->health;
		this->UItext.setString(ss.str());
	}
	else {
		ss << "GAME OVER"<<"\n"
			<<"Points:"<<this->points;
		
		sf::Vector2f middle(static_cast<float>((this->window->getSize().x / 2) - 135),
			static_cast<float>(this->window->getSize().y / 2));
		
		this->UItext.setString(ss.str());
		this->UItext.setPosition(middle);
		this->UItext.setCharacterSize(40);
	}
}