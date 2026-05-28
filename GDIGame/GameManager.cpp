#include "GameManager.h"
#include "Game.h"

#include "PanelObject.h"


#pragma region Lifecycles

void GameManager::Awake()
{
	// ½Ì±ÛÅæ
	if (instance != nullptr && instance != this)
	{
		// ¿ÀºêÁ§Æ®±îÁö ÆÄ±«
		Game::GetInstance()->DestroyObject(pGameObject);
		return;
	}
	else /*if (instance == nullptr)*/
	{
		instance = this;
	}


	InitGame(ROW, COL, MINE_AMOUNT);

}

void GameManager::Start()
{

}

void GameManager::Update(float deltaTime)
{

}

void GameManager::FixedUpdate()
{

}

void GameManager::OnDestroy()
{

}

#pragma endregion


#pragma region OwnLogics

void GameManager::InitGame(int row, int col, int mineAmount)
{
	// Àá±ñ ¸ØÃçºÁ
	//InitPanels(row, col);

	//InitRandomMines(mineAmount);

	//InitPanelProps();
}

void GameManager::OnBoom(Panel* pBoomPanel)
{

}

void GameManager::OnPanelOpened()
{

}

void GameManager::GameOver()
{

}

void GameManager::FinalizeGame()
{

}


void GameManager::InitPanels(int row, int col)
{
	// À¯´ÏÆ¼·Î Ä¡¸é.. Instantiate¸¦ ÇØ¼­ ¾²°Ú´Ü °ÍÀÌ´Ù
	ppPanels = new Panel* [row * col];

	PanelObject* pPanelObject;
	Panel* pPanel;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			pPanelObject = new PanelObject();
			pPanel = pPanelObject->GetPanel();

			ppPanels[i * col + j] = pPanel;
		}
	}
}

void GameManager::InitRandomMines(int mineAmount)
{

}

void GameManager::InitPanelProps()
{

}

#pragma endregion