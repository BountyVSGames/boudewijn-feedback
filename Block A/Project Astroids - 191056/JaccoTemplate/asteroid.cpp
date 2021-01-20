#include "precomp.h"
#include "asteroid.h"

namespace Tmpl8
{
	void Asteroid::Collision(Gameobject* object)
	{
		bool minX = pos.x + 20 < object->GetPos().x + 10;//(object->GetPos().x + 20) * object->GetSize();
		bool maxX = pos.x > object->GetPos().x - 10;//object->GetPos().x;
		bool minY = pos.y + 30 < object->GetPos().y + 2.5f;//(object->GetPos().y + 30) * object->GetSize();
		bool maxY = pos.y > object->GetPos().y;

		if ((minX && maxX) && (minY && maxY))
		{
			String fullObjectName = String(typeid(*object).name());
			fullObjectName.StringFromIndex(13);

			std::cout << fullObjectName.GetString() << std::endl;

			if (object != this && fullObjectName == "Player")
			{
				std::cout << "COLIDE";

				return;
			}
		}
	}

	void Asteroid::Update(float deltaTime)
	{
		/*if (game->GetKeyboardHandler()->isSpaceInputButtonDown)
		{
			Destroy();
		}*/

		Asteroid::Movement(deltaTime);
		Asteroid::Draw(game->GetSurface());
	}
	void Asteroid::Movement(float deltaTime)
	{
		if (pos.x > (SCRWIDTH + (10 * size)))
		{
			pos.x = 1 - (10 * size);
		}
		else if (pos.x < (0 - (10 * size)))
		{
			pos.x = SCRWIDTH - (10 * size);
		}

		if (pos.y > (SCRHEIGHT + (10 * size)))
		{
			pos.y = 1 - (10 * size);
		}
		else if (pos.y < (0 - (10 * size)))
		{
			pos.y = SCRHEIGHT - (10 * size);
		}

		CalculateRotation(angle, movement);

		pos += movement * speed;
	}
	void Asteroid::Draw(Surface* drawWindow)
	{
		drawWindow->Line(pos.x, pos.y, pos.x - (20 * size), pos.y + (10 * size), 0xffffff);
		drawWindow->Line(pos.x - (20 * size), pos.y + (10 * size), pos.x - (5 * size), pos.y + (30 * size), 0xffffff);
		drawWindow->Line(pos.x - (5 * size), pos.y + (30 * size), pos.x + (15 * size), pos.y + (30 * size), 0xffffff);
		drawWindow->Line(pos.x + (15 * size), pos.y + (30 * size), pos.x + (10 * size), pos.y + (20 * size), 0xffffff);
		drawWindow->Line(pos.x + (10 * size), pos.y + (20 * size), pos.x + (20 * size), pos.y, 0xffffff);
		drawWindow->Line(pos.x + (20 * size), pos.y, pos.x + (17 * size), pos.y, 0xffffff);
		drawWindow->Line(pos.x + (17 * size), pos.y, pos.x, pos.y, 0xffffff);

		drawWindow->Line(pos.x - 20 * size, pos.y, pos.x + 20 * size, pos.y, 0xff0000);
		drawWindow->Line(pos.x + 20 * size, pos.y, pos.x + 20 * size, pos.y + 30 * size, 0xff0000);
		drawWindow->Line(pos.x + 20 * size, pos.y + 30 * size, pos.x - 20 * size, pos.y + 30 * size, 0xff0000);
		drawWindow->Line(pos.x - 20 * size, pos.y + 30 * size, pos.x - 20 * size, pos.y, 0xff0000);
	}
	void Asteroid::Destroy()
	{
		//TODO: Fix this workaround
		if (lifeCycle > 2)
		{
			game->AddAsteroid(pos, angle - 90, lifeCycle - 1);
			game->AddAsteroid(pos, angle + 90, lifeCycle - 1);

			enabled = false;
			return;
		}

		enabled = false;
	}
}