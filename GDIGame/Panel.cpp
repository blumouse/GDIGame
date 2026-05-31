#include "Panel.h"
#include "GameManager.h"

#include "PanelObject.h"
#include "PanelBitmap.h"


#pragma region Lifecycles

void Panel::Awake() {
    //PanelObject* panelObject = dynamic_cast<PanelObject*>(pGameObject);

    //if (panelObject)
    //    panelObject->SetLayer(3);
}

void Panel::Start() {
    PanelObject* panelObject = dynamic_cast<PanelObject*>(pGameObject);

    if (panelObject)
        panelBitmap = panelObject->GetPanelBitmap();

    panelBitmap->InitPanelInfo(isMine, surroundingMine);
}

void Panel::Update(float deltaTime) {

}

void Panel::FixedUpdate() {

}

void Panel::OnDestroy() {

}

#pragma endregion


#pragma region Clickable

void Panel::OnMouseEnter() {

    panelBitmap->SetClickState(Enter);
}

void Panel::OnMouseExit() {

    panelBitmap->SetClickState(Exit);
}


void Panel::OnLDown() {

    panelBitmap->SetClickState(LDown);
}

void Panel::OnLComplete() {

    panelBitmap->SetClickState(LComplete);

    if (isOpen)
    {
        ForceOpenLinkedPanel();
        return;
    }

    OpenPanel();
}

void Panel::OnLCancel() {

    panelBitmap->SetClickState(LCancel);
}


void Panel::OnRDown() {

    panelBitmap->SetClickState(RDown);
}

void Panel::OnRComplete() {

    panelBitmap->SetClickState(RComplete);

    SetMarkedPanel();
}

void Panel::OnRCancel() {

    panelBitmap->SetClickState(RCancel);
}

#pragma endregion


#pragma region OwnLogic

void Panel::InitPanel() {
	// 본인이 폭탄이면 노드 찾아가서 숫자 하나! 올려주기

	if (isMine)
	{
        if (pPanel_NW)
            pPanel_NW->surroundingMine++;

        if (pPanel_N)
            pPanel_N->surroundingMine++;

        if (pPanel_NE)
            pPanel_NE->surroundingMine++;


        if (pPanel_W)
            pPanel_W->surroundingMine++;

        if (pPanel_E)
            pPanel_E->surroundingMine++;


        if (pPanel_SW)
            pPanel_SW->surroundingMine++;

        if (pPanel_S)
            pPanel_S->surroundingMine++;

        if (pPanel_SE)
            pPanel_SE->surroundingMine++;
	}
}


void Panel::OpenPanel() {

    if (isOpen)
        return;

    if (isMarked)
        return;

    isOpen = true;


    panelBitmap->SetPanelInfo(isOpen, isMarked);


    if (isMine)
    {
        GameManager::GetInstance()->OnBoom(this);
        return;
    }


    GameManager::GetInstance()->OnPanelOpened();    // 이 안에서 개수로 클리어판정


    if (surroundingMine == 0)
        OpenLinkedPanel();
}

void Panel::OpenLinkedPanel() {

    if (pPanel_NW && !pPanel_NW->isMine)
        pPanel_NW->OpenPanel();

    if (pPanel_N && !pPanel_N->isMine)
        pPanel_N->OpenPanel();

    if (pPanel_NE && !pPanel_NE->isMine)
        pPanel_NE->OpenPanel();


    if (pPanel_W && !pPanel_W->isMine)
        pPanel_W->OpenPanel();

    if (pPanel_E && !pPanel_E->isMine)
        pPanel_E->OpenPanel();


    if (pPanel_SW && !pPanel_SW->isMine)
        pPanel_SW->OpenPanel();

    if (pPanel_S && !pPanel_S->isMine)
        pPanel_S->OpenPanel();

    if (pPanel_SE && !pPanel_SE->isMine)
        pPanel_SE->OpenPanel();
}

void Panel::SetMarkedPanel() {
    isMarked = !isMarked;
    panelBitmap->SetPanelInfo(isOpen, isMarked);
}

void Panel::ForceOpenLinkedPanel() {

    if (!isOpen)
        return;

    if (isMarked)
        return;

    if (surroundingMine == 0)
        return;

    int count = 0;

    if (pPanel_NW && pPanel_NW->isMarked)
        count++;

    if (pPanel_N && pPanel_N->isMarked)
        count++;

    if (pPanel_NE && pPanel_NE->isMarked)
        count++;


    if (pPanel_W && pPanel_W->isMarked)
        count++;

    if (pPanel_E && pPanel_E->isMarked)
        count++;


    if (pPanel_SW && pPanel_SW->isMarked)
        count++;

    if (pPanel_S && pPanel_S->isMarked)
        count++;

    if (pPanel_SE && pPanel_SE->isMarked)
        count++;


    if (count != surroundingMine)
        return;



    if (pPanel_NW && !pPanel_NW->isMarked)
        pPanel_NW->OpenPanel();

    if (pPanel_N && !pPanel_N->isMarked)
        pPanel_N->OpenPanel();

    if (pPanel_NE && !pPanel_NE->isMarked)
        pPanel_NE->OpenPanel();


    if (pPanel_W && !pPanel_W->isMarked)
        pPanel_W->OpenPanel();

    if (pPanel_E && !pPanel_E->isMarked)
        pPanel_E->OpenPanel();


    if (pPanel_SW && !pPanel_SW->isMarked)
        pPanel_SW->OpenPanel();

    if (pPanel_S && !pPanel_S->isMarked)
        pPanel_S->OpenPanel();

    if (pPanel_SE && !pPanel_SE->isMarked)
        pPanel_SE->OpenPanel();
}

#pragma endregion
