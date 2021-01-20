#include "powerupblock.h"

namespace Tmpl8
{
	void PowerupBlock::Animation(float deltaTime)
	{
		if (animationUpdateTime > 0)
		{
			animationUpdateTime -= deltaTime;
			return;
		}

		graphic->SetFrame(graphic_currentFrame);

		if (graphic_currentFrame == 2)
		{
			graphic_currentFrame = 0;
			animationUpdateTime = 200;
			return;
		}

		graphic_currentFrame++;
		animationUpdateTime = 200;
	}

	void PowerupBlock::BlockInteraction()
	{

	}

	void PowerupBlock::Draw(Surface* gameWindow)
	{
		GetScreenPos();
		//graphic->DrawScaled(scrPosX, scrPosY, graphic->GetWidth() * size, graphic->GetHeight() * size, gameWindow);
		graphic->Draw(gameWindow, (int)scrPosX, (int)scrPosY);
	}

	void PowerupBlock::Update(float deltaTime)
	{
		Animation(deltaTime);
	}
}