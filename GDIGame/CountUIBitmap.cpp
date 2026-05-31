#include "CountUIBitmap.h"
#include "Game.h"


#pragma region Lifecycles

void CountUIBitmap::Awake() {

	SetCountUIBitmapInfo();
}

void CountUIBitmap::Start() {

}

void CountUIBitmap::Update(float deltaTime) {

}

void CountUIBitmap::FixedUpdate() {

}

void CountUIBitmap::OnDestroy() {

}

#pragma endregion


#pragma region OwnLogic

// -1은 Blank, -2는 Dash
void CountUIBitmap::InitCountUIInfo(int num) {

	SetCountUIInfo(num);
}

// -1은 Blank, -2는 Dash
void CountUIBitmap::SetCountUIInfo(int num)
{
	switch (num)
	{
	default:
	case -2:
		SetCount(Count_Dash);	break;

	case -1:
		SetCount(Count_Blank);	break;

	case 0:
		SetCount(Count_0);		break;

	case 1:
		SetCount(Count_1);		break;

	case 2:
		SetCount(Count_2);		break;

	case 3:
		SetCount(Count_3);		break;

	case 4:
		SetCount(Count_4);		break;

	case 5:
		SetCount(Count_5);		break;

	case 6:
		SetCount(Count_6);		break;

	case 7:
		SetCount(Count_7);		break;

	case 8:
		SetCount(Count_8);		break;

	case 9:
		SetCount(Count_9);		break;
	}
}


void CountUIBitmap::SetCount(CountState countState) {
	count = countState;
}

void CountUIBitmap::SetCountUIBitmapInfo()
{
	pCountUIBitmapInfo = Game::GetInstance()->GetBitmapResource(1);
}

#pragma endregion
