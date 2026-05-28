#include "ClickableManager.h"
#include "Game.h"


ClickableManager* ClickableManager::instance = nullptr;

ClickableManager* ClickableManager::GetInstance() { return ClickableManager::instance; }

#pragma region Lifecycles

void ClickableManager::Awake()
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
}

void ClickableManager::Start()
{

}

void ClickableManager::Update(float deltaTime)
{

}

void ClickableManager::FixedUpdate()
{

}

void ClickableManager::OnDestroy()
{

}

#pragma endregion


#pragma region OwnLogics

// Input Events

void ClickableManager::HandleMouseMove(int mouseX, int mouseY)
{

}

void ClickableManager::HandleLDown(int mouseX, int mouseY)
{

}
void ClickableManager::HandleLUp(int mouseX, int mouseY)
{

}

void ClickableManager::HandleRDown(int mouseX, int mouseY)
{

}
void ClickableManager::HandleRUp(int mouseX, int mouseY)
{

}


IClickable* ClickableManager::TryGetClickable(GameObjectBase* pGameObject)
{
	// TODO
	return nullptr;
}

#pragma endregion
