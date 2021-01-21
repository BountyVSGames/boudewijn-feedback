#pragma once
#include "precomp.h"

namespace Tmpl8
{
	// Deze classe lijkt niet compleet te zijn
	// maar als je hem van plan bent af te maken, zou ik het aanraden om jezelf te verdiepen in
	// move-semantics in C++.
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