#ifndef TEXTURES_H
#define TEXTURES_H

#include "Raylib\raylib\src\raylib.h"

struct Textures{
    Texture2D idle;
    Texture2D movement;
    Texture2D attack;
    Texture2D death;
    int maxAttackFrames;
    float attackUpdateTime;
    int attackFrames_w_damage[2];
    int maxDeathFrames;
};

#endif