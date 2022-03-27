#include "player.h"


void Player::initTexture()
{
	//Load texture from a file
	if (!this->texture.loadFromFile("Textures/ship.png"))
	{
		std::cout << " ERROR::PLAYER::INITTEXTURE:: couldn't load texture file" << "\n";
	}
}

void Player::initSprite()
{
	//Set the texture to the sprite
	this->sprite.setTexture(this->texture);
	
	//Resize the sprite

	this->sprite.scale(0.1f, 0.1f);
}

void Player::initVariables()
{
	this->movementSpeed = 5.f;
	this->attackCooldownmax = 10.f;
	this->attackCooldown = this->attackCooldownmax;

	this->hpMax = 100;
	this->hp = this->hpMax;

}



Player::Player()
{
	this->initTexture();
	this->initSprite();
	this->initVariables();

}


Player::~Player()
{

}

const sf::Vector2f& Player::getPos() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const int& Player::getHp() const
{
	return this->hp;
}

const int& Player::getHpMax() const
{
	return this->hpMax;
}

void Player::setPosition(const sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::setHp(const int hp)
{
	this->hp = hp;
}

void Player::loseHp(const int value)
{
	this->hp -= value;
	if (this->hp < 0)
		this->hp = 0;
}

void Player::update()
{
	this->updateAttack();
}

void Player::updateAttack()
{
	if (this->attackCooldownmax <= this->attackCooldownmax)
	{
		this->attackCooldown += 0.5f;
	}
}

const bool Player::canAttack()
{
	if (this->attackCooldown >= this->attackCooldownmax)
	{
		this->attackCooldown = 0.f;
		return true;
	}
	return false;
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}

void Player::move(const float dirX, const float dirY)
{
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}
