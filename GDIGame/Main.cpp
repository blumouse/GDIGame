#include "Game.h"
#include <iostream>


int main()
{
	Game* game = new Game;


	if (false == game->Initialize())
	{
		std::cout << "Failed to initialize the game. Error: " << GetLastError() << std::endl;
		delete game;
		return -1;
	}

	game->Run();

	game->Finalize();


	delete game;

	return 0;

}