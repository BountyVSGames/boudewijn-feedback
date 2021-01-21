#include "precomp.h" // include this first in every .cpp file
#include "player.h"
#include "asteroid.h"
#include "bullet.h"
#include <iostream>

namespace Tmpl8
{
	Gameobject* allGameobjects[100];

	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
		// New is niet gepaart met delete. Gebruik smart pointers. Meer info aan onderaan de file.
		keyboardHandler = new KeyboardHandler();

		// New is niet gepaart met delete. Gebruik smart pointers. Meer info aan onderaan de file.
		allGameobjects[0] = new Player(this, NULL, 5, vec2(100, 100));
		AddAsteroid(vec2(200, 200), rand() % 360, 3);
		AddAsteroid(vec2(400, 400), rand() % 360, 3);
		AddAsteroid(vec2(300, 600), rand() % 360, 3);

		for (int i = 4; i < 100; i++)
		{
			allGameobjects[i] = NULL;
		}
	}

	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
	}

	static int frame = 0;
	int keyText = 0;
	char* text = "test";

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick(float deltaTime)
	{
		// clear the graphics window
		screen->Clear(0);
		//// print something in the graphics window
		screen->Print(text, 2, 2, 0xffffff);

		for (int i = 0; i < sizeof(allGameobjects); i++)
		{
			if (allGameobjects[i] == NULL)
			{
				break;
			}
			
			if (allGameobjects[i]->enabled)
			{
				for (int j = 0; j < sizeof(allGameobjects); j++)
				{
					if (allGameobjects[j] == NULL || !allGameobjects[i]->enabled)
					{
						break;
					}
					else if (!allGameobjects[j]->enabled)
					{
						continue;
					}

					if (allGameobjects[i] != allGameobjects[j])
					{
						allGameobjects[i]->Collision(allGameobjects[j]);
					}
				}

				allGameobjects[i]->Update(deltaTime);
			}
		}
	}

	void Game::KeyDown(int key)
	{
		switch (key)
		{
			case SDL_SCANCODE_UP:
				keyboardHandler->isUpInputButtonDown = true;
				break;
			case SDL_SCANCODE_LEFT:
				keyboardHandler->isLeftInputButtonDown = true;
				break;
			case SDL_SCANCODE_DOWN:
				keyboardHandler->isDownInputButtonDown = true;
				break;
			case SDL_SCANCODE_RIGHT:
				keyboardHandler->isRightInputButtonDown = true;
				break;
			case SDL_SCANCODE_SPACE:
				keyboardHandler->isSpaceInputButtonDown = true;
		}
	}
	void Game::KeyUp(int key)
	{
		switch (key)
		{
			case SDL_SCANCODE_UP:
				keyboardHandler->isUpInputButtonDown = false;
				break;
			case SDL_SCANCODE_LEFT:
				keyboardHandler->isLeftInputButtonDown = false;
				break;
			case SDL_SCANCODE_DOWN:
				keyboardHandler->isDownInputButtonDown = false;
				break;
			case SDL_SCANCODE_RIGHT:
				keyboardHandler->isRightInputButtonDown = false;
				break;
			case SDL_SCANCODE_SPACE:
				keyboardHandler->isSpaceInputButtonDown = false;
		}
	}

	void Game::AddBullet(vec2 bulletPos, int angle, bool isPlayerOwner)
	{
		for (int i = 0; i < 100; i++)
		{
			if (allGameobjects[i] == NULL || !allGameobjects[i]->enabled)
			{
				// MEMORY LEAKS MEMORY LEAKS MEMORY LEAKS
				allGameobjects[i] = new Bullet(this, NULL, 1, bulletPos, angle, isPlayerOwner);
				break;
			}
		}
	}
	void Game::AddAsteroid(vec2 astroidPos, int angle, int lifeCycle)
	{
		for (size_t i = 0; i < 100; i++)
		{
			if (allGameobjects[i] == NULL || !allGameobjects[i]->enabled)
			{
				// MEMORY LEAKS MEMORY LEAKS MEMORY LEAKS
				allGameobjects[i] = new Asteroid(this, NULL, lifeCycle, astroidPos, angle, lifeCycle);

				// Ik leg even uit wat hier mis gaat: met new maak je een Asteroid (of Bullet) aan op de heap. Maar die word nooit meer verwijderd.
				// Alleen de referentie daarnaartoe word wel verwijderd. Ofwel-- er ontstaat een leak.
				// Dit kun je ook terug zien in het geheugengebruik van je game. Die gaat naarmate het langer draait alsmaar omhoog.
				//
				// De rule-of-thumb met het gebruiken van new is dat er ALTIJD een bijbehorende delete bij moet. Je hebt hier classes voor
				// die dit voor je kunnen doen. Bijvoorbeeld std::unique_ptr. Als je die overschrijft dan word de oude resource automatisch gedelete.
				//
				// Maar het makkelijkste blijft toch om geen new te gebruiken, en als je ze moet gebruiken,
				// gebruik iets als std::unique_ptr en std::make_unique.
				// https://en.cppreference.com/w/cpp/memory/unique_ptr
				//
				// Door de ruwe pointers in allGameobjects te vervangen met std::unique_ptrs heb ik al ervoor gezorgd dat het geheugengebruik minder hard
				// groet. Maar helaas is het nog niet constant. (Of eigenlijk zou het niet meer moeten groeien na een bepaalde tijd, dat heb ik nog niet
				// getest! Doe dat vooral)

				break;
			}
		}
	}
};