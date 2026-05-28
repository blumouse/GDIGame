#include "PanelObject.h"
#include "Game.h"
#include "Panel.h"
#include "PanelBitmap.h"

PanelObject::PanelObject() 
{
	pPanel = new Panel(this);
	pPanelBitmap = new PanelBitmap(this);

	ppComponents[componentsSize++] = pPanel;
	ppComponents[componentsSize++] = pPanelBitmap;


    Game::GetInstance()->RegisterObject(this);
}


#pragma region Lifecycles

// 그대로

#pragma endregion



#pragma region IDrawable

void PanelObject::Draw(HDC hdc)
{
	// 임시로 콜라이더나 그리기?

    HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));

    Rectangle(hdc, pos.x - scale.x / 2.0f,
        pos.y - scale.y / 2.0f,
        pos.x + scale.x / 2.0f,
        pos.y + scale.y / 2.0f);

    // 이전 객체 복원 및 펜 삭제
    SelectObject(hdc, hOldPen);
    SelectObject(hdc, hOldBrush);
    DeleteObject(hPen);

	// 비트맵갖다 그리기..
    //pPanelBitmap-> ...
}

#pragma endregion


#pragma region Transform

// 딱히
//bool PanelObject::IsIntersectPoint(int x, int y) 
//{
//
//}

#pragma endregion
