#pragma once
#include "kinematicbody.h"
#include "CollisionDetection.h"
#include "SDL_scancode.h"
#include "Menu.h"
#include "Bounds.h"

#include <map>
#include <vector>
#include <iostream>

namespace Tmpl8 {

class Surface;
class Sprite;
class Game
{
public:
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
	Surface* screen  = nullptr;
	Sprite* PlayerSprite = nullptr;
	
	Sprite* Background = nullptr;
	Snowy::Menu* GameMenu = nullptr;

	Snowy::Player* PlayerBody = nullptr;

	Snowy::Bounds* GameBounds = nullptr;

	std::map<std::string, int> movementStates =
	{
		{"m_up", 0},
		{"m_down", 0},
		{"m_left", 0},
		{"m_right", 0}
	};

	// Bullet properties
	Sprite* BulletSprite = nullptr;
	vec2 BulletSize = {};

	std::vector<Snowy::Bullet> bullets = {};

	const float movementSpeed = 5e2f;
	int difficultyBallAmount = 50; 
	int difficultyBallSpeed_Min = 100;
	int difficultyBallSpeed_Max = 150;

	bool gameOver = false;
};

}; // namespace Tmpl8