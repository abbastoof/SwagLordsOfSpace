#include "Game.h"

//Private Funtions
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Swaglords of Space Game", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	if (!this->textures["BULLET"]->loadFromFile("Textures/bullet.png"))
	{
		std::cout << "ERROR::GAME::INITTEXTURES::Could not load bullet texture." << std::endl;
	}
}

void Game::initGui()
{
	//Load font
	if (!this->font.loadFromFile("Fonts/PixellettersFull.ttf"))
		std::cout << "ERROR::GAME::Failed to load font" << std::endl;
	//Init point text
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(22);
	this->pointText.setFillColor(sf::Color::White);
	this->pointText.setString("Test");
}

void Game::initWorldBackground()
{
	if (!this->worldBackgroundTexture.loadFromFile("Textures/Background2.jpg"))
	{
		std::cout << "ERROR::GAME::INITWORLDBACKGROUND::Could not load world background texture." << std::endl;
	}
	this->worldBackground.setTexture(this->worldBackgroundTexture);
	//Fill the screen with the background
	this->worldBackground.setScale(0.2f, 0.2f);
}

void Game::initSystems()
{
	this->points = 0;
}

void Game::initPlayer()
{
	this->player = new Player();
}

void Game::initEnemies()
{
	this->spawnTimerMax = 50.f;
	this->spawnTimer = 0.f;
}

//Constructor
Game::Game()
{
	this->initWindow();
	this->initTextures();
	this->initGui();
	this->initWorldBackground();
	this->initSystems();
	this->initPlayer();
	this->initEnemies();
}

//Destructor
Game::~Game()
{
	delete this->window;
	delete this->player;

	//Delete textures
	for (auto& i : this->textures) {
		delete i.second;
	}

	//Delete bullets
	for (auto* i : this->bullets)
	{
		delete i;
	}
	//Delete enemies
	for (auto* i : this->enemies) {
		delete i;
	}
}

//Functions
void Game::run()
{
	while (this->window->isOpen())
	{
		this->update();
		this->render();
	}
}

void Game::updatePollEvents()
{
	sf::Event e;
	while (this->window->pollEvent(e)) {
		if (e.Event::type == sf::Event::Closed)
			this->window->close();
		if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
			this->window->close();
	}

}

void Game::updateInput()
{
	//Move Player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->player->move(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->player->move(1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->player->move(0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->player->move(0.f, 1.f);

	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack()) {
		sf::FloatRect playerBounds = this->player->getBounds();
		float bulletPosX = playerBounds.left + (playerBounds.width / 2); // Center the bullet on player's x-axis
		float bulletPosY = playerBounds.top; // Place it at the top of the player

		this->bullets.push_back(new Bullet(this->textures["BULLET"], bulletPosX, bulletPosY, 0.f, -1.f, 5.f));
	}

}

void Game::updateGUI()
{
	std::stringstream ss;
	ss << "Points: " << this->points;
	this->pointText.setString(ss.str());
}

void Game::updateWorldBackground()
{

}

void Game::updateCollision()
{
	// limit the player to the window size by checking the bounds of the player and the window size
	if (this->player->getBounds().left <= 0.f)
		this->player->setPosition(0.f, this->player->getBounds().top);
	else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x)
		this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);

	if (this->player->getBounds().top <= 0.f)
		this->player->setPosition(this->player->getBounds().left, 0.f);
	else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y)
		this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
}

void Game::updateBullets()
{
	unsigned counter = 0;
	for (auto* bullet : this->bullets)
	{
		bullet->update();

		//Bullet culling (top of screen)
		// if top of the bullet plus the height of the bullet(means the bottom of the bullet) is less than 0(which means the bullet is out of the screen) then delete the bullet
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			delete this->bullets.at(counter); //delete the current bullet from the vector of bullets
			this->bullets.erase(this->bullets.begin() + counter); //erase the bullet from the vector of bullets
			--counter; //because we deleted the bullet, we have to decrease the counter
		}
		++counter;
	}
}

void Game::updateEnemies()
{

	//Spawning enemies

	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->enemies.push_back(new Enemy(rand() % this->window->getSize().x - 20.f, -100.f));
		this->spawnTimer = 0.f; //reset the timer
	}
	
	//update
	unsigned counter = 0;
	for (auto* enemy : this->enemies)
	{
		enemy->update();

		//Bullet culling (top of screen)
		//if the top of the enemy is greater than the height of the window, then delete the enemy
		if (enemy->getBounds().top > this->window->getSize().y)
		{
			delete this->enemies.at(counter); //delete the current enemy from the vector of enemies
			this->enemies.erase(this->enemies.begin() + counter); //erase the enemy from the vector of enemies
			--counter; //because we deleted the enemy, we have to decrease the counter
		}
		++counter;
	}


}

void Game::updateCombat()
{
	for (int i = 0; i < this->enemies.size(); ++i) //for each enemy
	{
		bool enemy_deleted = false;
		for (size_t k = 0; k < this->bullets.size() && enemy_deleted == false; ++k) //for each bullet
		{
			if (this->enemies[i]->getBounds().intersects(this->bullets[k]->getBounds())) // if the enemy intersects with the bullet
			{
				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin() + i);

				delete this->bullets[k];
				this->bullets.erase(this->bullets.begin() + k);
				enemy_deleted = true;
			}
		}
	}

}

void Game::update()
{
	this->updatePollEvents();
	this->updateInput();
	this->player->update();
	this->updateCollision();
	this->updateBullets();
	this->updateEnemies();
	this->updateCombat();
	this->updateGUI();
	this->updateWorldBackground();
}

void Game::renderGUI()
{
	this->window->draw(this->pointText);
}

void Game::renderWorldBackground()
{
	this->window->draw(this->worldBackground);
}

void Game::render()
{
	//we have to clear all frame
	this->window->clear();

	//Draw world
	this->renderWorldBackground();

	//Draw all the stuffs
	this->player->render(*this->window);


	for (auto* bullet : this->bullets)
	{
		bullet->render(this->window);
	}
	
	for (auto* enemy : this->enemies)
	{
		enemy->render(this->window);
	}

	this->renderGUI();

	//this function called after OpenGL rendering has been done for the current frame, in orther to show it on screen
	this->window->display();

}
