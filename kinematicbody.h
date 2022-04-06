#pragma once

#include "template.h"
#include "surface.h"

#include <vector>
#include "hitbox.h"
#include <string>

// Forward declarations (useless)
namespace Tmpl8 {
	class vec2;
	class Surface;
	class Sprite;
}

namespace Snowy {
	class Hitbox;
	/** Kinematicbody2D
	* \brief An object with a position, sprite, hitbox and velocity
	**/
	class Kinematicbody
	{
	public:
		// Constructor of a Kinematicbody(2D) object
		explicit Kinematicbody(Tmpl8::Sprite* addSprite, float xPos = 0.f, float yPos = 0.f);

		// Setter for the sprite of the body
		void SetSprite(Tmpl8::Sprite* newSprite);

		// Getter for the active sprite of the body
		const Tmpl8::Sprite* GetSprite() const; 


		// Setter(s) for position
		void SetPosition(Tmpl8::vec2 newPos);
		void SetPosition(float x, float y);

		// Function to add certain values to position
		void AddToPosition(Tmpl8::vec2 changePos);
		void AddToPosition(float xChange, float yChange);

		// Getter for the current position of the body
		Tmpl8::vec2 GetPosition();


		// Setter(s) for velocity
		void SetVelocity(Tmpl8::vec2 newVel);
		void SetVelocity(float x, float y);

		// Function to add certain values to velocity
		void AddToVelocity(Tmpl8::vec2 changePos);
		void AddToVelocity(float xChange, float yChange);

		// Getter for the current velocity of the body
		Tmpl8::vec2 GetVelocity();

		// Draw the body on a Surface (screen) with the current position
		void DrawBody(int xScale, int yScale, Tmpl8::Surface* a_Target);

		// Setter for the diameter of its hitbox
		void setHitboxDiameter(float newDiameter);

		// Getter for the diameter of the hitbox
		float getHitboxDiameter();

		// Getter for the radius of the hitbox
		float getHitboxRadius();


	private: 
		// Hitbox of the body
		Snowy::Hitbox hitbox;

		// Sprite of the body
		Tmpl8::Sprite* Sprite;
		
		// Position of the body
		Tmpl8::vec2 Position;

		// Velocity of the body
		Tmpl8::vec2 Velocity;
	};

	class Player : public Kinematicbody
	{
	public:
		// Constructor of a Player object
		explicit Player(Tmpl8::Sprite* addSprite, float xPos = 0.f, float yPos = 0.f);

		// Getter for the direction the player is moving
		int getDirection();

		// Setter for the direction the player is moving
		void setDirection(int newDirection);

		void ResetHP();
		void LoseHP();
		int GetHP();
	private:
		// Whether the player is alive or not
		bool isAlive;

		// The direction the player is moving
		int facingDirection;

		// HP
		int HP;
	};

	class Bullet : public Kinematicbody
	{
	public:
		// Constructor of a Bullet object
		Bullet(Tmpl8::Sprite* addSprite, float xPos = 0.f, float yPos = 0.f) : Kinematicbody(addSprite, xPos, yPos)
		{
			this->setHitboxDiameter(25.f);
		}
	};

	class UniqueBullets : public Kinematicbody
	{
	public:
		// Constructor of a Powerup objects
		UniqueBullets(Tmpl8::Sprite* addSprite, int type, float xPos = 0.f, float yPos = 0.f) : Kinematicbody(addSprite, xPos, yPos),
			typeID(type)
		{
			switch(typeID)
			{
			case 0:
				typeName = "Shield";
				break;
			case 1:
				typeName = "Fireball";
				break;
			case 2:
				typeName = "Heart";
				break;
			default:
				break;
			}
		}

		void SetTypeID(int newType);
		int GetTypeID() const
		{
			return this->typeID;
		}
	private:
		// Type of the powerup
		int typeID;
		std::string typeName;
	};
}


