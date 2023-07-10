#pragma once
#include "Player.h"
#include "swagball.h"
#include <sstream>
class Game2
{
private:
	//Window for render and update
	sf::RenderWindow* window;
	//Event handler
	sf::Event ev;

	//font
	sf::Text UItext;
	sf::Font font;
	
	//Player
	Player player;

	//Balls
	std::vector<Swagball> swagballs;
	int balls_cant;

	//Game logic
	float spawnTimer;
	float maxSpawnTime;
	int point;
	bool engame;

	//player interaction
	bool player_interacted;
	float interact_timer;
	float maxInteractTimer;

	void initWindow();
	void initializeVariables();
	void initFont();
	void initText();
	void SpawnBalls(sf::RenderTarget& target);
	const int randBallType();
public:
	Game2();
	virtual ~Game2();

	const bool getWindowsIsOpen() const;
	void pollEvents();
	void update();
	void render();

	void updateSwagballs(sf::RenderTarget& target);
	void renderSwagballs(sf::RenderTarget& target);
	void updateCollision();

	void updateGui();
	void RenderGui(sf::RenderTarget& target);

};