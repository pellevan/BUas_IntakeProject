#include "HUD.h"

namespace Snowy
{
	HUD::HUD(Player* Player, Tmpl8::Surface* Screen) : activePlayer(Player), activeScreen(Screen)
	{
		// Source: Heart image from https://www.pinterest.com/pin/639792690782908560/
		// The same image for each member (there will only be 1 HUD at one time)
		heartSprite = new Tmpl8::Sprite(new Tmpl8::Surface("assets/hearts.png"), 1);
	}

	// Draw the amount of hearts the player of the HUD has (at the current frame)
	void HUD::DrawHearts() const
	{
		switch(activePlayer->GetHP())
		{
		case 1:
			heartSprite->DrawScaled(50, 50, 50, 50, activeScreen);
			break;
		case 2:
			heartSprite->DrawScaled(50, 50, 50, 50, activeScreen);
			heartSprite->DrawScaled(100, 50, 50, 50, activeScreen);
			break;
		case 3:
			heartSprite->DrawScaled(50, 50, 50, 50, activeScreen);
			heartSprite->DrawScaled(100, 50, 50, 50, activeScreen);
			heartSprite->DrawScaled(150, 50, 50, 50, activeScreen);
			break;
		default:
			break;
		}
	}
}