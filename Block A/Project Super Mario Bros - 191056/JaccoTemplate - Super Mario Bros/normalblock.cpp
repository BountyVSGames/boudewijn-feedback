#include "normalblock.h"

namespace Tmpl8
{
	void NormalBlock::Animation(float deltaTime)
	{

	}

	void NormalBlock::BlockInteraction()
	{

	}

	void NormalBlock::Draw(Surface* gameWindow)
	{
		GetScreenPos();
		graphic->Draw(gameWindow, (int)scrPosX, (int)scrPosY);
		//graphic->DrawScaled(scrPosX, scrPosY, graphic->GetWidth() * size, graphic->GetHeight() * size, gameWindow);
	}

	void NormalBlock::Update(float deltaTime)
	{

	}
}