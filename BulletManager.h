#pragma once
#include <vector>

#include "kinematicbody.h"

namespace Snowy
{
	class BulletManager
	{
	public:
		BulletManager();

		std::vector<Snowy::Kinematicbody> getBulletArray();

	private:
		std::vector<Snowy::Kinematicbody> bulletArray;
	};
}
