#include "GameManagerObject.h"
#include "Game.h"
#include "GameManager.h"

GameManagerObject::GameManagerObject() 
{
	// 컴포넌트 만들어 넣기

	pGameManager = new GameManager(this);

	ppComponents[componentsSize++] = pGameManager;


	// 맘에안든다..........
	Game::GetInstance()->RegisterObject(this);
}


#pragma region Lifecycles

// 그대로

#pragma endregion

