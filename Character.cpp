#include "Character.h"
#include "Raylib\raylib\src\raymath.h"
#include "Textures.h"

Character::Character(int winWidth, int winHeight, Textures texture_s, float life_s, float damage_s){
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
    worldPos = {0.0, 0.0};
    controlled = true;
    life = life_s;
    damage = damage_s;
    for (int i = 0; i < 2; i++) attackFrames_w_damage[i] = texture_s.attackFrames_w_damage[i];
}

void Character::tick(float deltaTime){
    // if (!getAlive()) return;
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
            // if (direction.x > 0) rightleft = 1.f;
            // else if (direction.x < 0) rightleft = -1.f;
            moving = true;
        }
        else moving = false;
    }

    BaseCharacter::tick(deltaTime);

    // Rectangle source = {frame * dimensions[0], 0.0f, dimensions[0] * rightleft, dimensions[1]};
    // Rectangle dest = {screenPos.x + 16, screenPos.y - 48, scale * dimensions[0], scale * dimensions[1]};
    // DrawTexturePro(texture, source, dest, (Vector2){0.0, 0.0}, 0.0f, WHITE);
}