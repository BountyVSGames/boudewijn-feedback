#pragma once
#include "precomp.h";

namespace Tmpl8
{
	class Map
	{
		private:
			char mapLocation;
			char worldName;

			vec2 maxMapPos;
			vec2 halfwayPoint;
		public:
			Map(vec2 newMaxMapPos, vec2 newHalfwayPoint, char newWorldName, char newMapLocation) :
				maxMapPos(newMaxMapPos),
				halfwayPoint(newHalfwayPoint)
			{
				mapLocation = newMapLocation;
				worldName = newMapLocation;
			}	
	};
}