#pragma once
#include "keyboardhandler.h"
class Gameobject;

namespace Tmpl8 
{
	class Game
	{
		public:
			void SetTarget( Surface* surface ) { screen = surface; }
			void Init();
			void Shutdown();
			void Tick( float deltaTime );
			void MouseUp( int button ) { /* implement if you want to detect mouse button presses */ }
			void MouseDown( int button ) { /* implement if you want to detect mouse button presses */ }
			void MouseMove( int x, int y ) { /* implement if you want to detect mouse movement */ }
			void KeyUp(int key);
			void KeyDown(int key);

			void AddBullet(vec2 bulletPos, int angle, bool isPlayerOwner);
			void AddAsteroid(vec2 astroidPos, int angle, int lifeCycle);

			KeyboardHandler* GetKeyboardHandler()
			{
				return keyboardHandler;
			};
			Surface* GetSurface()
			{
				return screen;
			}
		private:
			KeyboardHandler* keyboardHandler;
			Surface* screen;
	};

}; // namespace Tmpl8