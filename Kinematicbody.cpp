#include "kinematicbody.h"

namespace Snowy {
	Kinematicbody::Kinematicbody(Tmpl8::Sprite* addSprite, float xPos, float yPos) : Sprite(addSprite)
	{
		this->Position.x = 0.f;
		this->Position.y = 0.f;

		this->Velocity.x = 0.f;
		this->Velocity.y = 0.f;
	}

	void Kinematicbody::SetSprite(Tmpl8::Sprite* newSprite)
	{
		this->Sprite = newSprite;
	}

	const Tmpl8::Sprite* Kinematicbody::GetSprite() const
	{
		return this->Sprite;
	}

	void Kinematicbody::SetPosition(Tmpl8::vec2 newPos)
	{
		this->Position = newPos;
	}

	void Kinematicbody::SetPosition(float x, float y)
	{
		this->Position.x = x;
		this->Position.y = y;
	}

	void Kinematicbody::AddToPosition(Tmpl8::vec2 changePos)
	{
		this->Position += changePos;
	}

	void Kinematicbody::AddToPosition(const float xChange, const float yChange)
	{
		this->Position.x += xChange;
		this->Position.y += yChange;
	}
	
	Tmpl8::vec2 Kinematicbody::GetPosition()
	{
		return this->Position;
	}

	void Kinematicbody::SetVelocity(Tmpl8::vec2 newVel)
	{
		this->Velocity = newVel;
	}

	void Kinematicbody::SetVelocity(const float x, const float y)
	{
		this->Velocity.x = x;
		this->Velocity.y = y;
	}

	void Kinematicbody::AddToVelocity(Tmpl8::vec2 changePos)
	{
		this->Velocity += changePos;
	}

	void Kinematicbody::AddToVelocity(const float xChange, const float yChange)
	{
		this->Velocity.x += xChange;
		this->Velocity.y += yChange;
	}

	Tmpl8::vec2 Kinematicbody::GetVelocity()
	{
		return this->Velocity;
	}

	void Kinematicbody::DrawBody(int xScale, int yScale, Tmpl8::Surface* a_Target)
	{
		// this->Sprite->DrawScaled(static_cast<int>(this->Position.x), static_cast<int >(this->Position.y), xScale, yScale, a_Target);
		this->Sprite->Draw(a_Target, static_cast<int>(this->Position.x), static_cast<int>(this->Position.y)); 
	}

	void Kinematicbody::setHitboxDiameter(float newDiameter)
	{
		hitbox.setDiameter(newDiameter);
	}

	float Kinematicbody::getHitboxDiameter()
	{
		return hitbox.getDiameter();
	}

	float Kinematicbody::getHitboxRadius()
	{
		return hitbox.getRadius();
	}

	Player::Player(Tmpl8::Sprite* addSprite, float xPos, float yPos): Kinematicbody(addSprite, xPos, yPos),
	                                                                  isAlive(true), facingDirection(1), HP(3)
	{
	}

	int Player::getDirection()
	{
		return this->facingDirection;
	}
	void Player::setDirection(int newDirection)
	{
		this->facingDirection = newDirection;
	}

	void Player::ResetHP()
	{
		HP = 3;
	}

	void Player::LoseHP()
	{
		--HP;
	}

	int Player::GetHP()
	{
		return HP;
	}

	void UniqueBullets::SetTypeID(int newType)
	{
		typeID = newType;
	}


};