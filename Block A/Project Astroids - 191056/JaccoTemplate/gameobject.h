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

			// Het gebruik van angle en speed is minder algemeen. Ik stel voor om vec2 velocity; te gebruiken als vervanging voor speed en angle.
			// Een vector is namelijk niks anders dan een hoek en een magnitude gecodeerd als een x en y.
			
			// Het kan wel zijn dat je moeite zult hebben met het tekenen van een gedraaid voorwerp, dit kun je eventueel als 3e waarde in je pos coderen.
			// Hiervoor zou ik wel het datatype float gebruiken en een waarde in radians per second.
			int angle = 0;

			int frame = 0;

			vec2 pos;

			// Het gebruiken van `vec2 velocity;` maakt `vec2 movement;` overbodig.
			//
			// Tevens het gebruik van velocity als vector i.p.v. een hoek een een snelheid is meer
			// algemener en stelt je in staat om lastigere berekeningen makkelijker te maken.
			// (Klinkt misschien tegenstrijdig, maar het gemak is dat je kunt redeneren over één vector die
			//  alles vastlegt over de verplaatsing van een gameobject)
			vec2 movement;


			// Het verhaaltje hierboven even kort opgeschreven.
			// Wat ik zou doen is:
			// 
			// vec2 pos; // Dit bestaat uit de elementen [x, y]
			// vec2 velocity; // Dit bestaat uit de elementen [dx, dy], de d staat voor delta.
			//					 Velocity codeert dus de verandering per seconde van dit gameobject.
			//                   Position codeert je huidige positie
			// float angle;   // Huidige draai
			// float angularVelocity; // Huidige verandering van de draai
			// 
			// Ik had het overigens ook over radians, ik weet niet of je het kent, maar het is gewoon meer formele aanpak dan graden.
			// Zie: https://nl.wikipedia.org/wiki/Radiaal_(wiskunde)
			//
			// En voila, je update functie is nu héél simpel. Vanuit bijvoorbeeld andere classes kun je dan
			// het gedrag dingen zoals de player aanpassen zonder te 'vriemelen' met de achterliggende physics
			//
			// void Update(float delta) {
			//    pos += velocity; // Speed is gecodeerd in velocity.
			//    angle += angularVelocity;
			// }
			//
			// Je kunt een helper functie schrijven waarmee je de velocity kan aanpassen zodat het in de richting gaat van een bepaalde hoek.
			// Bijvoorbeeld:
			// static constexpr vec2 CreateAngularVector(float rotation, float magnitude) {
			//   return vec2(cos(rotation), sin(rotation)) * magnitude;
			// }
			// 
			// Op deze manier heb je de verandering van posities van gameobjects gescheiden van de huidige posities. Dit is heel erg wenselijk.
			//
			//
			//
			//
			// Als laatste kun je eventueel forces toevoegen. Dit kun je interpreteren als de verandering van velocity. Dan krijg je een update functie als dit:
			// void Update(float delta) {
			//    pos += velocity; // Speed is gecodeerd in velocity.
			//    angle += angularVelocity;
			//    velocity += force;
			//    angularVelocity += angularForce;
			// }
			//
			// Hiermee kan je weer op een natuurlijke wijze dingen versnellen/vertragen of
			// misschien zelfs van elkaar af laten botsen. (Asteroids en je vliegtuigje?)
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

			// Ik zou het werkwoord vorm van movement gebruiken, je doet namelijk iets en dat is het game object verplaatsen. 
			// Ik zou Move ipv Movement schrijven.
			virtual void Movement(float deltaTime) {};

			// Persoonlijk zou ik deze functie schrijven als: 
			// static constexpr vec2 CalculateRotation(int degree) // Dit zou meer C++ idiomatisch zijn
			// {
			// 	 float angle = degree * PI / 180;
			//   
			//   return vec2(cos(angle), sin(angle));
			// } 
			//
			// Misschien dat je docent zegt dat het inefficient zou zijn, dan kun je hem wijzen naar deze pagina:
			// https://en.cppreference.com/w/cpp/language/copy_elision
			// https://stackoverflow.com/questions/3601602/what-are-rvalues-lvalues-xvalues-glvalues-and-prvalues
			// C++ garandeerd dat als de return waarde een prvalue is dat het object in-place word geconstruct.
			// Ofwel als je de functie als volgt gebruikt: 
			//
			// ```
			// this->movement = CalculateRotation(69); // mag ook naar een class member
			// ```
			//
			// dan is dat even efficient als
			// 
			// ```
			// CalculateRotation(69, this->movement);
			// ```
			//
			// Met deze regel kan je checken of iets een prvalue is. (De check vind plaats tijdens compilation)
			// static_assert(!std::is_reference_v<decltype((vec2()))>, "Value is not a PRValue!");
			//
			// 
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