#pragma once
#include "../stdafx.h"
#include "PlayerGame3.h"
#include "Bullet.h"
#include <map>
#include "Enemy.h"


class Game3
{

private:
	//Window
	sf::RenderWindow* window;
	sf::Event ev;

	//Font
	sf::Text UItext;
	sf::Font font;

	//Player
	PlayerGame3* player;
	int points;
	int pointCount;
	bool playerDamaged;
	float invecibleTime;
	float MaxinvencibleTime;

	//enemy
	std::vector<Enemy*> enemies;
	float spawnTimer;
	float spawnTimerMax;

	//Resources
	std::map<std::string,sf::Texture*> textures;
	std::vector<Bullet*> bullets;

	//World
	sf::Texture worldBackTex;
	sf::Sprite  worldBackground;

	//logic variables
	bool canShoot;
	float shootTimer;
	float shootTimerMax;
	bool endgame;

	void initPlayer();
	void initEnemies();

	void initWorldBack();
	void initTextures();
	void initWindow();
	void initVariables();
	void initText();
	void initFont();


public:

	Game3();
	~Game3();

	void pollEvents();
	void run();
	void update();
	void render();

	void spawnEnemies();
	void updateEnemiesAndCombat();
	void renderEnemies();

	void updateCollision();

	void updateSpawnTimer();

	void renderBackGround();
	void updateBullet();
	void renderBullet();
	void InputMouse();
	void updateGui();
	void renderGui();
};