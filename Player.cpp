#include "Player.h"


void Player::initVariables()
{
	this->movementSpeed = 2.f;
	this->attackCooldownMax = 10.f;
	this->attackCooldown = this->attackCooldownMax; // This means that the player can attack as soon as the game starts.
}

void Player::initTexture()
{
	//load a texture from file
	if (!this->texture.loadFromFile("Textures/spaceship.png")) // This returns a boolean value, true if the texture was loaded successfully, false otherwise
	{
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file." << std::endl;
	}
}

void Player::initSprite()
{
	//set the texture to the sprite, sprite is a class that inherits from drawable class and transformable class and it is used to draw images on the screen
	this->sprite.setTexture(this->texture);

	
	//Resize the sprite
	this->sprite.scale(0.2f, 0.2f);
}

//Constructor
Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
}

//Destructor

Player::~Player()
{
}

const sf::Vector2f& Player::getPos() const
{
	return this->sprite.getPosition(); // Returns the position of the player.
}

const sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}


//Functions

void Player::setPosition(const sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::move(const float dirX, const float dirY)
{

	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

const bool Player::canAttack()
{
	if (this->attackCooldown >= this->attackCooldownMax)
	{
		this->attackCooldown = 0.f;
		return true;
	}
	return false;
}

void Player::updateAttack()
{
	if (this->attackCooldown < this->attackCooldownMax)
		this->attackCooldown += 0.5f;
}

void Player::update()
{
	updateAttack();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
