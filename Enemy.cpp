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
    lastSeenTargetTime = 3.0f;
};

Vector2 Enemy::distanceToTarget(){
    return Vector2{-target->getWorldPos().x - worldPos.x + target->getScreenPos().x, 
                        -target->getWorldPos().y - worldPos.y + target->getScreenPos().y};
}

Vector2 Enemy::toTarget(){
    // return Vector2{-target->getWorldPos().x - worldPos.x + target->getScreenPos().x, 
    //                 -target->getWorldPos().y - worldPos.y + target->getScreenPos().y};
    return Vector2{target->pathToTarget(getCollisionRec(), target->getWorldPos()).x, target->pathToTarget(getCollisionRec(), target->getWorldPos()).y};
};

bool Enemy::getCanSeeTarget(float deltaTime){
    if (target->getAlive() == false) return false;
    bool boolValue = true;
    Vector2 lineStart[5] = {Vector2{getCollisionRec().x + getCollisionRec().width / 2, getCollisionRec().y + getCollisionRec().height / 2},
                            Vector2{getCollisionRec().x, getCollisionRec().y},
                            Vector2{getCollisionRec().x + getCollisionRec().width, getCollisionRec().y},
                            Vector2{getCollisionRec().x, getCollisionRec().y + getCollisionRec().height},
                            Vector2{getCollisionRec().x + getCollisionRec().width, getCollisionRec().y + getCollisionRec().height}};
    Vector2 lineEnd[5] = {Vector2{target->getCollisionRec().x + target->getCollisionRec().width / 2, target->getCollisionRec().y + target->getCollisionRec().height / 2},
                            Vector2{target->getCharacterRec().x, target->getCharacterRec().y},
                            Vector2{target->getCharacterRec().x + target->getCharacterRec().width, target->getCharacterRec().y},
                            Vector2{target->getCharacterRec().x, target->getCharacterRec().y + target->getCharacterRec().height},
                            Vector2{target->getCharacterRec().x + target->getCharacterRec().width, target->getCharacterRec().y + target->getCharacterRec().height}};

    // for (int i = 0; i < 5; i++){
    //     for (int j = 0; j < 5; j++){
    //         DrawLineEx(lineStart[j], lineEnd[i], 2.0f, BLUE);
    //     }
    // }
    // DrawLineEx(lineStart, lineEnd[0], 2.0f, BLUE);
    // Check if the line intersects with any of the walls
    lastSeenTargetTime += deltaTime;
    for (int i = 0; i < 12; i++){
        int visionValue = 0;
        // DrawLine(wallsRec[i].x, wallsRec[i].y, wallsRec[i].x + wallsRec[i].width, wallsRec[i].y, RED);
        // DrawLine(wallsRec[i].x, wallsRec[i].y, wallsRec[i].x, wallsRec[i].y + wallsRec[i].height, RED);
        // DrawLine(wallsRec[i].x + wallsRec[i].width, wallsRec[i].y, wallsRec[i].x + wallsRec[i].width, wallsRec[i].y + wallsRec[i].height, RED);
        // DrawLine(wallsRec[i].x, wallsRec[i].y + wallsRec[i].height, wallsRec[i].x + wallsRec[i].width, wallsRec[i].y + wallsRec[i].height, RED);
        for (int j = 0; j < 5; j++){
            for (int k = 0; k < 5; k++){
                if ((CheckCollisionLines(lineStart[k], lineEnd[j], Vector2 {wallsRec[i].x, wallsRec[i].y}, Vector2 {wallsRec[i].x + wallsRec[i].width, wallsRec[i].y}, NULL)
                    || CheckCollisionLines(lineStart[k], lineEnd[j], Vector2 {wallsRec[i].x, wallsRec[i].y}, Vector2 {wallsRec[i].x, wallsRec[i].y + wallsRec[i].height}, NULL)
                    || CheckCollisionLines(lineStart[k], lineEnd[j], Vector2 {wallsRec[i].x + wallsRec[i].width, wallsRec[i].y}, Vector2 {wallsRec[i].x + wallsRec[i].width, wallsRec[i].y + wallsRec[i].height}, NULL)
                    || CheckCollisionLines(lineStart[k], lineEnd[j], Vector2 {wallsRec[i].x, wallsRec[i].y + wallsRec[i].height}, Vector2 {wallsRec[i].x + wallsRec[i].width, wallsRec[i].y + wallsRec[i].height}, NULL))){
                    // return false;
                    visionValue++;
                    if (visionValue == 25){
                        if (lastSeenTargetTime > 1.5f){
                            boolValue = false;
                            return boolValue;
                        }
                    }
                    // boolValue = false;
                    // return boolValue;
                }
            }
        }
    }
    // return true;
    lastSeenTargetTime = 0.0f;
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
    Vector2 to_Target = distanceToTarget();
    // // Normalize the vector
    // to_Target = Vector2Normalize(to_Target);
    // multiply by speed
    if ((to_Target.x * to_Target.x + to_Target.y * to_Target.y) > (6.0f * 128.0f) * (6.0f * 128.0f) || attacking || !getAlive() || !getCanSeeTarget(deltaTime)){
        to_Target.x = no_speed;
        to_Target.y = no_speed;
    }
    else{
        to_Target = target->pathToTarget(getCollisionRec(), target->getWorldPos());
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