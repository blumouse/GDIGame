#include "Panel.h"
#include "GameManager.h"

#include "PanelObject.h"


#pragma region Lifecycles

void Panel::Awake() {
    
}

void Panel::Start() {

}

void Panel::Update(float deltaTime) {

}

void Panel::FixedUpdate() {

}

void Panel::OnDestroy() {

}

#pragma endregion


// TODO: 내부로직 호출하면서.. 여기서 비트맵 상태도 바꿔주는게 낫나?
#pragma region Clickable

void Panel::OnMouseEnter() {

}

void Panel::OnMouseExit() {

}


void Panel::OnLDown() {

}

void Panel::OnLComplete() {

}

void Panel::OnLCancel() {

}


void Panel::OnRDown() {

}

void Panel::OnRComplete() {

}

void Panel::OnRCancel() {

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

    GameManager::GetInstance()->OnPanelOpened();    // 이 안에서 개수로 클리어판정

    if (isMine)
    {
        GameManager::GetInstance()->OnBoom(this);
        return;
    }

    if (surroundingMine == 0)
        OpenLinkedPanel();
    else            /*(!= 0)*/
    {
        // TODO: 열심히 검사.. 
        // 존재하는 주변 패널 모두 mine && marked || !mine 이면 forceopen
        //if (true)
        //{


        //    ForceOpenLinkedPanel();
        //}
    }
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
}

void Panel::ForceOpenLinkedPanel() {

    if (pPanel_NW && !pPanel_NW->isMine)
        pPanel_NW->ForceOpenPanel();

    if (pPanel_N && !pPanel_N->isMine)
        pPanel_N->ForceOpenPanel();

    if (pPanel_NE && !pPanel_NE->isMine)
        pPanel_NE->ForceOpenPanel();


    if (pPanel_W && !pPanel_W->isMine)
        pPanel_W->ForceOpenPanel();

    if (pPanel_E && !pPanel_E->isMine)
        pPanel_E->ForceOpenPanel();


    if (pPanel_SW && !pPanel_SW->isMine)
        pPanel_SW->ForceOpenPanel();

    if (pPanel_S && !pPanel_S->isMine)
        pPanel_S->ForceOpenPanel();

    if (pPanel_SE && !pPanel_SE->isMine)
        pPanel_SE->ForceOpenPanel();
}

void Panel::ForceOpenPanel() {

    if (isOpen)
        return;

    isOpen = true;

    GameManager::GetInstance()->OnPanelOpened();
}

#pragma endregion
