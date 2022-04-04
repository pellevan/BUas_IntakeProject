#pragma once
#include "kinematicbody.h"


namespace Snowy
{
	class HUD
	{
	public:
		explicit HUD(Player* Player, Tmpl8::Surface* Screen);

		void DrawHearts() const;
	private:
		Player* activePlayer = nullptr;
		Tmpl8::Surface* activeScreen = nullptr;

		Tmpl8::Sprite* heartSprite = nullptr;
	};
}