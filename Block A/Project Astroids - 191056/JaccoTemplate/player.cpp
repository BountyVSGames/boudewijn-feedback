#include "precomp.h"
#include "player.h"
#include <iostream>;

namespace Tmpl8
{
	void Player::Collision(Gameobject* object)
	{
		bool minX = (pos.x + 10) > object->GetPos().x + 20;
		bool maxX = (pos.x - 10) < object->GetPos().x;
		bool minY = (pos.y + 2.5f) > object->GetPos().y + 30;
		bool maxY = pos.y < object->GetPos().y;

		if ((minX && maxX) && (minY && maxY))
		{
			String fullObjectName = String(typeid(*object).name());
			fullObjectName.StringFromIndex(13);

			if (object != this && fullObjectName == "Asteroid")
			{
				std::cout << "COLIDE" << std::endl;

				return;
			}
		}
	}
	void Player::Draw(Surface* drawWindow)
	{
		vec2 test1 = vec2(pos.x + 10, pos.y + 10);
		vec2 test2 = vec2(pos.x, pos.y);
		vec2 test3 = vec2(pos.x + 20, pos.y);

		if (movement.y < 0)
		{
			test1 -= movement * -30;
		}
		else
		{
			test1 += movement * 20;
		}
		//test1 += movement * 20;
		test2 += movement;
		test3 += movement;

		drawWindow->Line(test1.x, test1.y, test2.x, test2.y, 0xffffff);
		drawWindow->Line(test1.x, test1.y, test3.x, test3.y, 0xffffff);
	}
	void Player::Movement(float deltaTime)
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
			pos.y = 1 - 10;
		}
		else if (pos.y < (0 - 10))
		{
			pos.y = SCRHEIGHT - 10;
		}

		if (game->GetKeyboardHandler()->isUpInputButtonDown && speed < 4)
		{
			speed += .05;
		}
		else if(speed > 0)
		{
			speed -= .1;
		}
		else
		{
			speed = 0;
		}
		 
		if (game->GetKeyboardHandler()->isLeftInputButtonDown)
		{
			angle -= speed;
		}
		if (game->GetKeyboardHandler()->isRightInputButtonDown)
		{
			angle += speed;
		}

		if (angle > 359)
		{
			angle = 1;
		}
		else if (angle < 1)
		{
			angle = 359;
		}

		CalculateRotation(angle, movement);

		pos += movement * speed;
	}
	void Player::Update(float deltaTime)
	{
		Player::Movement(deltaTime);

		if (game->GetKeyboardHandler()->isSpaceInputButtonDown && shootDelay < 0)
		{
			vec2 test1 = vec2(pos.x, pos.y);
			test1 += movement * 20;

			game->AddBullet(vec2(test1.x, test1.y), angle, true);
			shootDelay = 100;
		}
		else
		{
			shootDelay -= deltaTime;
		}

		Player::Draw(game->GetSurface());
	}
}