#include "Pathfinder.h"
#include "Raylib\raylib\src\raylib.h"
#include <string>
#include <iostream>

struct point{
    int x;
    int y;
};

// Pathfinder
Pathfinder::Pathfinder(int newScale, int newWallCount, int newWidth, int newHeight, Rectangle walls[], int newTileSize, int windowScaleX, int windowScaleY) {
    scale = newScale;
    wallCount = newWallCount;
    width = newWidth * scale * windowScaleX;
    height = newHeight * scale * windowScaleY;
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
        for (int j = static_cast<int>(wallsRec[i].y) * scale - 6; j < static_cast<int>(wallsRec[i].y + wallsRec[i].height) * scale - 6; j++) {
            for (int k = static_cast<int>(wallsRec[i].x) * scale - 5; k < static_cast<int>(wallsRec[i].x + wallsRec[i].width) * scale - 5; k++) {
                if (j >= 0 && j < height && k >= 0 && k < width) {
                    wallGrid[j * width + k] = 1; // Mark as a wall
                }
            }
        }
    }
    gGrid = new float[height * width]{};
};
Pathfinder::~Pathfinder() {
    if (wallGrid != nullptr) {
        // delete[] wallGrid;
        wallGrid = nullptr;
    }
    if (gGrid != nullptr) {
        delete[] gGrid;
        gGrid = nullptr;
    }
    if (wallsRec != nullptr) {
        delete[] wallsRec;
        wallsRec = nullptr;
    }
}

Vector2 Pathfinder::nextStepPathfind(Rectangle collisionRec, Vector2 worldPos){
    int x = static_cast<int>((collisionRec.x - worldPos.x) * scale / tileSize);
    int y = static_cast<int>((collisionRec.y - worldPos.y) * scale / tileSize);
    int w = static_cast<int>(collisionRec.width * scale / tileSize);
    if (w < 1) w = 1;
    int h = static_cast<int>(collisionRec.height * scale / tileSize);
    if (h < 1) h = 1;

    point nodes[height * width]{};
    point nextStep = point{0, 0};
    int nodeCount = 0;
    for (int i = y; i < y + h; i++) {
        for (int j = x; j < x + w; j++) {
            if (i >= 0 && i < height && j >= 0 && j < width) {
                nodes[nodeCount] = point{j, i};
                nodeCount++;
            }
        }
    }
    // {x1, y1} {x2, y1} {x3, y1} {x4, y1}
    // {x1, y2} {x2, y2} {x3, y2} {x4, y2}
    // {x1, y3} {x2, y3} {x3, y3} {x4, y3}
    // w = width * scale
    // h = height * scale
    float currentDistance = 998.0f;
    bool canGoUP = true;
    bool canGoLEFT = true;
    bool canGoRIGHT = true;
    bool canGoDOWN = true;
    // up
    for (int i = 0; i < w; i++){
        if (wallGrid[(nodes[i].y - 1) * width + nodes[i].x] != 1){
            if (gGrid[(nodes[i].y - 1) * width + nodes[i].x] < currentDistance){
                currentDistance = gGrid[(nodes[i].y - 1) * width + nodes[i].x];
                nextStep = point{0, -1};
            }
        }
        if (wallGrid[(nodes[i].y - 1) * width + nodes[i].x] == 1){
            canGoUP = false;
        }
    }
    // left
    for (int i = 0; i < h; i++){
        if (wallGrid[nodes[i * width].y * width + nodes[i * width].x - 1] != 1){
            if (gGrid[nodes[i * width].y * width + nodes[i * width].x - 1] < currentDistance){
                currentDistance = gGrid[nodes[i * width].y * width + nodes[i * width].x - 1];
                nextStep = point{-1, 0};
            }
        }
        if (wallGrid[nodes[i * width].y * width + nodes[i * width].x - 1] == 1){
            canGoLEFT = false;
        }
    }
    // right
    for (int i = 0; i < h; i++){
        if (wallGrid[nodes[(i * w) + w - 1].y * width + nodes[(i * w) + w - 1].x + 1] != 1){
            if (gGrid[nodes[i * w + w - 1].y * width + nodes[i * w + w - 1].x + 1] < currentDistance){
                currentDistance = gGrid[nodes[i * w + w - 1].y * width + nodes[i * w + w - 1].x + 1];
                nextStep = point{1, 0};
            }
        }
        if (wallGrid[nodes[(i * w) + w - 1].y * width + nodes[(i * w) + w - 1].x + 1] == 1){
            canGoRIGHT = false;
        }
    }
    // down
    for (int i = 0; i < w; i++){
        if (wallGrid[(nodes[i + (h - 1) * w].y + 1) * width + nodes[i + (h - 1) * w].x] != 1){
            if (gGrid[(nodes[i + (h - 1) * w].y + 1) * width + nodes[i + (h - 1) * w].x] < currentDistance){
                currentDistance = gGrid[(nodes[i + (h - 1) * w].y + 1) * width + nodes[i + (h - 1) * w].x];
                nextStep = point{0, 1};
            }
        }
        if (wallGrid[(nodes[i + (h - 1) * w].y + 1) * width + nodes[i + (h - 1) * w].x] == 1){
            canGoDOWN = false;
        }
    }
    // up right
    if (wallGrid[(nodes[w - 1].y - 1) * width + nodes[w - 1].x + 1] != 1){
        if (gGrid[(nodes[w - 1].y - 1) * width + nodes[w - 1].x + 1] < currentDistance){
            currentDistance = gGrid[(nodes[w - 1].y - 1) * width + nodes[w - 1].x + 1];
            nextStep = point{1, -1};
        }
    }
    // down left
    if (wallGrid[(nodes[h * w - w].y + 1) * width + nodes[h * w - w].x - 1] != 1){
        if (gGrid[(nodes[h * w - w].y + 1) * width + nodes[h * w - w].x - 1] < currentDistance){
            currentDistance = gGrid[(nodes[h * w - w].y + 1) * width + nodes[h * w - w].x - 1];
            nextStep = point{-1, 1};
        }
    }
    // down right
    if (wallGrid[(nodes[h * w - 1].y + 1) * width + nodes[h * w - 1].x + 1] != 1){
        if (gGrid[(nodes[h * w - 1].y + 1) * width + nodes[h * w - 1].x + 1] < currentDistance){
            currentDistance = gGrid[(nodes[h * w - 1].y + 1) * width + nodes[h*w - 1].x + 1];
            nextStep = point{1, 1};
        }
    }
    // up left
    if (wallGrid[(nodes[0].y - 1) * width + nodes[0].x - 1] != 1){
        if (gGrid[(nodes[0].y - 1) * width + nodes[0].x - 1] < currentDistance){
            currentDistance = gGrid[(nodes[0].y - 1) * width + nodes[0].x - 1];
            nextStep = point{-1, -1};
        }
    }

    if (nextStep.x !=0){
        if (canGoLEFT == false && nextStep.x == -1) nextStep.x = 0;
        if (canGoRIGHT == false && nextStep.x == 1) nextStep.x = 0;
    }
    if (nextStep.y !=0){
        if (canGoUP == false && nextStep.y == -1) nextStep.y = 0;
        if (canGoDOWN == false && nextStep.y == 1) nextStep.y = 0;
    }
    return Vector2{static_cast<float>(nextStep.x), static_cast<float>(nextStep.y)};
};

int Pathfinder::createGrid(Rectangle collisionRec, Vector2 worldPos){
    bool finished = false;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // Calculate the 1D index for the 2D grid
            if (wallGrid[i * width + j] == 1) gGrid[i * width + j] = 1000; // Mark as a wall
            else gGrid[i * width + j] = 999;
        }
    }
    point buffer = point{0, 0};
    if (IsKeyDown(KEY_A)) buffer.x = static_cast<int>(scale / 2.0f);
    int x = static_cast<int>((collisionRec.x + worldPos.x) * scale / tileSize - scale / 2.0f) + buffer.x;

    if (IsKeyDown(KEY_W)) buffer.y = static_cast<int>(scale / 2.0f);
    int y = static_cast<int>((collisionRec.y + worldPos.y) * scale / tileSize) + buffer.y;
    int w = static_cast<int>(collisionRec.width * scale / tileSize);
    if (w < 1) w = 1;
    int h = static_cast<int>(collisionRec.height * scale / tileSize);
    if (h < 1) h = 1;
    point nodes[height * width]{};
    point newNodes[height * width]{};
    int nodeCount = 0;
    for (int i = y; i < y + h; i++) {
        for (int j = x; j < x + w; j++) {
            if (i >= 0 && i < height && j >= 0 && j < width) {
                gGrid[i * width + j] = 0; // Mark as root
                nodes[nodeCount] = point{j, i};
                nodeCount++;
            }
        }
    }
    int isNodeFinished[height * width]{};
    int isNodeChecked[height * width]{};

    int timesChecked = 0;
    int perimeterCount{};
    while (!finished){
        perimeterCount = 0;

        for (int i = 0; i < nodeCount; i++){
            isNodeFinished[nodes[i].y * width + nodes[i].x] = 1;
        }
        for (int i = 0; i < nodeCount; i++){
            // up
            if (wallGrid[(nodes[i].y - 1) * width + nodes[i].x] != 1 && isNodeFinished[(nodes[i].y - 1) * width + nodes[i].x] != 1){
                if (gGrid[(nodes[i].y - 1) * width + nodes[i].x] > gGrid[nodes[i].y * width + nodes[i].x] + 1){
                    gGrid[(nodes[i].y - 1) * width + nodes[i].x] = gGrid[nodes[i].y * width + nodes[i].x] + 1;
                    if (isNodeChecked[(nodes[i].y - 1) * width + nodes[i].x] != 1){
                        isNodeChecked[(nodes[i].y - 1) * width + nodes[i].x] = 1;
                        newNodes[perimeterCount] = point{nodes[i].x, nodes[i].y - 1};
                        perimeterCount++;
                    }
                }
            }
            // left
            if (wallGrid[nodes[i].y * width + nodes[i].x - 1] != 1 && isNodeFinished[nodes[i].y * width + nodes[i].x - 1] != 1){
                if (gGrid[nodes[i].y * width + nodes[i].x - 1] > gGrid[nodes[i].y * width + nodes[i].x] + 1){
                    gGrid[nodes[i].y * width + nodes[i].x - 1] = gGrid[nodes[i].y * width + nodes[i].x] + 1;
                    if (isNodeChecked[nodes[i].y * width + nodes[i].x - 1] != 1){
                        isNodeChecked[nodes[i].y * width + nodes[i].x - 1] = 1;
                        newNodes[perimeterCount] = point{nodes[i].x - 1, nodes[i].y};
                        perimeterCount++;
                    }
                }
            }
            // right
            if (wallGrid[nodes[i].y * width + nodes[i].x + 1] != 1 && isNodeFinished[nodes[i].y * width + nodes[i].x + 1] != 1){
                if (gGrid[nodes[i].y * width + nodes[i].x + 1] > gGrid[nodes[i].y * width + nodes[i].x] + 1){
                    gGrid[nodes[i].y * width + nodes[i].x + 1] = gGrid[nodes[i].y * width + nodes[i].x] + 1;
                    if (isNodeChecked[nodes[i].y * width + nodes[i].x + 1] != 1){
                        isNodeChecked[nodes[i].y * width + nodes[i].x + 1] = 1;
                        newNodes[perimeterCount] = point{nodes[i].x + 1, nodes[i].y};
                        perimeterCount++;
                    }
                }
            }
            // down
            if (wallGrid[(nodes[i].y + 1) * width + nodes[i].x] != 1 && isNodeFinished[(nodes[i].y + 1) * width + nodes[i].x] != 1){
                if (gGrid[(nodes[i].y + 1) * width + nodes[i].x] > gGrid[nodes[i].y * width + nodes[i].x] + 1){
                    gGrid[(nodes[i].y + 1) * width + nodes[i].x] = gGrid[nodes[i].y * width + nodes[i].x] + 1;
                    if (isNodeChecked[(nodes[i].y + 1) * width + nodes[i].x] != 1){
                        isNodeChecked[(nodes[i].y + 1) * width + nodes[i].x] = 1;
                        newNodes[perimeterCount] = point{nodes[i].x, nodes[i].y + 1};
                        perimeterCount++;
                    }
                }
            }
            // up left
            if (wallGrid[(nodes[i].y - 1) * width + nodes[i].x - 1] != 1 && isNodeFinished[(nodes[i].y - 1) * width + nodes[i].x - 1] != 1){
                if (gGrid[(nodes[i].y - 1) * width + nodes[i].x - 1] > gGrid[nodes[i].y * width + nodes[i].x] + 1.414f){
                    gGrid[(nodes[i].y - 1) * width + nodes[i].x - 1] = gGrid[nodes[i].y * width + nodes[i].x] + 1.414f;
                    if (isNodeChecked[(nodes[i].y - 1) * width + nodes[i].x - 1] != 1){
                        isNodeChecked[(nodes[i].y - 1) * width + nodes[i].x - 1] = 1;
                        newNodes[perimeterCount] = point{nodes[i].x - 1, nodes[i].y - 1};
                        perimeterCount++;
                    }
                }
            }
            // up right
            if (wallGrid[(nodes[i].y - 1) * width + nodes[i].x + 1] != 1 && isNodeFinished[(nodes[i].y - 1) * width + nodes[i].x + 1] != 1){
                if (gGrid[(nodes[i].y - 1) * width + nodes[i].x + 1] > gGrid[nodes[i].y * width + nodes[i].x] + 1.414f){
                    gGrid[(nodes[i].y - 1) * width + nodes[i].x + 1] = gGrid[nodes[i].y * width + nodes[i].x] + 1.414f;
                    if (isNodeChecked[(nodes[i].y - 1) * width + nodes[i].x + 1] != 1){
                        isNodeChecked[(nodes[i].y - 1) * width + nodes[i].x + 1] = 1;
                        newNodes[perimeterCount] = point{nodes[i].x + 1, nodes[i].y - 1};
                        perimeterCount++;
                    }
                }
            }
            // down left
            if (wallGrid[(nodes[i].y + 1) * width + nodes[i].x - 1] != 1 && isNodeFinished[(nodes[i].y + 1) * width + nodes[i].x - 1] != 1){
                if (gGrid[(nodes[i].y + 1) * width + nodes[i].x - 1] > gGrid[nodes[i].y * width + nodes[i].x] + 1.414f){
                    gGrid[(nodes[i].y + 1) * width + nodes[i].x - 1] = gGrid[nodes[i].y * width + nodes[i].x] + 1.414f;
                    if (isNodeChecked[(nodes[i].y + 1) * width + nodes[i].x - 1] != 1){
                        isNodeChecked[(nodes[i].y + 1) * width + nodes[i].x - 1] = 1;
                        newNodes[perimeterCount] = point{nodes[i].x - 1, nodes[i].y + 1};
                        perimeterCount++;
                    }
                }
            }
            // down right
            if (wallGrid[(nodes[i].y + 1) * width + nodes[i].x + 1] != 1 && isNodeFinished[(nodes[i].y + 1) * width + nodes[i].x + 1] != 1){
                if (gGrid[(nodes[i].y + 1) * width + nodes[i].x + 1] > gGrid[nodes[i].y * width + nodes[i].x] + 1.414f){
                    gGrid[(nodes[i].y + 1) * width + nodes[i].x + 1] = gGrid[nodes[i].y * width + nodes[i].x] + 1.414f;
                    if (isNodeChecked[(nodes[i].y + 1) * width + nodes[i].x + 1] != 1){
                        isNodeChecked[(nodes[i].y + 1) * width + nodes[i].x + 1] = 1;
                        newNodes[perimeterCount] = point{nodes[i].x + 1, nodes[i].y + 1};
                        perimeterCount++;
                    }
                }
            }
            if (perimeterCount == 0 || timesChecked == 15 * scale * scale * scale) finished = true;
            else{
                for (int k = 0; k < perimeterCount; k++){
                    nodes[k] = newNodes[k];
                }
                nodeCount = perimeterCount;
                timesChecked++;
                finished = true;
            }
        }
    }
    return 0;
}

void Pathfinder::drawGrid(){
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (gGrid[i * width + j] == 1000) DrawRectangle(j * 5, i * 5, 5, 5, RED);
            else if (gGrid[i * width + j] != 999) DrawRectangle(j * 5, i * 5, 5, 5, WHITE);
            if (gGrid[i * width + j] == 0) DrawRectangle(j * 5, i * 5, 5, 5, BLUE);
        }
    }
}