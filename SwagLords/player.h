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
	float attackCooldown;
	float attackCooldownmax;

	int hp;
	int hpMax;

	//Private function

	void initTexture();
	void initSprite();
	void initVariables();
	
public:

	//Constructor and Destructor

	Player();
	~Player();

	//Accessors
	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;
	const int& getHp() const;
	const int& getHpMax() const;

	//Modifiers
	void setPosition(const sf::Vector2f pos);
	void setPosition(const float x, const float y);
	void setHp(const int hp);
	void loseHp(const int value);

	//Functions

	void update();
	void updateAttack();
	const bool canAttack();
	void render(sf::RenderTarget& target);
	void move(const float dirX, const float dirY);

};

