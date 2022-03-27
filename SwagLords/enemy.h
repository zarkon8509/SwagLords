#pragma once

#include<iostream>
#include<SFML/Graphics.hpp> 

class Enemy
{
private:
	sf::Sprite shape;
	sf::Texture shapeTexture;
	int type;
	int hp;
	int hpMax;
	int damage;
	unsigned pointCount;
	unsigned points;
	float speed;


public:

	//Constructor and Deconstructor
	Enemy(float pos_x, float pos_y);
	virtual ~Enemy();

	//Inizialization
	void initVariables();
	void initShape();
	void initTexture();

	//Accessors
	const sf::FloatRect getBounds() const;
	const int& getPoints() const;
	const int& getDamage() const;

	//Function
	void update();
	void render(sf::RenderTarget* target);



	
};

