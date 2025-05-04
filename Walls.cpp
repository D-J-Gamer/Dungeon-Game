#include "Walls.h"
#include "Raylib\raylib\src\raylib.h"


Rectangle getWall(float width, float height){
    return Rectangle{0.0, 0.0, width * 128, height * 128};
};