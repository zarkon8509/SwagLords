#pragma once

//STD Library
#include<iostream>
#include<ctime>
#include<sstream>

//SFML

#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>

class Player
{
private:
	sf::Sprite sprite;
	sf::Texture texture;
	float movementSpeed; 

	//Private function

	void initTexture();
	void initSprite();
public:

	//Constructor and Destructor

	Player();
	~Player();

	//Accessors
	const sf::Vector2f& getPos() const;

	//Function

	void update();
	void render(sf::RenderTarget& target);
	void move(const float dirX, const float dirY);

};

