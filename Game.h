#pragma once
#include "Player.h"

class Game
{
private:
	sf::RenderWindow* window;

	//Private Functions
	void initWindow();
public:
	Game();
	virtual ~Game();

	//Functions
	void run();

	void update();
	void render();
};

