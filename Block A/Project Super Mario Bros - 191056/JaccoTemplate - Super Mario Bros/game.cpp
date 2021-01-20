#include "precomp.h" // include this first in every .cpp file
#include "game.h"
#include "player.h"
#include "powerupblock.h"
#include "normalblock.h"
#include "mushroompowerup.h"
#include "map.h"

namespace Tmpl8
{
	Surface* ATile;
	Surface* tilesSpriteSheet;
	Surface* playerSpriteSheet;
	Surface* theTiles[71];
	Surface* background;

	Sprite* backgroundSprite;
	Sprite* dummySprite;

	Gameobject* allObjects[50];

	Map* currentMap;

	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
		Surface* dummyTile = new Surface(32,32);

		//currentMap = new Map(vec2(209 * 32, 20 * 32), vec2(104 * 32), "", "");

		xOffset = 0;

		keyboardHandler = new KeyboardHandler();

		background = new Surface("assets/super mario/background.png");
		playerSpriteSheet = new Surface("assets/super mario/NES - Super Mario Bros - Mario & Luigi.png");
		tilesSpriteSheet = new Surface("assets/super mario/Super Mario Tileset + items 2.png");

		backgroundSprite = new Sprite(background, 1);

		ATile = new Surface(224, 32);
		playerSpriteSheet->CopyFromTo(0, 19, playerSpriteSheet->GetPitch(), ATile, 0, 0);
		allObjects[0] = new Player(this, vec2(64, 100), new Sprite(ATile, 14), 4, 2);

		ATile = new Surface(208, 16);
		playerSpriteSheet->CopyFromTo(0, 0, playerSpriteSheet->GetPitch(), ATile, 0, 0);
		allObjects[0]->graphic = new Sprite(ATile, 13);

		for (int i = 0; i < 70; i++)
		{
			ATile = new Surface(32, 32);
			tilesSpriteSheet->CopyFromTo(0 + (i * 32), 0, tilesSpriteSheet->GetPitch(), dummyTile, 0, 0);
			dummySprite = new Sprite(dummyTile, 1);
			//dummySprite->Draw(ATile, 0, 0);
			dummySprite->DrawScaled(0, 0, dummySprite->GetWidth(), dummySprite->GetWidth(), ATile);
			theTiles[i + 1] = ATile;
		}

		for (float y = 0; y < 19; y++)
		{
			for (float x = 0; x < 209; x++)
			{
				int value = this->grid[(int)y][(int)x];

				if (value == 50)
				{
					for (int i = 0; i < 50; i++)
					{
						if (allObjects[i] == NULL)
						{
							ATile = new Surface(96, 32);
							allObjects[i] = new NormalBlock(this, vec2(x * 32, y * 32), 2);
							tilesSpriteSheet->CopyFromTo(1568, 0, tilesSpriteSheet->GetPitch(), ATile, 0, 0);
							allObjects[i]->graphic = new Sprite(ATile, 3);
							allObjects[i]->SetEnabledState(true);
							break;
						}
					}
				}
				else if (value == 51)
				{
					for (int i = 0; i < 50; i++)
					{
						if (allObjects[i] == NULL)
						{
							ATile = new Surface(128, 32);
							allObjects[i] = new PowerupBlock(this, vec2(x * 32, y * 32), 2);
							tilesSpriteSheet->CopyFromTo(1760, 0, tilesSpriteSheet->GetPitch(), ATile, 0, 0);
							allObjects[i]->graphic = new Sprite(ATile, 4);
							allObjects[i]->SetEnabledState(true);
							break;
						}
					}
				}
				else if (value == 52)
				{
					for (int i = 0; i < 50; i++)
					{
						if (allObjects[i] == NULL)
						{
							ATile = new Surface(32, 32);
							allObjects[i] = new MushroomPowerup(this, vec2(x * 32, y * 32), 2);
							tilesSpriteSheet->CopyFromTo(1984, 0, tilesSpriteSheet->GetPitch(), ATile, 0, 0);
							allObjects[i]->graphic = new Sprite(ATile, 1);
							allObjects[i]->SetEnabledState(true);
							break;
						}
					}
				}
			}
		}
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
		delete(grid);
	}

	Sprite* testSprite;// = new Sprite(theTiles[1], 1);

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick(float deltaTime)
	{
		//screen->Clear(0);
		backgroundSprite->DrawScaled(0,0,SCRWIDTH, SCRHEIGHT, screen);

		xOffset = (int)screenPosX % 32;

		//Sprite* testSprite = new Sprite(theTiles[1], 1);
		testSprite = new Sprite(tilesSpriteSheet, 1);
		testSprite->Draw(screen, 0, 0);
		//testSprite->DrawScaled(0, 0, testSprite->GetWidth() * 2, testSprite->GetHeight() * 2, screen);

		for (int y = 0; y < 19; y++)
		{
			for (int x = 0; x < 26; x++)
			{
				int value = grid[y][((int)screenPosX/32) + x];

				if (value != 0 && value < 50)
				{
					theTiles[value]->CopyTo(screen, (x * theTiles[value]->GetWidth()) - xOffset, y * theTiles[value]->GetHeight());
				}
			}
		}

		for (int i = 0; i < 50; i++)
		{
			if (allObjects[i] == NULL)
			{
				return;
			}

			if (allObjects[i]->GetEnabledState())
			{
				allObjects[i]->Update(deltaTime);
				allObjects[i]->Draw(screen);
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
};