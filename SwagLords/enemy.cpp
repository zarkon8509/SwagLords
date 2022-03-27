#include "enemy.h"




//Constructor and Deconstructor

Enemy::Enemy(float pos_x, float pos_y)
{
	this->initVariables();
	this->initShape();
	this->initTexture();
	this->shape.setPosition(pos_x, pos_y);
}

Enemy::~Enemy()
{
	 
}


void Enemy::initVariables()
{
	this->pointCount =static_cast<unsigned> (rand() % 8 + 3); //min=3 max=10
	this->type		=0;
	this->hpMax		= static_cast<int>(this->pointCount);
	this->hp		= this->hpMax;
	this->damage	= static_cast<int>(this->pointCount);
	this->points	= static_cast<int>(this->pointCount);
	this->speed		= static_cast<float>(this->pointCount)/2;
}

void Enemy::initShape()
{

	/*this->shape.setRadius(static_cast<float>(this->pointCount) * 5);
	this->shape.setPointCount(static_cast<size_t>(this->pointCount));
	this->shape.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, 255));*/
	if (!this->shapeTexture.loadFromFile("Textures/asteroid.png"))
		std::cout << "\n GAME::ENEMY::INITSHAPE::SHAPETEXTURELOAD ERROR";

}

void Enemy::initTexture()
{
	this->shape.setTexture(this->shapeTexture);

	this->shape.setScale(sf::Vector2f(this->pointCount*0.1f, 
									  this->pointCount*0.1f));
}

const sf::FloatRect Enemy::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const int& Enemy::getPoints() const
{
	return this->points;
}

const int& Enemy::getDamage() const
{
	return this->damage;
}

void Enemy::update()
{
	this->shape.move(0.f, this->speed);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
