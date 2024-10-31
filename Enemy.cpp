#include "Enemy.h"


void Enemy::initShape()
{
    this->shape.setRadius(rand() % 20 + 20); // Random size between 20 and 40
    this->shape.setPointCount(rand() % 20 + 3); // Random number of points between 3 and 102, points are the corners of the shape
    this->shape.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, 255));
}

void Enemy::initVariables()
{
    this->type = 0;
    this->hpMax = 10;
    this->hp = 0;
    this->damage = 1;
    this->points = 5;
	this->speed = static_cast<float>(rand() % 2 + 1);
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


//Functions
void Enemy::update()
{
	this->shape.move(0.f, this->speed);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
