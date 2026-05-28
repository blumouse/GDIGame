#include "ClickableManagerObject.h"
#include "ClickableManager.h"


ClickableManagerObject::ClickableManagerObject()
{
	// 컴포넌트 만들어 넣기

	pClickableManager = new ClickableManager(this);

	ppComponents[componentsSize++] = pClickableManager;
}


#pragma region Lifecycles

// 그대로

#pragma endregion

