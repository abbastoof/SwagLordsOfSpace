#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

class Player
{
private:
	sf::Sprite sprite;
	sf::Texture texture;

	float movementSpeed;
	
	float attackCooldown;
	float attackCooldownMax;

	//Private Functions
	void initVariables();
	void initTexture();
	void initSprite();

public:
	Player();
	virtual ~Player();

	//Accessors
	const sf::Vector2f& getPos() const; //Returns the position of the player.

	//Functions
	void move(const float dirx, const float diry);
	const bool canAttack();
	void updateAttack();
	void update();
	void render(sf::RenderTarget& target);
};

#endif