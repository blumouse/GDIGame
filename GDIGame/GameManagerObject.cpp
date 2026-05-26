#include "GameManagerObject.h"
#include "Game.h"
#include "GameManager.h"


GameManagerObject::GameManagerObject() 
{
	// 컴포넌트 만들어 넣기

	pGameManager = new GameManager();

	ppComponents[componentsSize++] = pGameManager;
}