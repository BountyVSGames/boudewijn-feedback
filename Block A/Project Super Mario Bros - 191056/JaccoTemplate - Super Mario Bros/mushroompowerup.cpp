#include "mushroompowerup.h"
#include "precomp.h"

namespace Tmpl8
{
	void MushroomPowerup::Animation(float deltaTime)
	{

	}
	void MushroomPowerup::Update(float deltaTime)
	{
		// Ergens in de feedback van jouw Asteroids game heb ik drie verschillende physics variabelen besproken:
		// position
		// velocity
		// force.
		//
		// In je asteroids game is de force variabele minder relevant als hier. Want je hebt in deze game een heel erg uitgesproken
		// force: zwaartekracht.
		//
		// Zwaartekracht is een force. Een force is de verandering van je velocity en een velocity is de verandering van je position.
		// Je codeert hier impliciet krachten. Maar je kunt dit beter expliciet coderen. Elk (bewegend) object heeft een force in de vorm van
		// vec2(0, -currentGame->GetGlobalGravity()). Deze force blijft altijd onveranderd!
		//
		// Als je dit mooi hebt geimplementeerd kun je heel makkelijk krachten modeleren:
		// 
		// force = vec2(0, -currentGame->GetGlobalGravity());
		// velocity += force;
		// positon += velocity;
		if (vSpeed < 10 || !collide) vSpeed += currentGame->GetGlobalGravity();

		Collision();

		pos.x += hSpeed;
		pos.y += vSpeed;
	}
	void MushroomPowerup::Collision()
	{
		// Erg grote functie, probeer hem kleiner te maken. Misschien door hem op te splitsen, of misschien door hem slimmer te maken.

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