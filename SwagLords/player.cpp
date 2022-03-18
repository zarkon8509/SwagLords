#include "player.h"


void Player::initTexture()
{
	//Load texture from a file
	if (!this->texture.loadFromFile("Textures/ship.png"))
	{
		std::cout << " ERROR::PLAYER::INITTEXTURE:: couldn't load texture file" << "\n";
	}

	//Resize the sprite

	this->sprite.scale(0.1f, 0.1f);

}

void Player::initSprite()
{
	//Set the texture to the sprite
	this->sprite.setTexture(this->texture);
}

Player::Player()
{
	this->initTexture();
	this->initSprite();
	this->movementSpeed = 1.f;

}


Player::~Player()
{

}

const sf::Vector2f& Player::getPos() const
{
	return this->sprite.getPosition();
}

void Player::update()
{

}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}

void Player::move(const float dirX, const float dirY)
{
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}
