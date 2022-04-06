#include "BulletManager.h"

namespace Snowy
{
	BulletManager::BulletManager() : bulletArray({})
	{
	}


	std::vector<Snowy::Kinematicbody> BulletManager::getBulletArray()
	{
		return bulletArray;
	}

}