#pragma once
#include "gameobject.h"

namespace Tmpl8
{
	class Asteroid : public Gameobject
	{
		private:
			int lifeCycle;
		public:
			Asteroid(Game* currentGame, Sprite* newSprite, float newSize, vec2 newPos, int newAngle, int newLifeCycle) :
				Gameobject(currentGame, newSprite, newSize, newPos)
			{
				angle = newAngle;
				lifeCycle = newLifeCycle;
			}

			void Collision(Gameobject* object);
			void Draw(Surface* drawWindow);
			void Destroy();
			void Movement(float deltaTime);
			void Update(float deltaTime);
	};
}