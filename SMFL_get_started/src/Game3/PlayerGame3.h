#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


class PlayerGame3
{
private:

	sf::Sprite sprite;
	sf::Texture texture;

	sf::Vector2f direction;
	sf::Vector2f position;

	//Privates functions
	void initTexture();
	void initSprite();

public:

	PlayerGame3();
	~PlayerGame3();

	void update();
	void render(sf::RenderTarget& target);
};