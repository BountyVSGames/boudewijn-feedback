#pragma once
#include "gameobject.h"

namespace Tmpl8
{
	class Ships : public Gameobject
	{
		private:
			float shootDelay;
		public:
			Ships(Game* currentGame, Sprite* newSprite, float newSize, vec2 newPos) :
				Gameobject{currentGame, newSprite, newSize, newPos}
			{}

			void Shoot() {};
	};
}