#include "CollisionDetection.h"

namespace Snowy {
    bool detectCollision(Kinematicbody bullet, Kinematicbody playerBody)
    {
        // Calculate distance distance between bullet and player
        const float distanceCircles = 
            powf((bullet.GetPosition().x + bullet.getHitboxRadius()-10) - (playerBody.GetPosition().x + playerBody.getHitboxRadius()), 2) +
            powf((bullet.GetPosition().y + bullet.getHitboxRadius()) - (playerBody.GetPosition().y + playerBody.getHitboxRadius()), 2);

        // No sqrtf() in above calculation, so we use powf() here again for the result
        if (distanceCircles < powf(playerBody.getHitboxRadius() + bullet.getHitboxRadius(), 2)) {
            return true;
        }
        return false;
    }
}

