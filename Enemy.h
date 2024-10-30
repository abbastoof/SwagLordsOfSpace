#ifndef ENEMY_H
#define ENEMY_H


#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Enemy
{
private:
	sf::CircleShape shape; //Shape of the enemy
	int hp; //Health points
	int hpMax; //Maximum health points
	int damage; //Damage
	int type; //Type of enemy
	int points; //Points given to the player when killed

	void initVariables(); //Initializes the variables
	void initShape(); //Initializes the shape

public:
	Enemy(float pos_x, float pos_y);
	virtual ~Enemy();

	//Functions
	void update(); //Updates the enemy
	void render(sf::RenderTarget* target); //Renders the enemy
};

#endif