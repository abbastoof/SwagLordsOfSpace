#ifndef GAME_H
#define GAME_H

#include <map>
#include <string>
#include <sstream>
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

	//GUI
	sf::Font	font;
	sf::Text	pointText;
	

	//World
	sf::Texture worldBackgroundTexture;
	sf::Sprite worldBackground; //Sprite is a class that inherits from drawable, so it can be drawn to the window

	//Systems
	unsigned points;
	
	//Player
	Player* player;

	//Enemies
	float spawnTimer;
	float spawnTimerMax;
	std::vector<Enemy*> enemies;


	//Private Functions
	void initWindow();
	void initTextures();
	void initGui();
	void initWorldBackground();
	void initSystems();
	void initPlayer();
	void initEnemies();

public:
	Game();
	virtual ~Game();

	//Functions
	void run();


	void updatePollEvents();
	void updateInput(); //Keyboard input for player
	void updateGUI();
	void updateWorldBackground();
	void updateCollision();
	void updateBullets();
	void updateEnemies();
	void updateCombat();
	void update();
	void renderGUI();
	void renderWorldBackground();
	void render();
};

#endif