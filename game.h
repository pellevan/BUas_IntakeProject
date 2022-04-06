#pragma once
#include "kinematicbody.h"
#include "CollisionDetection.h"
#include "SDL_scancode.h"
#include "Menu.h"
#include "Bounds.h"

#include <map>
#include <vector>
#include <iostream>

#include "HUD.h"
#include "Timer.h"

namespace Tmpl8 {

class Surface;
class Sprite;
class Game
{
public:
	Game();

	void SetTarget( Surface* surface ) { screen = surface; }
	void Init();
	void Shutdown() const;
	void Tick( float deltaTime );
	void MouseUp( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseDown( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseMove( int x, int y ) { /* implement if you want to detect mouse movement */ }
	void KeyUp(const SDL_Scancode key);
	void KeyDown(const SDL_Scancode key);

	void Movement(float deltaTime) const;
	void CollisionDetection();
	void DrawBullets(float deltaTime);

	void EnemySpawn();

	void RenderEntities();

	bool shutDown = false;
private:
	// All member variables initialized in Game::Init() or KeyUp() / KeyDown() functions
	// ---------------------------------------------------------------------------------

	// Self explanatory
	bool gameOver = false;

	// Timer
	Snowy::Timer* gameover_timer = nullptr;

	// Screen / window we're drawing on in this game class
	Surface* screen  = nullptr;

	// The sprite of the penguin/player (controllable)
	Sprite* PlayerSprite = nullptr;

	// The snowy background image
	Sprite* Background = nullptr;

	// The sprite for the game over screen
	Sprite* GameOverImage = nullptr;

	// Menu object of the main menu
	Snowy::Menu* GameMenu = nullptr;

	// The kinematicbody2D of the player
	Snowy::Player* PlayerBody = nullptr;

	// Bounds object for the current bounds of the game
	Snowy::Bounds* GameBounds = nullptr;

	// HUD object for the game (health bar)
	Snowy::HUD* CurrentHUD = nullptr;

	// Map for the state of button presses (only WASD)
	std::map<std::string, int> movementStates =
	{
		{"m_up", 0},
		{"m_down", 0},
		{"m_left", 0},
		{"m_right", 0}
	};

	// The sprite of the snowflake/bullet
	Sprite* BulletSprite = nullptr;

	// Size of the bullets (x,y)
	vec2 BulletSize = {};

	// The sprite of the fireball bullet
	Sprite* FireballSprite = nullptr;

	// Vector / array object for the current snowflakes/bullets on the screen
	std::vector<Snowy::Bullet> bullets = {};

	std::vector<Snowy::UniqueBullets> uniqueBullets = {};

	// Difficulty settings
	// -------------------
	const float movementSpeed = 5e2f;
	int difficultyBallAmount = 120; 
	int difficultyBallSpeed_Min = 100;
	int difficultyBallSpeed_Max = 150;
};

}; // namespace Tmpl8