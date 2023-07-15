#pragma once

#include "PlayerGame4.h"

class Game4
{
private:
	sf::RenderWindow* window;
	sf::Event ev;

	PlayerGame4* Player;

	sf::Text UItext;
	sf::Font font;

	void initFont();
	void initText();
	void initPlayer();
	void initWindow();

public:
	Game4();
	~Game4();

	void updateCollisions();
	void updateGUI();
	void UpdatePlayer();
	void RenderPlayer();
	void pollEvents();
	void run();
	void renderGUI();
	void render();
	void update();
};