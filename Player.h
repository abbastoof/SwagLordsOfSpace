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

	int hp;
	int hpMax;

	//Private Functions
	void initVariables();
	void initTexture();
	void initSprite();

public:
	Player();
	virtual ~Player();

	//Accessors
	const sf::Vector2f& getPos() const; //Returns the position of the player.
	const sf::FloatRect getBounds() const; //Returns the bounds of the player.
	const int& getHp() const; //Returns the health points of the player.
	const int& getHpMax() const; //Returns the maximum health points of the player.


	//Modifiers
	void setPosition(const sf::Vector2f pos);
	void setPosition(const float x, const float y);
	void setHp(const int hp); //Sets the health points of the player.
	void loseHp(const int value); //Loses health points.

	//Functions
	void move(const float dirx, const float diry);
	const bool canAttack();
	void updateAttack();
	void update();
	void render(sf::RenderTarget& target);
};

#endif