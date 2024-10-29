#include "Player.h"


void Player::initTexture()
{
	//load a texture from file
}

void Player::initSprite()
{
	//set the texture to the sprite
	this->sprite.setTexture(this->texture);
}

//Constructor
Player::Player()
{
	this->initTexture();
	this->initSprite();
}

//Destructor

Player::~Player()
{
}


//Functions

void Player::update()
{

}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
