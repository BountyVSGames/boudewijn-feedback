#include "precomp.h"
#include "asteroid.h"

namespace Tmpl8
{
	void Asteroid::Collision(Gameobject* object)
	{
		bool minX = pos.x + 20 < object->GetPos().x + 10;//(object->GetPos().x + 20) * object->GetSize();
		bool maxX = pos.x > object->GetPos().x - 10;//object->GetPos().x;
		bool minY = pos.y + 30 < object->GetPos().y + 2.5f;//(object->GetPos().y + 30) * object->GetSize();
		bool maxY = pos.y > object->GetPos().y;

		if ((minX && maxX) && (minY && maxY))
		{
			// Het gebruiken van typeid voegt voor C++ *heel veel* overhead toe. Omdat de compiter met RTTI de code moet compileren.
			// RTTI staat voor Run Time Type Information. In performance critical applications is het gebruikelijk om RTTI uit te zetten.
			// Ik kan mij voorstellen dat dit (ongeacht dat het wel werkt) niet gewenst is.
			String fullObjectName = String(typeid(*object).name());

			// Deze functie maakt een kopie van (een deel van) fullObjectName zonder dat de string uiteindelijk word gecleaned. Memory leak! Als je heel
			// veel collisions maakt met asteroids zou je game kunnen crashen. Ik zou een andere manier verzinnen om te kunnen herkennen dat je een
			// asteroid aanraakt.
			fullObjectName.StringFromIndex(13);

			// Debug print, ik zou er #if NDEBUG ... #endif omheen zetten.
			// Voorbeeld:
			//
			// #ifdef NDEBUG
			// nondebug ofwel release
			// #else
			// debug code
			// #endif
			//
			// Op deze manier voorkom je onnodige prints mocht je in een echte situatie je game shippen.
			std::cout << fullObjectName.GetString() << std::endl;

			// Ik zou zelf op hoger niveau testen dat object != this is, het is namelijk foutgevoelig om dit voor elke implementatie van een
			// collision functie te moeten doen. Daarnaast kan ik mij geen situatie bedenken waar het wenselijk is dat een object met zichzelf
			// kan botsen.
			if (object != this && fullObjectName == "Player")
			{
				std::cout << "COLIDE";

				return; // Return is overbodig
			}
		}
	}

	void Asteroid::Update(float deltaTime)
	{
		/*if (game->GetKeyboardHandler()->isSpaceInputButtonDown)
		{
			Destroy();
		}*/

		Asteroid::Movement(deltaTime);
		Asteroid::Draw(game->GetSurface());
	}
	void Asteroid::Movement(float deltaTime)
	{
		if (pos.x > (SCRWIDTH + (10 * size))) // Voorkom het gebruik van magic numbers, zoals de 10 op deze regel.
											  // Voor mij is het niet duidelijk wat die 10 betekend.
											  // Maak hier een constante voor aan in bijvoorbeeld Gameobject? Als je constexpr static gebruikt kost het geen
											  // memory tijdens run-time.
		{
			pos.x = 1 - (10 * size); // Magic number
		}
		else if (pos.x < (0 - (10 * size))) // Magic numbers, waarom doe je '0 - n' waar n een deel is van de expressie? Is -n niet hetzelfde (maar mooier)?
		{
			pos.x = SCRWIDTH - (10 * size); // Magic number
		}

		if (pos.y > (SCRHEIGHT + (10 * size))) // Magic number
		{
			pos.y = 1 - (10 * size); // Magic numbers
		}
		else if (pos.y < (0 - (10 * size))) // Magic number
		{
			pos.y = SCRHEIGHT - (10 * size); // Magic number
		}

		CalculateRotation(angle, movement); // Zie commentaar bij CalculateRotation, voorgestelde verandering is `movement = CalculateRotation(angle);`
		
		// Overigens, het lijkt erop dat een asteroid nooit van angle hoeft te veranderen,
		// zou je dit niet gewoon kunnen coderen met een member variable `vec2 velocity;`
		// Elke update moet je de velocity bij de position optellen. Tijdens construction
		// bereken je maar een keer de velocity. Dit commentaar staat ook bij Gameobject

		pos += movement * speed;
	}
	void Asteroid::Draw(Surface* drawWindow)
	{
		// Mooie functie, heel obscuur ook. Weet alleen niet of het waardig is om het anders aan te pakken.
		drawWindow->Line(pos.x, pos.y, pos.x - (20 * size), pos.y + (10 * size), 0xffffff);
		drawWindow->Line(pos.x - (20 * size), pos.y + (10 * size), pos.x - (5 * size), pos.y + (30 * size), 0xffffff);
		drawWindow->Line(pos.x - (5 * size), pos.y + (30 * size), pos.x + (15 * size), pos.y + (30 * size), 0xffffff);
		drawWindow->Line(pos.x + (15 * size), pos.y + (30 * size), pos.x + (10 * size), pos.y + (20 * size), 0xffffff);
		drawWindow->Line(pos.x + (10 * size), pos.y + (20 * size), pos.x + (20 * size), pos.y, 0xffffff);
		drawWindow->Line(pos.x + (20 * size), pos.y, pos.x + (17 * size), pos.y, 0xffffff);
		drawWindow->Line(pos.x + (17 * size), pos.y, pos.x, pos.y, 0xffffff);

		drawWindow->Line(pos.x - 20 * size, pos.y, pos.x + 20 * size, pos.y, 0xff0000);
		drawWindow->Line(pos.x + 20 * size, pos.y, pos.x + 20 * size, pos.y + 30 * size, 0xff0000);
		drawWindow->Line(pos.x + 20 * size, pos.y + 30 * size, pos.x - 20 * size, pos.y + 30 * size, 0xff0000);
		drawWindow->Line(pos.x - 20 * size, pos.y + 30 * size, pos.x - 20 * size, pos.y, 0xff0000);
	}
	void Asteroid::Destroy()
	{
		//TODO: Fix this workaround
		if (lifeCycle > 2)
		{
			game->AddAsteroid(pos, angle - 90, lifeCycle - 1);
			game->AddAsteroid(pos, angle + 90, lifeCycle - 1);

			enabled = false;
			return;
		}

		enabled = false;
	}
}