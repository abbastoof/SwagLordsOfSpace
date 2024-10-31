#ifndef GAME_H
#define GAME_H

#include <map>

#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

class Game
{
private:
	
	//Window
	sf::RenderWindow* window;

	//Resources
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;

	//Player
	Player* player;

	//Enemies
	float spawnTimer;
	float spawnTimerMax;
	std::vector<Enemy*> enemies;

	//Private Functions
	void initWindow();
	void initTextures();
	
	void initPlayer();
	void initEnemies();

public:
	Game();
	virtual ~Game();

	//Functions
	void run();


	void updatePollEvents();
	void updateInput(); //Keyboard input for player
	void updateBullets();
	void updateEnemies();
	void update();
	void render();
};

#endif