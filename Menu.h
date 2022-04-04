#pragma once
#include "template.h"
#include "surface.h"

namespace Snowy {
	class Menu
	{
	public:
		explicit Menu(Tmpl8::Sprite* addMenuBackground) : menuBackground(addMenuBackground),
		                                                  activeMenuSprite(menuBackground),
		                                                  optionsScreen( new Tmpl8::Sprite(new Tmpl8::Surface("assets/options.png"), 1)),
		                                                  isActive(true), currentWindow(0), difficultyMode(0)
		{
		}

		void SetSprite(Tmpl8::Sprite* newSprite);
		Tmpl8::Sprite* GetSprite();

		void SetActiveState(bool newState);
		bool GetActiveState();

		void SetCurrentWindow(int newWindow);
		int GetCurrentWindow();

		void SetDifficultyMode(int newMode);
		int GetDifficultyMode();

		void DrawOnScreen(Tmpl8::Surface* screen);

	private:
		// The image used for the menu
		Tmpl8::Sprite* menuBackground;

		// The image currently drawn
		Tmpl8::Sprite* activeMenuSprite;

		// The options screen
		Tmpl8::Sprite* optionsScreen;

		// Whether the menu is actually active
		bool isActive;
		
		// 0: Main menu, 1: Options screen
		int currentWindow;

		// The difficulty of the game: affects ball speed and amount
		int difficultyMode;
	};
}