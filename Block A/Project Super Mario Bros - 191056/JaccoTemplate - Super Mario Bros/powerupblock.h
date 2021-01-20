#pragma once
#include "blocks.h"

namespace Tmpl8
{
	class PowerupBlock : public Blocks
	{
		protected:
			void BlockInteraction();
		public:
			PowerupBlock(Game* currentGame, vec2 newPos, int newSize) :
				Blocks(currentGame, newPos, newSize)
			{
				animationUpdateTime = 50;
			};

			~PowerupBlock();

			void Animation(float deltaTime);
			void Collision() {};
			void Draw(Surface* gameWindow);
			void Update(float deltaTime);
	};
}