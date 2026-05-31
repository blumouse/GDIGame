#include "CountUIObject.h"
#include "Game.h"

#include "RenderHelp.h"
#include "CountUI.h"
#include "CountUIBitmap.h"


CountUIObject::CountUIObject()
{
    pCountUI = new CountUI(this);
    pCountUIBitmap = new CountUIBitmap(this);

    ppComponents[componentsSize++] = pCountUI;
    ppComponents[componentsSize++] = pCountUIBitmap;


    Game::GetInstance()->RegisterObject(this);
    Game::GetInstance()->RegisterDrawable(this, 2);
}


#pragma region Lifecycles

// 그대로

#pragma endregion



#pragma region IDrawable

void CountUIObject::Draw(HDC hdc)
{
    BitmapInfo* bmi = pCountUIBitmap->GetCountUIBitmapInfo();


    if (bmi == nullptr) return;
    if (bmi->GetBitmapHandle() == nullptr) return;

    HDC hBitmapDC = CreateCompatibleDC(hdc);

    HBITMAP hOldBitmap = (HBITMAP)SelectObject(hBitmapDC, bmi->GetBitmapHandle());
    // BLENDFUNCTION 설정 (알파 채널 처리)
    BLENDFUNCTION blend = { 0 };
    blend.BlendOp = AC_SRC_OVER;
    blend.SourceConstantAlpha = 255;  // 원본 알파 채널 그대로 사용
    blend.AlphaFormat = AC_SRC_ALPHA;

    const int x = pos.x - scale.x / 2.0f;
    const int y = pos.y - scale.y / 2.0f;

    const int srcX = 0;
    int srcY = pCountUIBitmap->GetCurNumber() * CountUIBitmap::COUNTUI_BITMAP_SLICE_HEIGHT;

    AlphaBlend(hdc, x, y, scale.x, scale.y,
        hBitmapDC, srcX, srcY, CountUIBitmap::COUNTUI_BITMAP_SLICE_WIDTH, CountUIBitmap::COUNTUI_BITMAP_SLICE_HEIGHT, blend);


    // 비트맵 핸들 복원
    SelectObject(hBitmapDC, hOldBitmap);
    DeleteDC(hBitmapDC);
}

int CountUIObject::GetLayer()
{
    return layer;
}

void CountUIObject::SetLayer(int layer)
{
    if (layer < 0 || layer > MAX_LAYER_NUM)
        return;

    Game::GetInstance()->QuitDrawable(this);

    Game::GetInstance()->RegisterDrawable(this, layer);
    this->layer = layer;
}

#pragma endregion


#pragma region Transform

// 딱히
//bool PanelObject::IsIntersectPoint(int x, int y) 
//{
//
//}

#pragma endregion
