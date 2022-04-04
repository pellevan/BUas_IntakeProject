#pragma once
#include "kinematicbody.h"


namespace Snowy
{
	class HUD
	{
	public:
		explicit HUD();
	private:
		Player* activePlayer = nullptr;
		Tmpl8::Surface* activeScreen = nullptr;
	};
}