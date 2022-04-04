#include "Menu.h"

namespace Snowy {
	
	// Setter for the menuBackground sprite
	void Menu::SetSprite(Tmpl8::Sprite* newSprite)
	{
		this->menuBackground = newSprite;
	}

	// Getter for the menuBackground sprite (used in draw fuction)
	Tmpl8::Sprite* Menu::GetSprite()
	{
		return this->menuBackground;
	}

	// Setter for the state of the menu (active or non-active)
	void Menu::SetActiveState(bool newState)
	{
		this->isActive = newState;
	}

	// Getter for the state of the menu (active or non-active)
	bool Menu::GetActiveState()
	{
		return this->isActive;
	}

	// Setter for the current window of the menu (0: Main menu, 1: Options menu)
	void Menu::SetCurrentWindow(int newWindow)
	{
		this->currentWindow = newWindow;
	}

	// Getter for the current menu window
	int Menu::GetCurrentWindow()
	{
		return this->currentWindow;
	}

	// Setter for the difficulty of the game (influences bullet speed and amount)
	void Menu::SetDifficultyMode(int newMode)
	{
		this->difficultyMode = newMode;
	}
	
	// Getter for the difficulty of the game
	int Menu::GetDifficultyMode()
	{
		return this->difficultyMode;
	}

	// Getter for the current window of the menu
	void Menu::DrawOnScreen(Tmpl8::Surface* screen)
	{
		screen->Clear(0);
		this->menuBackground->Draw(screen, 0, 0);
	}
}