#include "CollisionDetection.h"

namespace Snowy {
    bool detectCollision(Bullet bullet, Kinematicbody playerBody)
    {
        // Distance between bullet and player
        const float distanceCircles = 
            powf((bullet.GetPosition().x + bullet.getHitboxRadius()) - (playerBody.GetPosition().x + playerBody.getHitboxRadius()), 2) +
            powf((bullet.GetPosition().y + bullet.getHitboxRadius()) - (playerBody.GetPosition().y + playerBody.getHitboxRadius()), 2);

        if (distanceCircles < powf(playerBody.getHitboxRadius() + bullet.getHitboxRadius(), 2)) {
            return true;
        }
        return false;
    }
}

