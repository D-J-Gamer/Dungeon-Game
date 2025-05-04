#include "Character.h"
#include "Raylib\raylib\src\raymath.h"
#include "Textures.h"
#include "Pathfinder.h"

Character::Character(int winWidth, int winHeight, Textures texture_s, float life_s, float damage_s, int wallCount, Rectangle walls[], Vector2 pos)
{
    texture = texture_s.idle;
    idle = texture_s.idle;
    movement = texture_s.movement;
    attack = texture_s.attack;
    maxAttackFrames = texture_s.maxAttackFrames;
    updateTimeAttack = texture_s.attackUpdateTime;
    death = texture_s.death;
    maxDeathFrames = texture_s.maxDeathFrames;
    dimensions[0] = (float)idle.width / (float)maxIdleFrames; //width
    dimensions[1] = (float)texture.height; //height
    screenPos = {static_cast<float>(winWidth)/2.0f - scale * dimensions[0] / 2.0f, 
                static_cast<float>(winHeight)/2.0f - scale * dimensions[1] / 2.0f};
    
    worldPos = {0.0f + screenPos.x - pos.x, 0.0f + screenPos.y - pos.y};
    controlled = true;
    life = life_s;
    damage = damage_s;
    distancedMoved = 0.0f;
    for (int i = 0; i < 2; i++) attackFrames_w_damage[i] = texture_s.attackFrames_w_damage[i];
}

void Character::tick(float deltaTime){
    Vector2 direction = {0.0, 0.0};
    worldPosLastFrame = worldPos;

    if (IsKeyDown(KEY_SPACE) && !attacking){
        attacking = true;
        frame = 0;
    }
    if (!attacking && getAlive()){
        if (IsKeyDown(KEY_W)) direction.y -= 1.0;
        if (IsKeyDown(KEY_S)) direction.y += 1.0;
        if (IsKeyDown(KEY_A)) direction.x -= 1.0;
        if (IsKeyDown(KEY_D)) direction.x += 1.0;
        if (Vector2Length(direction) != 0.0){
            direction = Vector2Normalize(direction);
            direction.x *= speed;
            direction.y *= speed;
            if (IsKeyDown(KEY_LEFT_SHIFT)) {
                direction.x *= 2.0f;
                direction.y *= 2.0f;
            }
            worldPos.x -= direction.x;
            worldPos.y -= direction.y;
            path->createGrid(getCollisionRec(), Vector2 {-worldPos.x, -worldPos.y});

            moving = true;
        }
        else moving = false;
    }

    BaseCharacter::tick(deltaTime);
}

Character::~Character(){
    // pathfinder.~Pathfinder();
    // delete pathfinder;
}