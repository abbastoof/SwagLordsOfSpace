#include "Enemy.h"


void Enemy::initShape()
{
    this->shape.setRadius(rand() % 20 + 20); // Random size between 20 and 40
    this->shape.setPointCount(rand() % 20 + 3); // Random number of points between 3 and 102, points are the corners of the shape
}

void Enemy::initVariables()
{
    this->type = 0;
    this->hpMax = 10;
    this->hp = 0;
    this->damage = 1;
    this->points = 5;
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


//Functions
void Enemy::update()
{

}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
