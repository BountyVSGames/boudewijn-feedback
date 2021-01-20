#pragma once
#include "gameobject.h"

namespace Tmpl8
{
	class Bullet : public Gameobject
	{
		public:
			Bullet(Game* currentGame, Sprite* newSprite, float newSize, vec2 newPos, int newDirection, bool newIsOwnerPlayer) :
				Gameobject{ currentGame, newSprite, newSize, newPos }
			{
				angle = newDirection;
				speed = 10;
				isOwnerPlayer = newIsOwnerPlayer;
			};

			void Collision(Gameobject* object);
			void Draw(Surface* drawWindow);
			void Destroy();
			void Update(float deltaTime);
			void Movement(float deltaTime);
		private:
			bool isOwnerPlayer = false;
			float lifeTime = 750;
	};
}