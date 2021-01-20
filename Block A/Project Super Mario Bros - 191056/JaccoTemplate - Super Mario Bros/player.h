#pragma once
#include "gameobject.h"

namespace Tmpl8
{
	class Player : public Gameobject
	{
		public:
			Player(Game* setGame, vec2 newPos, Sprite* bigMarioSprite, float newSpeed, int newSize) :
				Gameobject(setGame, newPos, newSpeed, newSize),
				bigMarioSprite(bigMarioSprite)
			{
				healthPoints = 1;
				SetPlayerState(0);
			};
			~Player() {};

			void Animation(float deltaTime);
			void Update(float deltaTime);
			void Draw(Surface* gameWindow);

			void SetPlayerState(int stateID);
		private:
			enum class playerState
			{
				smallIdle = 0,
				smallWalkingLeft,
				smallWalkingRight,
				smallJumping,
				bigIdle,
				bigWalkingLeft,
				bigWalkingRigt,
				bigWalkingJumping,
				bigDuckingLeft,
				bigDuckingRight
			};

			playerState state = (playerState)1;

			Sprite* bigMarioSprite;
			
			int cameraReachedX = 0;
			
			float hSpeed = 0;
			float vSpeed = 0;
			float maxSpeed = 4;

			bool collide = false;

			void CameraMovement();
			void Collision();
			void Movement(float deltaTime);
		};
}