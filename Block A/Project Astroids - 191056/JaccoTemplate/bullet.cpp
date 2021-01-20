#include "precomp.h"
#include "bullet.h"

namespace Tmpl8
{
	void Bullet::Update(float deltaTime)
	{
		if (lifeTime < 0)
		{
			Destroy();
			return;
		}
		else
		{
			lifeTime -= deltaTime;
		}

		Movement(deltaTime);
		Draw(game->GetSurface());
	}

	void Bullet::Collision(Gameobject* object)
	{
		bool minX = pos.x + 10 >= (object->GetPos().x + 20) * object->GetSize();
		bool maxX = pos.x <= object->GetPos().x;
		bool minY = pos.y + 30 >= (object->GetPos().y + 30) * object->GetSize();
		bool maxY = pos.y <= object->GetPos().y;

		if(minX || maxX || minY || maxY)
			return;

		/*std::cout << pos.x + 10 << " . " << (object->GetPos().x + 20) * object->GetSize() << std::endl;
		std::cout << pos.x << " . " << object->GetPos().x << std::endl;
		std::cout << pos.y + 30 << " . " << (object->GetPos().y + 30) * object->GetSize() << std::endl;
		std::cout << pos.y << " . " << object->GetPos().y << std::endl;*/

		String fullObjectName = String(typeid(*object).name());
		fullObjectName.StringFromIndex(13);

		if (isOwnerPlayer && object != this && fullObjectName == "Asteroid")
		{
			std::cout << minX << " . " << maxX << " . " << minY << " . " << maxY;

			object->Destroy();
			this->Destroy();

			return;
		}
	}

	void Bullet::Draw(Surface* gameWindow)
	{
		vec2 test0 = vec2(pos.x, pos.y);
		vec2 test1 = vec2(pos.x + 10, pos.y);
		vec2 test2 = vec2(pos.x + 10, pos.y + 30);
		vec2 test3 = vec2(pos.x, pos.y + 30);

		gameWindow->Line(test0.x, test0.y, test1.x, test1.y, 0xffffff);
		gameWindow->Line(test1.x, test1.y, test2.x, test2.y, 0xffffff);
		gameWindow->Line(test2.x, test2.y, test3.x, test3.y, 0xffffff);
		gameWindow->Line(test3.x, test3.y, test0.x, test0.y, 0xffffff);
	}

	void Bullet::Destroy()
	{
		this->enabled = false;
	}

	void Bullet::Movement(float deltaTime)
	{
		if (pos.x > (SCRWIDTH + 10))
		{
			pos.x = 1 - 10;
		}
		else if (pos.x < (0 - 10))
		{
			pos.x = SCRWIDTH - 10;
		}
		if (pos.y > (SCRHEIGHT + 10))
		{
			pos.y = 0;
		}
		else if (pos.y < (0 - 10))
		{
			pos.y = SCRHEIGHT - 10;
		}

		CalculateRotation(angle, movement);

		pos += movement * speed;
	}
}