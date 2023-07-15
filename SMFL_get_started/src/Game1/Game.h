#pragma once
#include "../stdafx.h"
class Game
{
private:

	//Variables
	sf::RenderWindow* window;
	sf::Event ev;

	//Mouse pos
	sf::Vector2i mousPosWindow;
	sf::Vector2f mousePosView;

	//Resources
	sf::Font font;

	//Game logic
	unsigned int points;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouse_is_pressed;
	int health;
	bool endgame;	

	//Text
	sf::Text UItext;

	//Game objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;

	//Private functions
	void initializeVariables();
	void initWindow();
	void initEnemies(sf::Vector2f size, sf::Color color);
	void initFonts();
	void initText();

public:
	//Constructors and Deastructors
	Game();
	virtual ~Game();

	//accesors
	const bool getWindowsIsOpen() const;

	//Functions
	void spawnEnemies();
	void updateEnemies();
	void renderEnemies(sf::RenderTarget& target);
	void pollEvents();
	void update();
	void render();
	void updateMousePos();
	void renderText(sf::RenderTarget& target);
	void updateText();
};
