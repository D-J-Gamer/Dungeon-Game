#include "Enemy.h"
#include "Raylib\raylib\src\raylib.h"
#include "Textures.h"
#include "Raylib\raylib\src\raymath.h"
// #include "src\Pathfinder.h"


Enemy::Enemy(Vector2 pos, Textures texture_s, float life_s, float damage_s)
{
    texture = texture_s.idle;
    idle = texture_s.idle;
    movement = texture_s.movement;
    attack = texture_s.attack;
    maxAttackFrames = texture_s.maxAttackFrames;
    updateTimeAttack = texture_s.attackUpdateTime;
    death = texture_s.death;
    maxDeathFrames = texture_s.maxDeathFrames;
    worldPos = pos;
    dimensions[0] = static_cast<float>(idle.width) / static_cast<float>(maxIdleFrames); //width
    dimensions[1] = static_cast<float>(texture.height); //height
    controlled = false;
    life = life_s;
    damage = damage_s;
    for (int i = 0; i < 2; i++) attackFrames_w_damage[i] = texture_s.attackFrames_w_damage[i];
};

Vector2 Enemy::toTarget(){
    return Vector2{-target->getWorldPos().x - worldPos.x + target->getScreenPos().x, 
                    -target->getWorldPos().y - worldPos.y + target->getScreenPos().y};                    
};

bool Enemy::getCanSeeTarget(){
    if (target->getAlive() == false) return false;
    bool boolValue = true;
    Vector2 line[2] = {Vector2{getCollisionRec().x, getCollisionRec().y}, Vector2{target->getCollisionRec().x, target->getCollisionRec().y}};
    DrawLineEx(line[0], line[1], 2.0f, BLUE);
    // Check if the line intersects with any of the walls
    for (int i = 0; i < 12; i++){
        DrawLine(wallsRec[i].x, wallsRec[i].y, wallsRec[i].x + wallsRec[i].width, wallsRec[i].y, RED);
        DrawLine(wallsRec[i].x, wallsRec[i].y, wallsRec[i].x, wallsRec[i].y + wallsRec[i].height, RED);
        DrawLine(wallsRec[i].x + wallsRec[i].width, wallsRec[i].y, wallsRec[i].x + wallsRec[i].width, wallsRec[i].y + wallsRec[i].height, RED);
        DrawLine(wallsRec[i].x, wallsRec[i].y + wallsRec[i].height, wallsRec[i].x + wallsRec[i].width, wallsRec[i].y + wallsRec[i].height, RED);
        if (CheckCollisionLines(line[0], line[1], Vector2 {wallsRec[i].x, wallsRec[i].y}, Vector2 {wallsRec[i].x + wallsRec[i].width, wallsRec[i].y}, NULL)
            || CheckCollisionLines(line[0], line[1], Vector2 {wallsRec[i].x, wallsRec[i].y}, Vector2 {wallsRec[i].x, wallsRec[i].y + wallsRec[i].height}, NULL)
            || CheckCollisionLines(line[0], line[1], Vector2 {wallsRec[i].x + wallsRec[i].width, wallsRec[i].y}, Vector2 {wallsRec[i].x + wallsRec[i].width, wallsRec[i].y + wallsRec[i].height}, NULL)
            || CheckCollisionLines(line[0], line[1], Vector2 {wallsRec[i].x, wallsRec[i].y + wallsRec[i].height}, Vector2 {wallsRec[i].x + wallsRec[i].width, wallsRec[i].y + wallsRec[i].height}, NULL)){
            // return false;
            boolValue = false;
        }
    }
    // return true;
    return boolValue;

    // Vector2 theTargetDirection = Vector2Normalize(toTarget());
    // Vector2 distanceToCheck = Vector2{abs(target->getWorldPos().x - worldPos.x), abs(target->getWorldPos().y - worldPos.y)};
    // for (Vector2 i = {-target->getWorldPos().x, -target->getWorldPos().y}; distanceToCheck.x < 0.0f || distanceToCheck.y < 0.0f ;distanceToCheck = {distanceToCheck.x - abs(theTargetDirection.x), distanceToCheck.y - abs(theTargetDirection.y)}){
    //     for (int k = 0; k < wallCount; k++){
    //         if (CheckCollisionRecs(wallsRec[k], Rectangle {i.x, i.y, 1, 1})){
    //             return false;
    //         }
    //     }
    //     i = {i.x + theTargetDirection.x, i.y + theTargetDirection.y};
    // }
    // return false;
}

void Enemy::tick(float deltaTime){
    // if (!getAlive()) return;
    worldPosLastFrame = worldPos;

    int no_speed = 0;

    // get toTarget
    Vector2 to_Target = toTarget();
    // // Normalize the vector
    // to_Target = Vector2Normalize(to_Target);
    // multiply by speed
    if ((to_Target.x * to_Target.x + to_Target.y * to_Target.y) > (6.0f * 128.0f) * (6.0f * 128.0f) || attacking || !getAlive() || !getCanSeeTarget()){
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
    else if (to_Target.x < 0) rightleft = -1.f;
    if (to_Target.x != 0 || to_Target.y != 0) moving = true;
    else moving = false;
    if (worldPosLastFrame != worldPos) moving = true;
    else moving = false;
    screenPos.x = worldPos.x + target->getWorldPos().x;
    screenPos.y = worldPos.y + target->getWorldPos().y;

    BaseCharacter::tick(deltaTime);
};