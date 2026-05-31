#include "ClickableManager.h"
#include "Game.h"
#include "IClickable.h"

#include <iostream>

ClickableManager* ClickableManager::instance = nullptr;

ClickableManager* ClickableManager::GetInstance() { return ClickableManager::instance; }

#pragma region Lifecycles

void ClickableManager::Awake()
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
	if (!isActive)
	{
		if (curOver)
			curOver->OnMouseExit();
		return;
	}


	GameObjectBase* go = nullptr;
	if (!Game::GetInstance()->TryGetObjectWithPos(mouseX, mouseY, go))
	{
		if (curOver)
			curOver->OnMouseExit();
		return;
	}

	IClickable* hover = nullptr;
	if (!TryGetClickable(go, hover))
	{
		if (curOver)
			curOver->OnMouseExit();
		return;
	}


	if (curOver == hover)
	{
		// 절대 아무것도 안함
		return;
	}
	else /*(curOver != hover)*/
	{
		//if (interactingL)
		//	;

		//if (interactingR)
		//	;

		//if (isLDown)
		//	;

		//if (isRDown)
		//	;


		if (curOver)
			curOver->OnMouseExit();

		if (hover)
			hover->OnMouseEnter();

		curOver = hover;
	}
}

void ClickableManager::HandleLDown(int mouseX, int mouseY)
{
	if (!isActive)
		return;


	//if (isLDown) {}
	//	// ??

	//if (interactingL) {}
	//	// ??

	//if (isRDown) 
	//{
	//	// 우클릭 취소 시켜주는걸로 할까?
	//}

	if (curOver)
	{
		curOver->OnLDown();
		interactingL = curOver;
	}

	if (interactingR) {}


	isLDown = true;
}

void ClickableManager::HandleLUp(int mouseX, int mouseY)
{
	if (!isActive)
		return;


	//if (isRDown)
	//	;

	if (isLDown) 
	{
		if (interactingL)
		{
			if (interactingL == curOver)
			{
				interactingL->OnLComplete();
			}
			else	/*(interacting != curOver)*/
			{
				interactingL->OnLCancel();
			}
		}
	}
	else	// ??
	{

	}


	interactingL = nullptr;
	isLDown = false;
}

void ClickableManager::HandleRDown(int mouseX, int mouseY)
{
	if (!isActive)
		return;


	//if (isRDown) {}
	//// ??

	//if (interactingR) {}
	//// ??

	//if (isLDown)
	//{

	//}

	if (curOver)
	{
		curOver->OnRDown();
		interactingR = curOver;
	}

	if (interactingL) {}


	isRDown = true;
}

void ClickableManager::HandleRUp(int mouseX, int mouseY)
{
	if (!isActive)
		return;


	//if (isLDown)
	//	;

	if (isRDown)
	{
		if (interactingR)
		{
			if (interactingR == curOver)
			{
				interactingR->OnRComplete();
			}
			else	/*(interacting != curOver)*/
			{
				interactingR->OnRCancel();
			}
		}
	}
	else	// ??
	{

	}


	interactingR = nullptr;
	isRDown = false;
}


// Manager

IClickable* ClickableManager::GetClickable(GameObjectBase* pGameObject)
{
	IClickable* clickable = nullptr;
	Component** components = pGameObject->GetComponents();
	int size = pGameObject->GetComponentsSize();

	for (int i = 0; i < size; i++)
	{
		clickable = dynamic_cast<IClickable*>(components[i]);

		if (clickable)
			break;
	}

	return clickable;
}

bool ClickableManager::TryGetClickable(GameObjectBase* pGameObject, IClickable*& pClickable)
{
	IClickable* clickable = nullptr;
	Component** components = pGameObject->GetComponents();
	int size = pGameObject->GetComponentsSize();

	for (int i = 0; i < size; i++)
	{
		clickable = dynamic_cast<IClickable*>(components[i]);

		if (clickable)
		{
			pClickable = clickable;
			return true;
		}
	}
	
	return false;
}

#pragma endregion
