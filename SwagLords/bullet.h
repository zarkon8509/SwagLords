#pragma once

#include<iostream>
#include<SFML/Graphics.hpp>

class bullet
{
private:
	sf::Sprite shape;
	sf::Vector2f direction;
	float movementSpeed;


public:
	bullet();
	bullet(sf::Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed);
	virtual ~bullet();

	//Accessors

	const sf::FloatRect getBounds() const;

	void update();
	void render(sf::RenderTarget* target);
};

