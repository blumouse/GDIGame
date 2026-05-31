#include "CountUI.h"
#include "Game.h"
#include "GameManager.h"

#include "CountUIObject.h"
#include "CountUIBitmap.h"


#pragma region Lifecycles

void CountUI::Awake() {

}

void CountUI::Start() {
    CountUIObject* countUIObject = dynamic_cast<CountUIObject*>(pGameObject);

    if (countUIObject)
        countUIBitmap = countUIObject->GetCountUIBitmap();

    countUIBitmap->InitCountUIInfo(0);
}

void CountUI::Update(float deltaTime) {

}

void CountUI::FixedUpdate() {

}

void CountUI::OnDestroy() {

}

#pragma endregion


#pragma region OwnLogic

void CountUI::SetCount(int num) {
    countUIBitmap->InitCountUIInfo(num);
}

#pragma endregion
