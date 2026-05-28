#include "PanelObject.h"
#include "Game.h"
#include "Panel.h"


PanelObject::PanelObject() 
{
	pPanel = new Panel(this);
	//pPanelBitmap = new PanelBitmap(this);

	ppComponents[componentsSize++] = pPanel;
	ppComponents[componentsSize++] = pPanelBitmap;
}