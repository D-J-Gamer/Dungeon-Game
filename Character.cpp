#include "Character.h"
#include "C:/raylib/raylib/src/raymath.h"

Character::Character(int winWidth, int winHeight, Texture2D idleTexture, Texture2D movementTexture){
    texture = idleTexture;
    idle = idleTexture;
    movement = movementTexture;
    dimensions[0] = (float)idle.width / (float)maxIdleFrames; //width
    dimensions[1] = (float)texture.height; //height
    screenPos = {static_cast<float>(winWidth)/2.0f - scale * dimensions[0] / 2.0f, 
                static_cast<float>(winHeight)/2.0f - scale * dimensions[1] / 2.0f};
    worldPos = {0.0, 0.0};
    controlled = true;

}

void Character::tick(float deltaTime){
    Vector2 direction = {0.0, 0.0};
    worldPosLastFrame = worldPos;
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
        if (direction.x > 0) rightleft = 1.f;
        else if (direction.x < 0) rightleft = -1.f;
        moving = true;
    }
    else moving = false;

    BaseCharacter::tick(deltaTime);

    Rectangle source = {frame * dimensions[0], 0.0f, dimensions[0] * rightleft, dimensions[1]};
    Rectangle dest = {screenPos.x + 16, screenPos.y - 48, scale * dimensions[0], scale * dimensions[1]};
    DrawTexturePro(texture, source, dest, (Vector2){0.0, 0.0}, 0.0f, WHITE);
}