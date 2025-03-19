

#ifndef BASECHARACTER_H
#define BASECHARACTER_H
#include "C:/raylib/raylib/src/raylib.h"


class BaseCharacter{
public:
    BaseCharacter();
    Rectangle getCollisionRec();
    Vector2 getWorldPos(){return worldPos;}
    void undoMovement(){worldPos = worldPosLastFrame;}
    virtual void tick(float deltaTime);
protected:
Texture2D texture{};
    Texture2D idle{};
    Texture2D movement{};
    Vector2 screenPos{};
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};
    // 1: facing right, -1: facing left
    float rightleft = 1.f;
    // animation variables
    int frame = 0;
    int maxIdleFrames = 6;
    int maxMovingFrames = 10;
    float updateTimeIdle = 1.0f/8.0f;
    float updateTimeMoving = 1.0f/12.0f;
    float updateTimeRunning = 1.0f/24.0f;
    float updateMoving = updateTimeMoving;
    float runningTime = 0.0f;
    bool moving = false;
    int speed = 4;
    bool types[2] = {false/*idle*/, false/*moving*/};
    float dimensions[2]{};
    float width{};
    float height{};
    float scale = 8.0f;
    bool controlled{};
private:
};

#endif