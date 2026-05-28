#include "PanelObject.h"
#include "Game.h"
#include "Panel.h"
#include "PanelBitmap.h"


PanelObject::PanelObject() 
{
	pPanel = new Panel(this);
	//pPanelBitmap = new PanelBitmap(this);

	ppComponents[componentsSize++] = pPanel;
	ppComponents[componentsSize++] = pPanelBitmap;
}


#pragma region Lifecycles

// 그대로

#pragma endregion



#pragma region IDrawable

void PanelObject::Draw(HDC hdc)
{
	// 비트맵갖다 그리기..
}

#pragma endregion


#pragma region Transform

// 딱히
//bool PanelObject::IsIntersectPoint(int x, int y) 
//{
//
//}

#pragma endregion
