#ifdef PATHFINER_H
#define PATHFINER_H

#include "Raylib\raylib\src\raylib.h"
#include "Raylib\raylib\src\raymath.h"

Vector2 nextStepPathfind(float xPos, float yPos, float xTarget, float yTarget);

extern int map_height = 24*4;
extern int map_width = 32*4;
int createGrid[map_height][map_width]();




#endif