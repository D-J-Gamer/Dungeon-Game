#ifndef PATHFINER_H
#define PATHFINER_H

#include "Raylib\raylib\src\raylib.h"
#include "Raylib\raylib\src\raymath.h"

class Pathfinder{
public:
    Pathfinder(int newScale, int newWallCount, int newWidth, int newHeight, Rectangle* walls, int newTileSize);
    ~Pathfinder(/* args */);
    Vector2 nextStepPathfind(float xPos, float yPos, float xTarget, float yTarget);
    int createGrid(bool wallsUpdated, int scale);
private:
int scale{};
int wallCount{};
int* wallGrid;
int* gGrid;
int width{};
int height{};
Rectangle* wallsRec{};
int tileSize{};
};

// Pathfinder::Pathfinder(/* args */)
// {
// }



#endif