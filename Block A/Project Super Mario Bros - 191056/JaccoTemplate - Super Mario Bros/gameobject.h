#pragma once
#include "precomp.h"
#include "game.h"

namespace Tmpl8
{
	class Gameobject
	{
		protected:
			Game* currentGame;

			vec2 pos;

			bool enabled;

			int graphic_currentFrame = 0;
			int healthPoints = 0;
			float scrPosX = 0;
			float scrPosY = 0;
			int size = 0;

			float animationUpdateTime = 200;
			float speed;

			void GetScreenPos()
			{
				scrPosX = pos.x - currentGame->GetScreenPosX();
				scrPosY = pos.y - currentGame->GetScreenPosY();
			}
		public:
			Gameobject(Game* setGame, vec2 newPos, float newSpeed, int newSize) :
				currentGame(setGame)
			{
				enabled = true;

				pos = newPos;
				speed = newSpeed;
				size = newSize;
			};

			~Gameobject() {};

			virtual void Animation(float deltaTime) = 0;
			virtual void Collision() = 0;
			virtual void Update(float deltaTime) = 0;
			virtual void Draw(Surface* gameWindow) = 0;

			bool GetEnabledState()
			{
				return enabled;
			}
			void SetEnabledState(bool state)
			{
				enabled = state;
			}

			Sprite* graphic;
	};
}