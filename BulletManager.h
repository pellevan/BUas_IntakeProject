#pragma once
#include <vector>

#include "kinematicbody.h"

namespace Snowy
{
	class BulletManager
	{
	public:
		BulletManager(Tmpl8::Sprite* bulletSprite, int maxOnScreen, int bulletSpeed_min, int bulletSpeed_max);

		void SpawnBullets();
		void BorderCheck(float deltaTime);
		bool DetectCollisions(Kinematicbody playerBody) const;
		void DrawBullets(Tmpl8::Surface* screen);
		void ClearArray();

		std::vector<Snowy::Kinematicbody> getBulletArray();

	private:
		int maxOnScreen;
		int bulletSpeed_min;
		int bulletSpeed_max;

		Tmpl8::Sprite* bulletSprite;
		std::vector<Snowy::Kinematicbody> bulletArray;
	};
}
