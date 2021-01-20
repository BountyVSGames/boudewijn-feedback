#pragma once
#include "precomp.h"

namespace Tmpl8
{
	class String
	{
		private:
			char charString;
		public:
			String(char newCharString)
			{
				charString = newCharString;
			}

			void RemoveCharFromString(char charToRemove)
			{
				for (int i = 0; i < sizeof(charString); i++)
				{
					//if(charSt)
				}
			}

	};
}