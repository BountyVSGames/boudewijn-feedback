#pragma once
#include "gameobject.h"

namespace Tmpl8
{
	class MushroomPowerup : public Gameobject
	{
		private:
			bool collide = false;

			float hSpeed = 2;
			float vSpeed = 0;
		public:
			MushroomPowerup(Game* currentGame, vec2 newPos, int newSize) :
				Gameobject(currentGame, newPos, 2, newSize)
			{};

			~MushroomPowerup();

			void Animation(float deltaTime);
			void Collision();
			void Draw(Surface* gameWindow);
			void Update(float deltaTime);
	};
}