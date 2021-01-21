#pragma once

namespace Tmpl8
{
	class KeyboardHandler // Doet deze keyboard handler wel iets? Misschien kun je nadenken over een betere naam
	{
	public:
		bool isLeftInputButtonDown = false;
		bool isRightInputButtonDown = false;
		bool isUpInputButtonDown = false;
		bool isDownInputButtonDown = false;
		bool isSpaceInputButtonDown = false;
	};
}
