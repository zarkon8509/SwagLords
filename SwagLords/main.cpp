#include"game.h"
#include<ctime>

int main()

{
	std::srand(static_cast<unsigned>(time(NULL)));
	Game game;

	game.run();
	
	return 0;
}