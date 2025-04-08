#include "Prop.h"

Prop::Prop(Texture2D* tex, Vector2 pos, float base): worldPos(pos){
    for (int i = 0; i < maxFrames; i++) texture[i] = tex[i];
    worldPos = pos;
    baseFooting = base;
}

void Prop::Render(Vector2 playerPos){
    screenPos.x = worldPos.x + playerPos.x;
    screenPos.y = worldPos.y + playerPos.y;
    DrawTextureEx(texture[frame], screenPos, 0.0f, scale, WHITE);
}

void Prop::updateAnimation(float deltaTime){
    runningTime += deltaTime;
    if (runningTime >= updateTime){
        frame++;
        if (frame >= maxFrames) frame = 0;
        runningTime = 0.0f;
    }
}

Rectangle Prop::GetCollisionRec(){
    return Rectangle{screenPos.x, screenPos.y + texture[frame].height * scale * (1.0f - baseFooting), texture[frame].width * scale, texture[frame].height * scale * baseFooting};
}