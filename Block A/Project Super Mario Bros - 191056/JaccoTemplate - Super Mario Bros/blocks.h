#pragma once
#include "gameobject.h"

namespace Tmpl8
{
	class Blocks : public Gameobject
	{
		protected:
			virtual void BlockInteraction() = 0;
		public:
			Blocks(Game* currentGame, vec2 newPos, int newSize) :
				Gameobject(currentGame, newPos, 0, newSize)
			{};

			~Blocks();
	};
}