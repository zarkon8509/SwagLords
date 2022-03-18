#include "game.h"


//Initialization

void Game::initWindow()
{
	this->window = new sf::RenderWindow(videoMode, title, sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);

}

void Game::initVariables()
{
	this->window = nullptr;
	this->endGame = false;
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->title = "SwagLords";
}

void Game::initTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("Textures/bullet.png");
}

void Game::initPlayer()
{
	this->player = new Player();
}


//Constructor and Deconstructor

Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initTextures();
	this->initPlayer();

}

Game::~Game()
{
	delete this->window;
	delete this->player;

	//Delete textures
	for(auto& i:textures)
	{
		delete i.second;
	}

	//Delete bullets
	for (auto* i : this->bullets)
	{
		delete i;
	}
}


void Game::run()
{
	while (!this->isEndGame()&&this->window->isOpen())
	{
		this->update();

		this->render();
	}
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->event))
	{
		switch (this->event.type)
		{
		case sf::Event::KeyPressed:
			if (this->event.key.code == sf::Keyboard::Escape)
				this->window->close(); break;
		case sf::Event::Closed:
			this->window->close();
		default:
			break;
		}
	}

	
}

bool Game::isEndGame()
{
	return this->endGame;
}



void Game::update()
{
	this->pollEvents();
	this->updateInput();
	this->updateBullet();
	
}

void Game::updateInput()
{
	//Move player

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->player->move(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->player->move(1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->player->move(0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->player->move(0.f, 1.f);

	//Mouse clicked
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->bullets.push_back(new bullet(this->textures["BULLET"], this->player->getPos().x, this->player->getPos().y, 0.f, 0.f, 0.f));
	}
}

void Game::updateBullet()
{
	for (auto& bullet : this->bullets)
	{
		bullet->update();
	}
}

void Game::render()
{
	this->window->clear();

	this->player->render(*this->window);

	for (auto& bullet : this->bullets)
	{
		bullet->render(this->window);
	}
	
	this->window->display();
}
