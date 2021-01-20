#include "mushroompowerup.h"
#include "precomp.h"

namespace Tmpl8
{
	void MushroomPowerup::Animation(float deltaTime)
	{

	}
	void MushroomPowerup::Update(float deltaTime)
	{
		if (vSpeed < 10 || !collide) vSpeed += currentGame->GetGlobalGravity();

		Collision();

		pos.x += hSpeed;
		pos.y += vSpeed;
	}
	void MushroomPowerup::Collision()
	{
		//Collision Down
		if (((currentGame->GetScreenPosY() / 32) + (scrPosY / 32) + 1) < 19)
		{
			int value = currentGame->grid[(int)((currentGame->GetScreenPosY() / 32) + (scrPosY / 32)) + 1][(int)((currentGame->GetScreenPosX() / 32) + (scrPosX / 32))];
			float xValue = (currentGame->GetScreenPosX() / 32) + (scrPosX / 32);
			xValue -= (int)xValue;

			if (xValue > .5f)
			{
				value = currentGame->grid[(int)((currentGame->GetScreenPosY() / 32) + (scrPosY / 32)) + 1][(int)((currentGame->GetScreenPosX() / 32) + (scrPosX / 32)) + 1];
			}

			if (value < 52 && currentGame->GetStructers()[value] == SOLID)
			{
				vSpeed = 0;

				if (!collide)
				{
					collide = true;
				}
			}
			else
			{
				collide = false;
			}
		}

		//Collision Right
		if ((((currentGame->GetScreenPosX() / 32) + (scrPosY / 32)) + 1) < 209)
		{
			int value = currentGame->grid[(int)((currentGame->GetScreenPosY() / 32) + (scrPosY / 32))][(int)((currentGame->GetScreenPosX() / 32) + (scrPosX / 32) + 1)];
			if (value < 52 && currentGame->GetStructers()[value] == SOLID)
			{
				hSpeed = -hSpeed;
			}
		}
		//Collision Left
		if ((((currentGame->GetScreenPosX() / 32) + (scrPosY / 32))) > 0)
		{
			int value = currentGame->grid[(int)((currentGame->GetScreenPosY() / 32) + (scrPosY / 32))][(int)((currentGame->GetScreenPosX() / 32) + (scrPosX / 32))];
			float xValue = (currentGame->GetScreenPosX() / 32) + (scrPosX / 32);
			xValue -= (int)xValue;

			if (xValue < .5f)
			{
				value = currentGame->grid[(int)((currentGame->GetScreenPosY() / 32) + (scrPosY / 32))][(int)((currentGame->GetScreenPosX() / 32) + (scrPosX / 32)) - 1];
			}

			if (value < 52 && currentGame->GetStructers()[value] == SOLID)
			{
				hSpeed = -hSpeed;
			}
		}
	}
	void MushroomPowerup::Draw(Surface* gameWindow)
	{
		GetScreenPos();
		graphic->Draw(gameWindow, (int)scrPosX, (int)scrPosY);
	}
}