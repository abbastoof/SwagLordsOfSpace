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

void Game::initPlayer()
{
	this->player = new Player();
}

//Constructor
Game::Game()
{
	this->initWindow();
	this->initTextures();
	this->initPlayer();
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

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack()){
		this->bullets.push_back(new Bullet(this->textures["BULLET"], this->player->getPos().x, this->player->getPos().y, 0.f, -1.f, 5.f)); // 0.f, -1.f means the bullet will go up, 5.f is the speed of the bullet
	}
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

void Game::update()
{
	this->updatePollEvents();
	this->updateInput();
	this->player->update();
	this->updateBullets();
}

void Game::render()
{
	//we have to clear all frame
	this->window->clear();

	//Draw all the stuffs
	this->player->render(*this->window);


	for (auto* bullet : this->bullets)
	{
		bullet->render(*this->window);
	}

	//this function called after OpenGL rendering has been done for the current frame, in orther to show it on screen
	this->window->display();

}
