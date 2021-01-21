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

			// Markeer dit als virtual.
			// Ik citeer:
			// "Deleting a derived class object using a pointer of base class type that has a non-virtual
			// destructor results in undefined behavior. To correct this situation, the base class should
			// be defined with a virtual destructor. For example, following program results in undefined
			// behavior."
			// https://www.geeksforgeeks.org/virtual-destructor/
			//
			// Undefined behavior is een necessary evil in C++, als je er nog nooit van hebt gehoord. Maar
			// als je undefined behavior hebt dan kan het gedrag per compiler, compiler release, compiler
			// flags varieren. Dit is foute boel.
			//
			// Kortom: schrijf `virtual ~Gameobject() {};`
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