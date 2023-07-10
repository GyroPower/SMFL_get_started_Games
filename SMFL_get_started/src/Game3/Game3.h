#pragma once
#include "PlayerGame3.h"


class Game3
{

private:
	sf::RenderWindow* window;
	sf::Event ev;

	sf::Text UItext;
	sf::Font font;

	Player player;


	void initWindow();
	void initVariables();


public:

	Game3();
	~Game3();

	void pollEvents();
	void run();
	void update();
	void render();

};