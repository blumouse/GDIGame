#include "Game.h"
#include <iostream>


int main()
{
	if (false == Game::GetInstance()->Initialize())
	{
		std::cout << "Failed to initialize the game. Error: " << GetLastError() << std::endl;
		return -1;
	}

	Game::GetInstance()->Run();

	Game::GetInstance()->Finalize();


	Game::DestroyInstance();

	return 0;

}