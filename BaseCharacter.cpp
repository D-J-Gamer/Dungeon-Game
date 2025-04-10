#include "BaseCharacter.h"

BaseCharacter::BaseCharacter(){
}

Rectangle BaseCharacter::getCollisionRec(){
    return Rectangle{screenPos.x + 80 + 10, screenPos.y + 144, 112 - 20, 144 - 96};
};

Rectangle BaseCharacter::getCharacterRec(){
    return Rectangle{screenPos.x + 80, screenPos.y + 48, 112, 144};
};

Rectangle BaseCharacter::getAttackRec(){
    if (rightleft == 1.f) return Rectangle{screenPos.x + 80 - 112 + 80, screenPos.y - 104 + 144, 112 + 112, 144};
    else return Rectangle{screenPos.x - 80 + 80, screenPos.y - 104 + 144, 112 + 112, 144};
};

void BaseCharacter::tick(float deltaTime){
    // update animation frame
    runningTime += deltaTime;
    if (alive){
        if (life <= 0.0f) alive = false;
        if (!attacking){
            if (!moving){
                if (types[0] == false){
                    for (int i = 0; i < frametypes; i++) types[i] = false;
                    types[0] = true;
                    frame = 0;
                };
                texture = idle;
                if (runningTime >= updateTimeIdle){
                    frame++;
                    if (frame >= maxIdleFrames) frame = 0;
                    runningTime = 0.0f;
                }
            }
            else{
                if (types[1] == false){
                    for (int i = 0; i < frametypes; i++) types[i] = false;
                    types[1] = true;
                    frame = 0;
                };
                texture = movement;
                if (worldPosLastFrame.x > worldPos.x) rightleft = -1.f;
                else if (worldPosLastFrame.x < worldPos.x) rightleft = 1.f;
                if (controlled && (worldPosLastFrame.x != worldPos.x)) rightleft *= -1.f;
                if (IsKeyDown(KEY_LEFT_SHIFT) && controlled) updateMoving = updateTimeRunning;
                else updateMoving = updateTimeMoving;
                if (runningTime >= updateMoving){
                    frame++;
                    if (frame >= maxMovingFrames) frame = 0;
                    runningTime = 0.0f;
                }
            }
        }
        else{
            if (types[2] == false){
                for (int i = 0; i < frametypes; i++) types[i] = false;
                types[2] = true;
                frame = 0;
            };
            texture = attack;
            if (runningTime >= updateTimeAttack){
                frame++;
                if (frame >= maxAttackFrames) {
                    frame = 0;
                    attacking = false;
                }
                runningTime = 0.0f;
            }
        }
    }
    else{
        if (types[3] == false){
            for (int i = 0; i < frametypes; i++) types[i] = false;
            types[3] = true;
            frame = 0;
        };
        texture = death;
        attacking = false;
        if (!isdeadlastframe){
            if (runningTime >= updateTimeIdle){
                frame++;
                if (frame >= maxDeathFrames) {
                    frame--;
                    isdeadlastframe = true;
                }
                runningTime = 0.0f;
            }
        }
    }
    Rectangle source = {frame * dimensions[0], 0.0f, dimensions[0] * rightleft, dimensions[1]};
    Rectangle dest = {screenPos.x + 16, screenPos.y - 48, scale * dimensions[0], scale * dimensions[1]};
    DrawTexturePro(texture, source, dest, (Vector2){0.0, 0.0}, 0.0f, WHITE);
};