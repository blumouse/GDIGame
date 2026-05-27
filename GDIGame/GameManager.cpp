#include "GameManager.h"
#include "Game.h"

#include "PanelObject.h"

// TODO: 헤더 인라인으로 걍 옮기기
#pragma region Framework

GameManager::GameManager(GameObjectBase* gameObject) : Component(gameObject) {
	// 없어!
}

GameManager::~GameManager() {}

#pragma endregion

GameManager* GameManager::GetInstance()
{
	return instance;
}


#pragma region Lifecycles

void GameManager::Awake()
{
	// 싱글톤
	if (instance != nullptr && instance != this)
	{
		// 오브젝트까지 파괴
		Game::GetInstance()->DestroyObject(pObject);
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
	InitPanels(row, col);

	InitRandomMines(mineAmount);

	InitPanelProps();
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
	// 유니티로 치면.. Instantiate를 해서 쓰겠단 것이다
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