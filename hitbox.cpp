#include "hitbox.h"

namespace Snowy {
	Hitbox::Hitbox(float hitboxDiameter) : diameter(hitboxDiameter), radius(this->diameter / 2)
	{
	}
	void Hitbox::setDiameter(float newDiameter)
	{
		this->diameter = newDiameter;
		this->radius = this->diameter / 2;
	}

	float Hitbox::getDiameter()
	{
		return this->diameter;
	}

	float Hitbox::getRadius()
	{
		return this->radius;
	}
}