#include "PanelBitmap.h"
#include "Game.h"

#include <iostream>


#pragma region Lifecycles

void PanelBitmap::Awake() {

	SetSprite(Covered);
	SetAnim(Idle);

	SetPanelBitmapInfo();
}

void PanelBitmap::Start() {

}

void PanelBitmap::Update(float deltaTime) {

	//std::cout << (int)sprite << std::endl;
}

void PanelBitmap::FixedUpdate() {

}

void PanelBitmap::OnDestroy() {

}

#pragma endregion


#pragma region OwnLogic

void PanelBitmap::InitPanelInfo(bool isMine, int surroundingMine) {

	this->isMine = isMine;
	this->surroundingMine = surroundingMine;
}


void PanelBitmap::SetClickState(ClickState clickState) {

	if (isOpen)
		return;

	if (isMarked)
	{
		// L클릭 계열은 안먹는다 특수처리
		if (clickState == LDown || clickState == LComplete || clickState == LCancel)
			return;
	}


	// 애니메이션 자체는 좌클/우클 구분 없을것같군
	if (prevState == LDown)
	{
		// 나우 인터랙팅.. 호버보다 클릭상태가 우선이다 Down 상태 보존
		if (clickState == Enter || clickState == Exit)
			return;

		// 사실 이것도 지금 선에서 구분 없을거같은데!
		if (clickState == LComplete)
		{
			SetAnim(Idle);
		}
		else if (clickState == LCancel)
		{
			SetAnim(Idle);
		}
	}

	else if (prevState == RDown)
	{
		if (clickState == Enter || clickState == Exit)
			return;

		if (clickState == RComplete)
		{
			SetAnim(Idle);
		}
		else if (clickState == RCancel)
		{
			SetAnim(Idle);
		}
	}

	else	/*(Enter .. RCancel)*/
	{
		// 호버 애니메이션
		if (clickState == Enter)
		{
			SetAnim(Highlighted);
		}
		else if (clickState == Exit)
		{
			SetAnim(Idle);
		}
		else if (clickState == LDown)
		{
			SetAnim(Down);
		}
		else if (clickState == RDown) 
		{
			SetAnim(Down);
		}
	}


	// 비교처리 후...
	prevState = clickState;
}

void PanelBitmap::SetPanelInfo(bool isOpen, bool isMarked) {

	this->isOpen = isOpen;
	this->isMarked = isMarked;

	if (!isOpen)
	{
		if (!isMarked)
		{
			SetSprite(Covered);
		}
		else	/*(isMarked)*/
		{
			SetSprite(Marked);
		}
	}
	else	/*(isOpen)*/
	{
		if (isMine)
		{
			SetSprite(Opened_Mine);
		}
		else
		{
			switch (surroundingMine)
			{
			case 0:
				SetSprite(Opened_Blank);	break;

			case 1:
				SetSprite(Opened_1);		break;

			case 2:
				SetSprite(Opened_2);		break;

			case 3:
				SetSprite(Opened_3);		break;

			case 4:
				SetSprite(Opened_4);		break;

			case 5:
				SetSprite(Opened_5);		break;

			case 6:
				SetSprite(Opened_6);		break;

			case 7:
				SetSprite(Opened_7);		break;

			case 8:
				SetSprite(Opened_8);		break;

			default:
				break;
			}
		}
	}
}


void PanelBitmap::SetAnim(AnimState animState) {
	anim = animState;
}

void PanelBitmap::SetSprite(SpriteState spriteState) {
	sprite = spriteState;
}


void PanelBitmap::SetPanelBitmapInfo()
{
	pPanelBitmapInfo = Game::GetInstance()->GetBitmapResource(0);
}

#pragma endregion
