

#ifndef BASECHARACTER_H
#define BASECHARACTER_H
#include "Raylib\raylib\src\raylib.h"


class BaseCharacter{
public:
    BaseCharacter();
    Rectangle getCollisionRec();
    Rectangle getCharacterRec();
    Rectangle getAttackRec();
    Vector2 getWorldPos(){return worldPos;}
    void undoMovement(){worldPos = worldPosLastFrame;}
    virtual void tick(float deltaTime);
    bool getAlive(){return alive;}
    void setAlive(bool isAlive){alive = isAlive;}
    void recieveDamage(float damage){life -= damage;}
    int getFrame(){return frame;}
    int getAttackFrames(int i){return attackFrames_w_damage[i];}
    float getDamage(){return damage;}
    bool getIsAttacking(){return attacking;}
    float getLife(){return life;}
protected:
    Texture2D texture{};
    Texture2D idle{};
    Texture2D movement{};
    Texture2D attack{};
    Texture2D death{};
    Vector2 screenPos{};
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};
    // 1: facing right, -1: facing left
    float rightleft = 1.f;
    // animation variables
    int frame = 0;
    int maxIdleFrames = 6;
    int maxMovingFrames = 10;
    int maxAttackFrames{};
    int maxDeathFrames{};
    float updateTimeIdle = 1.0f/8.0f;
    float updateTimeMoving = 1.0f/12.0f;
    float updateTimeRunning = 1.0f/24.0f;
    float updateTimeAttack{};
    int attackFrames_w_damage[2]{};
    float updateMoving = updateTimeMoving;
    float runningTime = 0.0f;
    bool moving = false;
    bool attacking = false;
    int speed = 4;
    float life{};
    float damage{};
    bool types[4] = {false/*idle*/, false/*moving*/, false/*attacking*/, false/*alive*/};
    int frametypes = 4;
    float dimensions[2]{};
    float width{};
    float height{};
    float scale = 8.0f;
    bool controlled{};
    bool isdeadlastframe = false;
    Color color = WHITE;
private:
    bool alive = true;
};

#endif