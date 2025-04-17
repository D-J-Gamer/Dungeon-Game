#ifndef PATHFINER_H
#define PATHFINER_H

#include "Raylib\raylib\src\raylib.h"
#include "Raylib\raylib\src\raymath.h"

class Pathfinder{
    public:
        Pathfinder(int newScale, int newWallCount, int newWidth, int newHeight, Rectangle walls[], int newTileSize);
        ~Pathfinder(/* args */);
        Vector2 nextStepPathfind(Rectangle collisionRec, Vector2 worldPos);
        int createGrid(Rectangle collisionRec, Vector2 worldPos);
        void drawGrid();
        int getGvalue(int x, int y){return gGrid[y * width + x];}
        int getHeight(){return height;}
        int getWidth(){return width;}
    private:
        int scale{};
        int wallCount{};
        int* wallGrid{};//Magic 24 * 24 for now
        float* gGrid{}; //Magic 24 * 24 for now
        int width{};
        int height{};
        Rectangle* wallsRec{}; //Magic 100 for now
        int tileSize{};
    };

// Pathfinder::Pathfinder(/* args */)
// {
// }



#endif