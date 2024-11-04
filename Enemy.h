#ifndef ENEMY_H
#define ENEMY_H


#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Enemy
{
private:
	unsigned pointCount;
	sf::CircleShape shape; //Shape of the enemy
	int hp; //Health points
	int hpMax; //Maximum health points
	int damage; //Damage
	int type; //Type of enemy
	int points; //Points given to the player when killed
	float speed; //Speed of the enemy

	void initVariables(); //Initializes the variables
	void initShape(); //Initializes the shape

public:
	Enemy(float pos_x, float pos_y);
	virtual ~Enemy();

	//Accessors
	const sf::FloatRect getBounds() const; //Returns the bounds of the enemy
	const int& getPoints() const; //Returns the points given to the player when killed
	//Functions
	void update(); //Updates the enemy
	void render(sf::RenderTarget* target); //Renders the enemy
};

#endif