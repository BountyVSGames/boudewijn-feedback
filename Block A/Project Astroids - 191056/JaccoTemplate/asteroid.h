#pragma once
#include "gameobject.h"

namespace Tmpl8
{
	class Asteroid : public Gameobject
	{
		private:
			int lifeCycle;
		public:
			// Deze constructor heeft best veel variabelen, wat het aanroepen van deze constructor onduidelijk kan maken.
			// Stel je voor dat iemand anders je code leest en `Asteroid(this, &SomeSprite, 0, vec2(), 0, 200);` tegen komt.
			// Hoe moet hij de variabelen van elkaar onderschijden?
			//
			// Als je newAngle codeert in de position in de 3e variabele van een vec3, dan krijg je een veel meer uniform stelsel
			// om de positie en orientatie bij te houden. Dan kun je in de plaats dit schrijven.
			// Asteroid(this, &SomeSprite, vec3(0, 0, 90), 10, 0); Het liefst zou je ook moeten kijken hoe je lifecycle weg kan werken.
			// Als dat is gelukt word het makkelijker om de waardes te onderscheiden. Stel voor dat een aanroep van de constructor er zo uit ziet:
			// 
			// Asteroid(this, &Sprite, vec3(0, 0, 0), 20). Kun je raden welke waardes wat is?
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