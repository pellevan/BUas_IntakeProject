#include "BulletManager.h"

#include "CollisionDetection.h"

namespace Snowy
{
	BulletManager::BulletManager(Tmpl8::Sprite* bulletSprite, int maxOnScreen, int bulletSpeed_min, int bulletSpeed_max)
	: maxOnScreen(maxOnScreen), bulletSpeed_min(bulletSpeed_min), bulletSpeed_max(bulletSpeed_max),
	  bulletSprite(bulletSprite), bulletArray({})
{
	}

    void BulletManager::SpawnBullets()
    {
        for (int i = 0; i < (maxOnScreen - static_cast<int>(bulletArray.size())); i++)
        {
            bulletArray.emplace_back(bulletSprite);
            bulletArray[bulletArray.size() - 1].SetPosition(static_cast<float>(IRand(ScreenWidth - 50)), static_cast<float>(IRand(300)));
            bulletArray[bulletArray.size() - 1].SetVelocity(0.f, static_cast<float>(rand() % bulletSpeed_min + bulletSpeed_max));
            bulletArray[bulletArray.size() - 1].setHitboxDiameter(25.f);
        }
    }

    void BulletManager::BorderCheck(float deltaTime)
	{
        for (auto iter = bulletArray.begin(); iter != bulletArray.end(); )
        {
            auto& bullet = *iter;
            bullet.SetPosition(bullet.GetPosition() + bullet.GetVelocity() * deltaTime);
            if (bullet.GetPosition().x > 0 &&
                bullet.GetPosition().x < ScreenWidth - 25 &&
                bullet.GetPosition().y > 0 &&
                bullet.GetPosition().y < ScreenHeight - 25)
            {
                ++iter;
            }
            else
            {
                iter = bulletArray.erase(iter);
            }
        }
	}

    bool BulletManager::DetectCollisions(Kinematicbody playerBody) const
    {
        for (const Snowy::Kinematicbody& bulletIT : bulletArray)
        {
            if (Snowy::detectCollision(bulletIT, playerBody)) return true;
        }

        return false;
    }

    void BulletManager::DrawBullets(Tmpl8::Surface* screen)
    {
        for (auto iter = bulletArray.begin(); iter != bulletArray.end(); )
        {
            auto& bullet = *iter;
            bullet.DrawBody(static_cast<int>(25.f), static_cast<int>(25.f), screen);
            /*screen->Line(bullet.GetPosition().x + bullet.getHitboxRadius(), bullet.GetPosition().y + bullet.getHitboxRadius(), bullet.GetPosition().x + bullet.getHitboxRadius(), ScreenHeight, 0xFF0000);*/
            ++iter;
        }
    }

    void BulletManager::ClearArray()
    {
        bulletArray.clear();
    }


	std::vector<Snowy::Kinematicbody> BulletManager::getBulletArray()
	{
		return bulletArray;
	}
}
