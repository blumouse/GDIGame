#include "IDrawable.h"
#include "Game.h"

IDrawable::IDrawable() 
{
	Game::GetInstance()->RegisterDrawable(this);
}