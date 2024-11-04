#include "Enemy.h"

void Enemy::initVariables()
{
    this->pointCount    = rand() % 8 + 3; //min = 3; max = 10
    this->type          = 0;
	this->hpMax			= static_cast<int>(this->pointCount); //min = 3; max = 10
	this->hp			= this->hpMax; //Health points of the enemy should be full
	this->damage		= this->pointCount; //Damage of the enemy should be equal to the number of points
	this->points		= this->pointCount; //Points given to the player when killed should be equal to the number of points
	this->speed			= static_cast<float>(this->pointCount / 2); //Speed of the enemy should be half of the number of points
}

void Enemy::initShape()
{
	this->shape.setRadius(this->pointCount * 5); //Radius of the enemy circle
	this->shape.setPointCount(this->pointCount); //Number of points of the enemy circle
    this->shape.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, 255));
}

Enemy::Enemy(float pos_x, float pos_y)
{
	this->initVariables();
	this->initShape();
	this->shape.setPosition(pos_x, pos_y);
}

Enemy::~Enemy()
{
}

const sf::FloatRect Enemy::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const int& Enemy::getPoints() const
{
	return this->points;
}


//Functions
void Enemy::update()
{
	this->shape.move(0.f, this->speed);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
