#pragma once

//Game Library
#include"player.h"
#include"bullet.h"
#include"enemy.h"

//STD Library
#include<map>


class Game
{
private:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;
	std::string title;
	bool endGame;

	//System

	unsigned points;

	//GUI
	sf::Font font;
	sf::Text text;
	sf::Text gameoverText;

	//Player GUI
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	//World
	sf::Sprite worldBackground;
	sf::Texture worldBackgroundtex;

	//Player
	Player* player;

	//Enemies

	float spawnTimer;
	float spawnTimermax;
	std::vector<Enemy*> enemies;

	//Resource
	std::map<std::string, sf::Texture*> textures;
	std::vector<bullet*> bullets;

	//Initialization

	void initWindow();
	void initVariables();
	void initTextures();
	void initGui();
	void initWorld();
	void initPlayer();
	void initEnemies();
	

public:
	Game();
	virtual ~Game();

	//Accessors

	//Function
	void run();
	void pollEvents();
	bool isEndGame();

	//Update
	void update();
	void updateInput();
	void updateGui();
	void updateWorld();
	void updateCollision();
	void updateBullet();
	void updateEnemies();
	void updateCombat();

	//Render
	void render();
	void renderGui();
	void renderWorld();


};

