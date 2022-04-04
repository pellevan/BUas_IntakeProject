#pragma once

namespace Snowy {
	class Hitbox
	{
	public:
		Hitbox(float hitboxDiameter = 0.f);
		void setDiameter(float newDiameter);
		float getDiameter();
		float getRadius();

	private:
		float diameter;
		float radius;
	};
}