#include "Enemy.h"
#include "Raylib\raylib\src\raylib.h"
#include "Textures.h"
#include "Raylib\raylib\src\raymath.h"

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
    // 50%
    // 25%
    // 10%
    // 5%
    // 1%
    int randomValues[5] = {GetRandomValue(1,2), GetRandomValue(1, 4),
                            GetRandomValue(1, 10), GetRandomValue(1, 20),
                            GetRandomValue(1, 100)};
    
    // Temporary code
    randomValues[0] = 1;
    randomValues[1] = 2;

    for (int i = 1; i < 6; i++){
        if (i == randomValues[i - 1]){
            addItem(createRandomItem());
            // index++;
        }
        else break;
    }
    goldCount = GetRandomValue(1, 100) - index * 10;
    if (goldCount < 0) goldCount = 0;
};

Vector2 Enemy::distanceToTarget(){
    return Vector2{-target->getWorldPos().x - worldPos.x + target->getScreenPos().x, 
                        -target->getWorldPos().y - worldPos.y + target->getScreenPos().y};
}

Vector2 Enemy::toTarget(){
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

    // See vision lines
    // for (int i = 0; i < 5; i++){
    //     for (int j = 0; j < 5; j++){
    //         DrawLineEx(lineStart[j], lineEnd[i], 2.0f, BLUE);
    //     }
    // }

    // Check if the line intersects with any of the walls
    lastSeenTargetTime += deltaTime;
    for (int i = 0; i < 12; i++){
        int visionValue = 0;
        for (int j = 0; j < 5; j++){
            for (int k = 0; k < 5; k++){
                if ((CheckCollisionLines(lineStart[k], lineEnd[j], Vector2 {wallsRec[i].x, wallsRec[i].y}, Vector2 {wallsRec[i].x + wallsRec[i].width, wallsRec[i].y}, NULL)
                    || CheckCollisionLines(lineStart[k], lineEnd[j], Vector2 {wallsRec[i].x, wallsRec[i].y}, Vector2 {wallsRec[i].x, wallsRec[i].y + wallsRec[i].height}, NULL)
                    || CheckCollisionLines(lineStart[k], lineEnd[j], Vector2 {wallsRec[i].x + wallsRec[i].width, wallsRec[i].y}, Vector2 {wallsRec[i].x + wallsRec[i].width, wallsRec[i].y + wallsRec[i].height}, NULL)
                    || CheckCollisionLines(lineStart[k], lineEnd[j], Vector2 {wallsRec[i].x, wallsRec[i].y + wallsRec[i].height}, Vector2 {wallsRec[i].x + wallsRec[i].width, wallsRec[i].y + wallsRec[i].height}, NULL))){
                    visionValue++;
                    if (visionValue == 25){
                        if (lastSeenTargetTime > 1.5f){
                            boolValue = false;
                            return boolValue;
                        }
                    }
                }
            }
        }
    }
    lastSeenTargetTime = 0.0f;
    return boolValue;
}

void Enemy::tick(float deltaTime){
    worldPosLastFrame = worldPos;

    int no_speed = 0;

    if (getAlive() == false){
        //
    }
    else {
        // get toTarget
        Vector2 to_Target = distanceToTarget();
        if ((to_Target.x * to_Target.x + to_Target.y * to_Target.y) < (1.0f * 128.0f) * (1.0f * 128.0f)){
            attacking = true;
        }
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
    }
    screenPos.x = worldPos.x + target->getWorldPos().x;
    screenPos.y = worldPos.y + target->getWorldPos().y;

    if (CheckCollisionRecs(getCollisionRec(), target->getCollisionRec()) && !getAlive() && index > 0){
        color = BLUE;
        if(IsKeyPressed(KEY_E)){
            openInventory = true;
        }
    }
    else if (!getAlive()){
        color = WHITE;
    }

    BaseCharacter::tick(deltaTime);
};