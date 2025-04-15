#include "Pathfinder.h"
#include "Raylib\raylib\src\raylib.h"

// const int map_height = 24*4;
// const int map_width = 32*4;

Pathfinder::Pathfinder(int newScale, int newWallCount, int newWidth, int newHeight, Rectangle* walls, int newTileSize){
    scale = newScale;
    wallCount = newWallCount;
    width = newWidth * scale;
    height = newHeight * scale;
    tileSize = newTileSize;
    wallsRec = new Rectangle[wallCount]{};
    for (int i = 0; i < wallCount; i++){
        wallsRec[i] = walls[i];
        wallsRec[i].x /= tileSize;
        wallsRec[i].y /= tileSize;
        wallsRec[i].width /= tileSize;
        wallsRec[i].height /= tileSize;
    }
    wallGrid = new int[height * width]{}; //y1{x1, x2, x3 ...} y2{x1, x2, x3 ...}
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // Calculate the 1D index for the 2D grid
            wallGrid[i * width + j] = 0;
        }
    }

    for (int i = 0; i < wallCount; i++) {
        for (int j = static_cast<int>(wallsRec[i].y) * scale; j < static_cast<int>(wallsRec[i].y + wallsRec[i].height) * scale; j++) {
            for (int k = static_cast<int>(wallsRec[i].x) * scale; k < static_cast<int>(wallsRec[i].x + wallsRec[i].width) * scale; k++) {
                if (j >= 0 && j < height && k >= 0 && k < width) {
                    wallGrid[j * width + k] = 1; // Mark as a wall
                }
            }
        }
    }
    gGrid = new int[height * width]{};
};
Pathfinder::~Pathfinder(/* args */){
    delete[] wallGrid;
    delete[] gGrid;
    // delete[] wallsRec;
    // delete[] wallCount;
};

Vector2 Pathfinder::nextStepPathfind(float xPos, float yPos, float xTarget, float yTarget){
    return Vector2{0.0f, 0.0f};
};

// int grid[map_height][map_width]{};

int Pathfinder::createGrid(bool wallsUpdated, int scale){
    if (!wallsUpdated){
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                // Calculate the 1D index for the 2D grid
                wallGrid[i * width + j] = 0;
            }
        }
    
        for (int i = 0; i < wallCount; i++) {
            for (int j = static_cast<int>(wallsRec[i].y); j < static_cast<int>(wallsRec[i].y + wallsRec[i].height); j++) {
                for (int k = static_cast<int>(wallsRec[i].x); k < static_cast<int>(wallsRec[i].x + wallsRec[i].width); k++) {
                    if (j >= 0 && j < height * scale && k >= 0 && k < width * scale) {
                        wallGrid[j * width + k] = 1; // Mark as a wall
                    }
                }
            }
        }

    }

    return 0;
};