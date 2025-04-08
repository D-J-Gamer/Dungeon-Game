#ifndef WALLS_H
#define WALLS_H
#include "Raylib\raylib\src\raylib.h"

struct Wall{
    Rectangle rec;
    float xMultiplier; // X tile
    float yMultiplier; // Y tile
    float xOffset; // X offset
    float yOffset; // Y offset
};

Rectangle getWall(float width, float height){
    return Rectangle{0.0, 0.0, width * 128, height * 128};
};

#endif