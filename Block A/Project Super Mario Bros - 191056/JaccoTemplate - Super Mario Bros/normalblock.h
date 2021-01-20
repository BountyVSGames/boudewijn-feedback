#pragma once
#include "blocks.h"

namespace Tmpl8
{
	class NormalBlock : public Blocks
	{
		protected:
			void BlockInteraction();
		public:
			NormalBlock(Game* currentGame, vec2 newPos, int newSize) :
				Blocks(currentGame, newPos, newSize)
			{};

			~NormalBlock();

			void Animation(float deltaTime);
			void Collision() {};
			void Draw(Surface* gameWindow);
			void Update(float deltaTime);
	};
}