#include "Enemy.h"
#include "C:/raylib/raylib/src/raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idleTexture, Texture2D movementTexture)
{
    texture = idleTexture;
    idle = idleTexture;
    movement = movementTexture;
    worldPos = pos;
    dimensions[0] = static_cast<float>(idle.width) / static_cast<float>(maxIdleFrames); //width
    dimensions[1] = static_cast<float>(texture.height); //height
    controlled = false;
};

Vector2 Enemy::toTarget(){
    return Vector2{-target->getWorldPos().x - worldPos.x + target->getScreenPos().x, 
                    -target->getWorldPos().y - worldPos.y + target->getScreenPos().y};
};

void Enemy::tick(float deltaTime){
    worldPosLastFrame = worldPos;

    int no_speed = 0;

    // get toTarget
    Vector2 to_Target = toTarget();
    // Normalize the vector
    // to_Target = Vector2Normalize(to_Target);
    // multiply by speed
    if ((to_Target.x * to_Target.x + to_Target.y * to_Target.y) < 1){
        to_Target.x = no_speed;
        to_Target.y = no_speed;
    }
    else{
        // Normalize the vector
        to_Target = Vector2Normalize(to_Target);
        // multiply by speed
        to_Target.x *= speed;
        to_Target.y *= speed;
    };
    // Move the enemy (change worldPos)
    worldPos.x += to_Target.x;
    worldPos.y += to_Target.y;
    if (to_Target.x > 0) rightleft = 1.f;
    else if (to_Target.x > 0) rightleft = -1.f;
    // if (to_Target.x != 0 || to_Target.y != 0) moving = true;
    // else moving = false;
    if (worldPosLastFrame != worldPos) moving = true;
    else moving = false;

    screenPos.x = worldPos.x + target->getWorldPos().x;
    screenPos.y = worldPos.y + target->getWorldPos().y;

    BaseCharacter::tick(deltaTime);
};