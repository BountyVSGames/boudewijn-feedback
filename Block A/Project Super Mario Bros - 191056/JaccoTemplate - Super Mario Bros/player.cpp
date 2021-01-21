#include "player.h"
#include <iostream>

namespace Tmpl8
{
	void Player::Update(float deltaTime)
	{
		Movement(deltaTime);

		Animation(deltaTime);
	}
	void Player::Animation(float deltaTime)
	{
		if (animationUpdateTime > 0)
		{
			animationUpdateTime -= deltaTime;
			return;
		}

		graphic->SetFrame(graphic_currentFrame);
		bigMarioSprite->SetFrame(graphic_currentFrame);

		switch ((int)state)
		{
			case 1:
				if (graphic_currentFrame == 10)
				{
					graphic_currentFrame = 8;
					break;
				}

				graphic_currentFrame++;
				break;
			case 2:
				if (graphic_currentFrame == 3)
				{
					graphic_currentFrame = 1;
					break;
				}

				graphic_currentFrame++;
				break;
		}

		animationUpdateTime = 2;
	}
	void Player::CameraMovement()
	{
		currentGame->SetScreenPosX((int)pos.x - (SCRWIDTH / 2));

		if (((int)pos.x - (SCRWIDTH / 2)) < cameraReachedX)
		{
			currentGame->SetScreenPosX(cameraReachedX);
		}
		else
		{
			cameraReachedX = (int)pos.x - (SCRWIDTH / 2);
		}

		if (currentGame->GetScreenPosX() < 0)
		{
			currentGame->SetScreenPosX(0);
		}
		if (currentGame->GetScreenPosY() < 0)
		{
			currentGame->SetScreenPosY(0);
		}

		if (currentGame->GetScreenPosX() > 5800)
		{
			currentGame->SetScreenPosX(5800);
		}
	}
	void Player::Collision()
	{
		// Je hebt geen up collision. Overigens is deze functie ook erg groot.

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
				if (hSpeed > 0)
				{
					hSpeed = 0;
				}
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
				if (hSpeed < 0)
				{
					hSpeed = 0;
				}
			}
		}
	}
	void Player::Draw(Surface* gameWindow)
	{
		if (pos.y > 570)
		{
			return;
		}

		if (healthPoints == 2)
		{
			//bigMarioSprite->DrawScaled(scrPosX, scrPosY - (graphic->GetHeight() / 2), bigMarioSprite->GetWidth() * size, bigMarioSprite->GetHeight() * size, gameWindow);
			graphic->DrawScaled((int)scrPosX, (int)scrPosY - (graphic->GetHeight() / 2), graphic->GetWidth() * size, graphic->GetHeight() * size, gameWindow);
		}
		else if(healthPoints <= 1)
		{
			//bigMarioSprite->DrawScaled(scrPosX, scrPosY - (graphic->GetHeight() / 2), bigMarioSprite->GetWidth() * size, bigMarioSprite->GetHeight() * size, gameWindow);
			graphic->DrawScaled((int)scrPosX, (int)scrPosY - (graphic->GetHeight() / 2), graphic->GetWidth() * size, graphic->GetHeight() * size, gameWindow);
		}
	}
	void Player::Movement(float deltaTime)
	{
		// Deze functie is erg groot. Probeer hem kleiner te maken. Je kunt bijvoorbeeld een functie schrijven
		// dat de player input ophaalt en het in een vector zet.
		//
		// vec2 playerInput = GetInput();
		// 
		// if (playerInput.x < 0) {
		//   MoveLeft();
		// } else if (playerInput.x > 0) {
		//   MoveRight();
		// }
		// 
		// if (playerInput.y > 0) {
		//   Jump();
		// }
		if (currentGame->GetKeyboardHandler()->isRightInputButtonDown)
		{
			if (hSpeed < maxSpeed)
			{
				hSpeed += .5f * deltaTime;
			}
		}
		else if (currentGame->GetKeyboardHandler()->isLeftInputButtonDown)
		{
			if (hSpeed > -maxSpeed)
			{
				hSpeed -= .5f * deltaTime;
			}
		}
		else if (hSpeed != 0)
		{
			hSpeed = 0;
		}

		if(vSpeed < 10 || !collide) vSpeed += currentGame->GetGlobalGravity();

		Collision();

		if (collide && currentGame->GetKeyboardHandler()->isSpaceInputButtonDown)
		{
			if (healthPoints == 1)
			{
				healthPoints = 2;
			}
			else if (healthPoints == 2)
			{
				healthPoints = 1;
			}
			vSpeed = -11;
		}

		if (hSpeed > 0 && vSpeed == 0 && (int)state != 2)
		{
			SetPlayerState(2);
		}
		else if (hSpeed < 0 && vSpeed == 0 && (int)state != 1)
		{
			SetPlayerState(1);
		}
		else if((int)state != 0 && vSpeed == 0 && hSpeed == 0)
		{
			SetPlayerState(0);
		}

		if (vSpeed != 0)
		{
			if (hSpeed < 0)
			{
				SetPlayerState(3);
			}
			else
			{
				SetPlayerState(4);
			}
		}

		pos.x += hSpeed;
		pos.y += vSpeed;

		CameraMovement();
		GetScreenPos();
	}
	void Player::SetPlayerState(int stateID)
	{
		state = (playerState)stateID;

		switch ((int)stateID)
		{
			case 0:
				graphic_currentFrame = 0;
				break;
			case 1:
				graphic_currentFrame = 8;
				break;
			case 2:
				graphic_currentFrame = 1;
				break;
			case 3:
				graphic_currentFrame = 12;
				break;
			case 4:
				graphic_currentFrame = 5;
				break;
			case 5:
				graphic_currentFrame = 0;
				break;
			case 6:
				graphic_currentFrame = 10;
				break;
			case 7:
				graphic_currentFrame = 1;
				break;
			case 8:
				graphic_currentFrame = 5;
				break;
		}
	}
}