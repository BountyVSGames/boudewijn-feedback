#pragma once
#include "ships.h"

namespace Tmpl8
{
	class Player : public Ships
	{
		public:
			Player(Game* currentGame, Sprite* newSprite, float newSize, vec2 newPos) :
				Ships{ currentGame, newSprite, newSize, newPos }
			{
				angle = 90;
			};	

			void Collision(Gameobject* object);
			void Draw(Surface* drawWindow);
			void Update(float deltaTime);
			void Movement(float deltaTime);
		private:
			float shootDelay = 100;
	};
}