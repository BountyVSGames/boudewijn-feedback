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
		keyboardHandler = new KeyboardHandler();

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
				allGameobjects[i] = new Asteroid(this, NULL, lifeCycle, astroidPos, angle, lifeCycle);
				break;
			}
		}
	}
};