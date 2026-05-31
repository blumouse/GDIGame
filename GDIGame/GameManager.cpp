#include "GameManager.h"
#include "Game.h"

#include "PanelObject.h"
#include "Panel.h"
#include "ClickableManager.h"

#include <cstdlib>
#include <random>

#include <iostream>


GameManager* GameManager::instance = nullptr;

GameManager* GameManager::GetInstance() { return GameManager::instance; }

#pragma region Lifecycles

void GameManager::Awake()
{
	// 싱글톤
	if (instance != nullptr && instance != this)
	{
		// 오브젝트까지 파괴
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
	if (row < 2 || col < 2)			// 너무 적잖아
		return;

	InitPanels(row, col);

	InitRandomMines(row, col, mineAmount);

	InitPanelProps(row, col);
}

void GameManager::OnBoom(Panel* pBoomPanel)
{
	GameOver(false);
}

void GameManager::OnPanelOpened()
{
	openedPanel++;

	if (ROW * COL - MINE_AMOUNT == openedPanel)
		GameOver(true);
}

void GameManager::GameOver(bool isSueccess)
{
	// 대강
	ClickableManager::GetInstance()->isActive = false;

	if (isSueccess)		// 클리어
	{
		std::cout << "와 다찾았다" << std::endl;
	}
	else
	{
		std::cout << "KABOOM" << std::endl;
	}
}

void GameManager::FinalizeGame()
{
	// 차피 오브젝트 지워지면 알아서 다 지워지는데?
	// 라고 하기엔 재시작한다던가도 있지 핫하
}


void GameManager::InitPanels(int row, int col)
{
	// width == col
	// height == row ???? 어흑흑

	// 유니티로 치면.. Instantiate를 해서 쓰겠단 것이다
	ppPanels = new Panel* [row * col];

	PanelObject* pPanelObject;
	Panel* pPanel;

	Vector2 wholeScale = Vector2(panelScale.x * col, panelScale.y * row);

	// 20x20 기준 살짝 보정된..
	Vector2 panelPosMargin 
		= Vector2(((float)Game::GetInstance()->GetWidth() - wholeScale.x) / 2.0f, ((float)Game::GetInstance()->GetHeight() - wholeScale.y) / 2.0f + 25.0f);

	Vector2 rectPos;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			pPanelObject = new PanelObject();

			pPanelObject->scale = panelScale;

			rectPos = Vector2(panelScale.x * j, panelScale.y * i);
			pPanelObject->pos = panelPosMargin + panelScale / 2.0f + rectPos;


			pPanel = pPanelObject->GetPanel();

			ppPanels[i * col + j] = pPanel;
		}
	}


	// 노드 엮어주기
	// 모서리 / 꼭짓점일때 특수처리해주면 된다
	for (int i = 0; i < row * col; i++)
	{
		if (i < col)
		{
			if (i % col == 0)				// 좌상단
			{
				ppPanels[i]->pPanel_E = ppPanels[i + 1];
				ppPanels[i]->pPanel_S = ppPanels[i + col];
				ppPanels[i]->pPanel_SE = ppPanels[i + col + 1];
			}
			else if (i % col == col - 1)	// 우상단
			{
				ppPanels[i]->pPanel_W = ppPanels[i - 1];
				ppPanels[i]->pPanel_S = ppPanels[i + col];
				ppPanels[i]->pPanel_SW = ppPanels[i + col - 1];
			}
			else							// 위쪽 모서리						
			{
				ppPanels[i]->pPanel_E = ppPanels[i + 1];
				ppPanels[i]->pPanel_SE = ppPanels[i + col + 1];
				ppPanels[i]->pPanel_S = ppPanels[i + col];
				ppPanels[i]->pPanel_SW = ppPanels[i + col - 1];
				ppPanels[i]->pPanel_W = ppPanels[i - 1];
			}
		}
		else if (i >= (row - 1) * col)
		{
			if (i % col == 0)				// 좌하단
			{
				ppPanels[i]->pPanel_E = ppPanels[i + 1];
				ppPanels[i]->pPanel_N = ppPanels[i - col];
				ppPanels[i]->pPanel_NE = ppPanels[i - col + 1];
			}
			else if (i % col == col - 1)	// 우하단
			{
				ppPanels[i]->pPanel_W = ppPanels[i - 1];
				ppPanels[i]->pPanel_N = ppPanels[i - col];
				ppPanels[i]->pPanel_NW = ppPanels[i - col - 1];
			}
			else 							// 아래쪽 모서리
			{
				ppPanels[i]->pPanel_E = ppPanels[i + 1];
				ppPanels[i]->pPanel_NE = ppPanels[i - col + 1];
				ppPanels[i]->pPanel_N = ppPanels[i - col];
				ppPanels[i]->pPanel_NW = ppPanels[i - col - 1];
				ppPanels[i]->pPanel_W = ppPanels[i - 1];
			}
		}
		else
		{
			if (i % col == 0)				// 왼쪽 모서리
			{
				ppPanels[i]->pPanel_N = ppPanels[i - col];
				ppPanels[i]->pPanel_NE = ppPanels[i - col + 1];
				ppPanels[i]->pPanel_E = ppPanels[i + 1];
				ppPanels[i]->pPanel_SE = ppPanels[i + col + 1];
				ppPanels[i]->pPanel_S = ppPanels[i + col];
			}
			else if (i % col == col - 1)	// 오른쪽 모서리 
			{
				ppPanels[i]->pPanel_N = ppPanels[i - col];
				ppPanels[i]->pPanel_NW = ppPanels[i - col - 1];
				ppPanels[i]->pPanel_W = ppPanels[i - 1];
				ppPanels[i]->pPanel_SW = ppPanels[i + col - 1];
				ppPanels[i]->pPanel_S = ppPanels[i + col];
			}
			else							// 그냥 안쪽
			{
				ppPanels[i]->pPanel_N = ppPanels[i - col];
				ppPanels[i]->pPanel_NW = ppPanels[i - col - 1];
				ppPanels[i]->pPanel_W = ppPanels[i - 1];
				ppPanels[i]->pPanel_SW = ppPanels[i + col - 1];
				ppPanels[i]->pPanel_S = ppPanels[i + col];

				ppPanels[i]->pPanel_N = ppPanels[i - col];
				ppPanels[i]->pPanel_NE = ppPanels[i - col + 1];
				ppPanels[i]->pPanel_E = ppPanels[i + 1];
				ppPanels[i]->pPanel_SE = ppPanels[i + col + 1];
			}
		}
	}
}

void GameManager::InitRandomMines(int row, int col, int mineAmount)
{
	std::random_device rd;
	unsigned long long seed = rd();
	std::mt19937 gen(seed);
	std::uniform_int_distribution<int> dist(0, row * col - 1);

	int rand = 0;

	for (int i = 0; i < mineAmount; i++)
	{
		do
		{
			rand = dist(gen);
		} while (ppPanels[rand]->isMine);

		ppPanels[rand]->isMine = true;
	}
}

void GameManager::InitPanelProps(int row, int col)
{
	// 은 넘겨주자
	for (int i = 0; i < row * col; i++)
		ppPanels[i]->InitPanel();

}

#pragma endregion