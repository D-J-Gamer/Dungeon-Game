#include "BaseCharacter.h"

BaseCharacter::BaseCharacter(){
}

Rectangle BaseCharacter::getCollisionRec(){
    return Rectangle{screenPos.x + 80, screenPos.y + 144, 112, 144 - 96};
};

void BaseCharacter::tick(float deltaTime){
    // update animation frame
    runningTime += deltaTime;
    if (!moving){
        if (types[0] == false){
            for (int i = 0; i < 2; i++) types[i] = false;
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
            for (int i = 0; i < 2; i++) types[i] = false;
            types[1] = true;
            frame = 0;
        };
        texture = movement;
        if (IsKeyDown(KEY_LEFT_SHIFT) && controlled) updateMoving = updateTimeRunning;
        else updateMoving = updateTimeMoving;
        if (runningTime >= updateMoving){
            frame++;
            if (frame >= maxMovingFrames) frame = 0;
            runningTime = 0.0f;
        }
    }

    Rectangle source = {frame * dimensions[0], 0.0f, dimensions[0] * rightleft, dimensions[1]};
    Rectangle dest = {screenPos.x + 16, screenPos.y - 48, scale * dimensions[0], scale * dimensions[1]};
    DrawTexturePro(texture, source, dest, (Vector2){0.0, 0.0}, 0.0f, WHITE);
};