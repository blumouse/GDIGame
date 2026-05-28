#include "IDrawable.h"
#include "Game.h"

// 이게 필요하긴 한데.. 이러면 인터페이스가 아닌데요
IDrawable::IDrawable() 
{
	Game::GetInstance()->RegisterDrawable(this);
}