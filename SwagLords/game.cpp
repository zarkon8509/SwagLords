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

	//System

	this->points = 0;

}

void Game::initTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("Textures/bullet.png");
}

void Game::initGui()
{
	//Load font
	if (!this->font.loadFromFile("Fonts/PixellettersFull.ttf"))
		std::cout << "\n ERROR::LOADING FONT";

	//Init point text
	this->text.setFont(this->font);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(30);
	this->text.setPosition(sf::Vector2f(20.f, 50.f));
	//this->text.setString("test");

	this->gameoverText.setFont(this->font);
	this->gameoverText.setFillColor(sf::Color::Red);
	this->gameoverText.setCharacterSize(60);
	this->gameoverText.setPosition(
		sf::Vector2f((this->window->getSize().x / 2.f) - (this->gameoverText.getGlobalBounds().width  / 2.f)
				   , (this->window->getSize().y / 2.f) - (this->gameoverText.getGlobalBounds().height / 2.f)));
	this->gameoverText.setString("Game Over!!");

	//Init GUI player
	this->playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
	this->playerHpBar.setFillColor(sf::Color::Red);
	this->playerHpBar.setPosition(20.f, 20.f);

	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));

}

void Game::initWorld()
{
	if(!this->worldBackgroundtex.loadFromFile("Textures/background1.jpg"))
		std::cout << "\n ERROR::LOADING TEXTURE";
	this->worldBackground.setTexture(this->worldBackgroundtex);
}

void Game::initPlayer()
{
	//Player
	this->player = new Player();

	
}

void Game::initEnemies()
{
	this->spawnTimermax = 50.f;
	this->spawnTimer = this->spawnTimermax;
}


//Constructor and Deconstructor

Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initGui();
	this->initTextures();
	this->initWorld();
	this->initPlayer();
	this->initEnemies();
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

	//Delete enemies
	for (auto* i : this->enemies)
	{
		delete i;
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


void Game::run()
{
	while (!this->isEndGame()&&this->window->isOpen())
	{
		this->pollEvents();

		if(this->player->getHp()>0)
			this->update();

		this->render();
	}
}


bool Game::isEndGame()
{
	return this->endGame;
}



void Game::update()
{
	this->updateWorld();
	this->updateGui();
	this->updateInput();
	this->player->update();
	this->updateCollision();
	this->updateBullet();	
	this->updateEnemies();
	this->updateCombat();
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
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)&&this->player->canAttack())
	{
		this->bullets.push_back(
			new bullet(this->textures["BULLET"], 
			this->player->getPos().x + this->player->getBounds().width / 2.f,
			this->player->getPos().y ,
			0.f,
			-1.f, 
			5.f));
	}
}

void Game::updateGui()
{
	std::stringstream ss;

	ss <<" Points: "<< this->points;

	this->text.setString(ss.str());

	//Update player GUI

	float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax() ;
	this->playerHpBar.setSize(sf::Vector2f(300.f * hpPercent, this->playerHpBar.getSize().y));

}

void Game::updateWorld()
{
}

void Game::updateCollision()
{
	//Left
	if (this->player->getBounds().left < 0.f)
	{
		this->player->setPosition(0.f, this->player->getBounds().top);
	}
	
	//Right
	else 
		if (this->player->getBounds().left + this->player->getBounds().width > this->window->getSize().x)
			{
				this->player->setPosition(this->window->getSize().x- this->player->getBounds().width, this->player->getBounds().top);
			}
	
	//Top
	if (this->player->getBounds().top < 0.f)
	{
		this->player->setPosition(this->player->getPos().x, 0.f);
	}
	
	//Bottom
	else
		if (this->player->getBounds().height + this->player->getPos().y > this->window->getSize().y)
			{
				this->player->setPosition(this->player->getPos().x, this->window->getSize().y - this->player->getBounds().height);
			}

}

void Game::updateBullet()
{
	unsigned counter=0;
	for (auto& bullet : this->bullets)
	{
		bullet->update();

		//Bullett culling (top screen), remove if exit from top screen
		if (bullet->getBounds().top + bullet->getBounds().height <= 0)
		{
			
			//Delete pointer to the single bullett out of screen
			delete this->bullets.at(counter);
			//Actually bullett delete
			this->bullets.erase(this->bullets.begin() + counter);
			//Bullett's vector decrease by one
			--counter;
			std::cout << this->bullets.size() << " \n";
		}
		++counter;
	}
}

void Game::updateEnemies()
{
	//Spawning
	this->spawnTimer += 1.f;
	if (this->spawnTimer > this->spawnTimermax)
	{
		this->enemies.push_back(new Enemy(rand() % this->window->getSize().x-20.f, -100.f));
		this->spawnTimer = 0;
	}

	//Updating
	unsigned counter = 0;
	for (auto& enemy : this->enemies)
	{
		enemy->update();
		bool enemy_deleted=false;
		//Bullett culling (top screen), remove if exit from top screen
		if ((enemy->getBounds().top > this->window->getSize().y)&&!enemy_deleted)
		{
			
			//Actually enemy delete
			this->enemies.erase(this->enemies.begin() + counter);
			//Enemy's vector decrease by one
			--counter;
			enemy_deleted = true;
			//Delete pointer to the single enemy out of screen
			//delete this->enemies.at(counter);
			//this->player
			std::cout << this->enemies.size() << " \n";
		}
		if (enemy->getBounds().intersects(this->player->getBounds()))
		{
			//Lose HP
			this->player->loseHp(enemy->getDamage());
			//Delete pointer to the single bullett out of screen
			delete enemy;
			//Actually bullett delete
			this->enemies.erase(this->enemies.begin() + counter);
			//Bullett's vector decrease by one
			//this->player
			enemy_deleted = true;
			std::cout << this->enemies.size() << " \n";
		}
		++counter;
	}
	

}

void Game::updateCombat()
{
	for (size_t i = 0; i < this->enemies.size(); ++i)
	{
		bool enemy_deleted = false;
		for (size_t k = 0; k < this->bullets.size() && enemy_deleted == false; k++)
		{
			if (this->enemies[i]->getBounds().intersects(this->bullets[k]->getBounds()) && !enemy_deleted)
			{
				this->points += this->enemies[i]->getPoints();

				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin() + i);

				delete this->bullets[k];
				this->bullets.erase(this->bullets.begin() + k);

				enemy_deleted = true;
				

			}
		
		}
	}
}

void Game::render()
{
	this->window->clear();

	this->renderWorld();

	this->renderGui();

	this->player->render(*this->window);

	for (auto& bullet : this->bullets)
	{
		bullet->render(this->window);
	}
	for (auto& enemy : this->enemies)
	{
		enemy->render(this->window);
	}
	

	
	this->window->display();
}

void Game::renderGui()
{
	this->window->draw(this->text);
	this->window->draw(this->playerHpBarBack);
	this->window->draw(this->playerHpBar);
	if (this->player->getHp() <= 0)
	{
		//this->window->clear();
		this->window->draw(this->gameoverText);
	}

}

void Game::renderWorld()
{
	this->window->draw(this->worldBackground);
}
