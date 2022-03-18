#pragma once
#include"player.h"
#include"bullet.h"
#include<map>


class Game
{
private:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;
	std::string title;
	bool endGame;

	//Player
	Player* player;

	//Resource
	std::map<std::string, sf::Texture*> textures;
	std::vector<bullet*> bullets;

	//Initialization

	void initWindow();
	void initVariables();
	void initTextures();
	void initPlayer();

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
	void updateBullet();

	//Render
	void render();


};

