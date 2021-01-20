#pragma once
#include "game.h"
#include <iostream>

namespace Tmpl8
{
	class Gameobject
	{
		protected:
			Game* game;
			Sprite* sprite;

			float speed = 0;
			float size = 1;

			int angle = 0;
			int frame = 0;

			vec2 pos;
			vec2 movement;
		public:
			Gameobject(Game* currentGame, Sprite* newSprite, float newSize, vec2 newPos) :
				game(currentGame),
				sprite(newSprite),
				pos(newPos)
			{
				size = newSize;
				speed = 2;
				movement = vec2(0,0);
			};

			bool enabled = true;

			vec2 GetPos()
			{
				return pos;
			}

			float GetSize()
			{
				return size;
			}

			virtual void Collision(Gameobject* object) {};
			virtual void Update(float deltaTime) {}; //{ std::cout << "TEST"; };
			virtual void Movement(float deltaTime) {};

			void CalculateRotation(int degree, vec2& vec2ToCalculate)
			{
				float angle = degree * PI / 180;

				vec2ToCalculate.x = cos(angle);
				vec2ToCalculate.y = sin(angle);
			}

			virtual void Destroy() {};
			virtual void Draw(Surface* surface)
			{
				sprite->SetFrame(frame);
				sprite->Draw(surface, (int)pos.x, (int)pos.y);
			}
	};
}