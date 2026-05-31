#include "PanelObject.h"
#include "Game.h"
#include "Panel.h"
#include "PanelBitmap.h"
#include "RenderHelp.h"

PanelObject::PanelObject() 
{
	pPanel = new Panel(this);
	pPanelBitmap = new PanelBitmap(this);

	ppComponents[componentsSize++] = pPanel;
	ppComponents[componentsSize++] = pPanelBitmap;


    Game::GetInstance()->RegisterObject(this);
	Game::GetInstance()->RegisterDrawable(this, 3);
}


#pragma region Lifecycles

// 그대로

#pragma endregion



#pragma region IDrawable

void PanelObject::Draw(HDC hdc)
{
	// 임시로 콜라이더나 그리기?

    //HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
    //HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
    //HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));

    //Rectangle(hdc, pos.x - scale.x / 2.0f,
    //    pos.y - scale.y / 2.0f,
    //    pos.x + scale.x / 2.0f,
    //    pos.y + scale.y / 2.0f);

    //// 이전 객체 복원 및 펜 삭제
    //SelectObject(hdc, hOldPen);
    //SelectObject(hdc, hOldBrush);
    //DeleteObject(hPen);

	// 비트맵갖다 그리기..

    BitmapInfo* bmi = pPanelBitmap->GetPanelBitmapInfo();


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
    int srcY = pPanelBitmap->GetSpriteIndex() * PanelBitmap::PANEL_BITMAP_SLICE_HEIGHT;

    AlphaBlend(hdc, x, y, scale.x, scale.y,
        hBitmapDC, srcX, srcY, PanelBitmap::PANEL_BITMAP_SLICE_WIDTH, PanelBitmap::PANEL_BITMAP_SLICE_HEIGHT, blend);


    // 여기다가 애니메이션 색 섞기

    COLORREF overlayColor;

    switch (pPanelBitmap->GetAnimIndex())
    {
    default:
    case Idle:
        // 안해
        SelectObject(hBitmapDC, hOldBitmap);
        DeleteDC(hBitmapDC);

        return;

    case Highlighted:
        // 연한 색으로
        overlayColor = RGB(255, 255, 255);
        break;

    case Down:
        // 더 어두운 색으로
        overlayColor = RGB(160, 160, 160);
        break;
    }

    static struct AnimResource {
        HDC hDC = NULL;
        HBITMAP hBmp = NULL;
        HBITMAP hOldBmp = NULL;

        AnimResource() {
            HDC hScreenDC = GetDC(NULL);
            hDC = CreateCompatibleDC(hScreenDC);
            hBmp = CreateCompatibleBitmap(hScreenDC, 1, 1);
            hOldBmp = (HBITMAP)SelectObject(hDC, hBmp);
            ReleaseDC(NULL, hScreenDC);
        }

        ~AnimResource() {
            if (hDC) {
                SelectObject(hDC, hOldBmp);
                DeleteObject(hBmp);
                DeleteDC(hDC);
            }
        }
    } animResource;


    SetPixel(animResource.hDC, 0, 0, overlayColor);

    blend = { 0 };
    blend.BlendOp = AC_SRC_OVER;
    blend.SourceConstantAlpha = 128;
    blend.AlphaFormat = 0;

    AlphaBlend(hdc, x, y, scale.x, scale.y,
            animResource.hDC, 0, 0, 1, 1, blend);


    // 비트맵 핸들 복원
    SelectObject(hBitmapDC, hOldBitmap);
    DeleteDC(hBitmapDC);
}

int PanelObject::GetLayer() 
{
    return layer;
}

void PanelObject::SetLayer(int layer) 
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
