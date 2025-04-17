#include "Character.h"
#include "Raylib\raylib\src\raymath.h"
#include "Textures.h"
#include "Pathfinder.h"

// struct point{
//     int x;
//     int y;
// };

// // Pathfinder
// Character::Pathfinder::Pathfinder(int newScale, int newWallCount, int newWidth, int newHeight, Rectangle* walls, int newTileSize){
//     scale = newScale;
//     wallCount = newWallCount;
//     width = newWidth * scale;
//     height = newHeight * scale;
//     tileSize = newTileSize;
//     wallsRec = new Rectangle[wallCount]{};
//     for (int i = 0; i < wallCount; i++){
//         wallsRec[i] = walls[i];
//         wallsRec[i].x /= tileSize;
//         wallsRec[i].y /= tileSize;
//         wallsRec[i].width /= tileSize;
//         wallsRec[i].height /= tileSize;
//     }
//     wallGrid = new int[height * width]{}; //y1{x1, x2, x3 ...} y2{x1, x2, x3 ...}
//     for (int i = 0; i < height; i++) {
//         for (int j = 0; j < width; j++) {
//             // Calculate the 1D index for the 2D grid
//             wallGrid[i * width + j] = 0;
//         }
//     }

//     for (int i = 0; i < wallCount; i++) {
//         for (int j = static_cast<int>(wallsRec[i].y) * scale; j < static_cast<int>(wallsRec[i].y + wallsRec[i].height) * scale; j++) {
//             for (int k = static_cast<int>(wallsRec[i].x) * scale; k < static_cast<int>(wallsRec[i].x + wallsRec[i].width) * scale; k++) {
//                 if (j >= 0 && j < height && k >= 0 && k < width) {
//                     wallGrid[j * width + k] = 1; // Mark as a wall
//                 }
//             }
//         }
//     }
//     gGrid = new float[height * width]{};
//     createGrid(Rectangle{0.0f, 0.0f, 0.0f, 0.0f}, Vector2{0.0f, 0.0f});
// };
// Character::Pathfinder::~Pathfinder(/* args */){
//     delete[] wallGrid;
//     delete[] gGrid;
//     delete[] wallsRec;
//     // delete[] wallCount;
// };

// Vector2 Character::Pathfinder::nextStepPathfind(float xPos, float yPos, float xTarget, float yTarget){
//     return Vector2{0.0f, 0.0f};
// };

// // int grid[map_height][map_width]{};

// int Character::Pathfinder::createGrid(Rectangle collisionRec, Vector2 worldPos){
//     bool finished = false;
//     for (int i = 0; i < height; i++) {
//         for (int j = 0; j < width; j++) {
//             // Calculate the 1D index for the 2D grid
//             if (wallGrid[i * width + j] == 1) gGrid[i * width + j] = 1000; // Mark as a wall
//             else gGrid[i * width + j] = 999;
//         }
//     }
//     int x = static_cast<int>((collisionRec.x + worldPos.x) * scale / tileSize);
//     int y = static_cast<int>((collisionRec.y + worldPos.y) * scale / tileSize);
//     int w = static_cast<int>(collisionRec.width * scale / tileSize);
//     int h = static_cast<int>(collisionRec.height * scale / tileSize);
//     point nodes[height * width]{};
//     point newNodes[height * width]{};
//     int nodeCount = 0;
//     for (int i = y; i < y + h; i++) {
//         for (int j = x; j < x + w; j++) {
//             if (i >= 0 && i < height && j >= 0 && j < width) {
//                 gGrid[i * width + j] = 0; // Mark as root
//                 nodes[nodeCount] = point{j, i};
//                 nodeCount++;
//             }
//         }
//     }
//     int isNodeFinished[height * width]{};
//     int isNodeChecked[height * width]{};

//     int timesChecked = 0;
//     int perimeterCount{};
//     while (!finished){
//         perimeterCount = 0;

//         for (int i = 0; i < nodeCount; i++){
//             isNodeFinished[nodes[i].y * width + nodes[i].x] = 1;
//         }
//         for (int i = 0; i < nodeCount; i++){
//             // up
//             if (wallGrid[(nodes[i].y - 1) * width + nodes[i].x] != 1 && isNodeFinished[(nodes[i].y - 1) * width + nodes[i].x] != 1){
//                 if (gGrid[(nodes[i].y - 1) * width + nodes[i].x] > gGrid[nodes[i].y * width + nodes[i].x] + 1){
//                     gGrid[(nodes[i].y - 1) * width + nodes[i].x] = gGrid[nodes[i].y * width + nodes[i].x] + 1;
//                     if (isNodeChecked[(nodes[i].y - 1) * width + nodes[i].x] != 1){
//                         isNodeChecked[(nodes[i].y - 1) * width + nodes[i].x] = 1;
//                         newNodes[perimeterCount] = point{nodes[i].x, nodes[i].y - 1};
//                         perimeterCount++;
//                     }
//                 }
//             }
//             // left
//             if (wallGrid[nodes[i].y * width + nodes[i].x - 1] != 1 && isNodeFinished[nodes[i].y * width + nodes[i].x - 1] != 1){
//                 if (gGrid[nodes[i].y * width + nodes[i].x - 1] > gGrid[nodes[i].y * width + nodes[i].x] + 1){
//                     gGrid[nodes[i].y * width + nodes[i].x - 1] = gGrid[nodes[i].y * width + nodes[i].x] + 1;
//                     if (isNodeChecked[nodes[i].y * width + nodes[i].x - 1] != 1){
//                         isNodeChecked[nodes[i].y * width + nodes[i].x - 1] = 1;
//                         newNodes[perimeterCount] = point{nodes[i].x - 1, nodes[i].y};
//                         perimeterCount++;
//                     }
//                 }
//             }
//             // right
//             if (wallGrid[nodes[i].y * width + nodes[i].x + 1] != 1 && isNodeFinished[nodes[i].y * width + nodes[i].x + 1] != 1){
//                 if (gGrid[nodes[i].y * width + nodes[i].x + 1] > gGrid[nodes[i].y * width + nodes[i].x] + 1){
//                     gGrid[nodes[i].y * width + nodes[i].x + 1] = gGrid[nodes[i].y * width + nodes[i].x] + 1;
//                     if (isNodeChecked[nodes[i].y * width + nodes[i].x + 1] != 1){
//                         isNodeChecked[nodes[i].y * width + nodes[i].x + 1] = 1;
//                         newNodes[perimeterCount] = point{nodes[i].x + 1, nodes[i].y};
//                         perimeterCount++;
//                     }
//                 }
//             }
//             // down
//             if (wallGrid[(nodes[i].y + 1) * width + nodes[i].x] != 1 && isNodeFinished[(nodes[i].y + 1) * width + nodes[i].x] != 1){
//                 if (gGrid[(nodes[i].y + 1) * width + nodes[i].x] > gGrid[nodes[i].y * width + nodes[i].x] + 1){
//                     gGrid[(nodes[i].y + 1) * width + nodes[i].x] = gGrid[nodes[i].y * width + nodes[i].x] + 1;
//                     if (isNodeChecked[(nodes[i].y + 1) * width + nodes[i].x] != 1){
//                         isNodeChecked[(nodes[i].y + 1) * width + nodes[i].x] = 1;
//                         newNodes[perimeterCount] = point{nodes[i].x, nodes[i].y + 1};
//                         perimeterCount++;
//                     }
//                 }
//             }
//             // up left
//             if (wallGrid[(nodes[i].y - 1) * width + nodes[i].x - 1] != 1 && isNodeFinished[(nodes[i].y - 1) * width + nodes[i].x - 1] != 1){
//                 if (gGrid[(nodes[i].y - 1) * width + nodes[i].x - 1] > gGrid[nodes[i].y * width + nodes[i].x] + 1.414f){
//                     gGrid[(nodes[i].y - 1) * width + nodes[i].x - 1] = gGrid[nodes[i].y * width + nodes[i].x] + 1.414f;
//                     if (isNodeChecked[(nodes[i].y - 1) * width + nodes[i].x - 1] != 1){
//                         isNodeChecked[(nodes[i].y - 1) * width + nodes[i].x - 1] = 1;
//                         newNodes[perimeterCount] = point{nodes[i].x - 1, nodes[i].y - 1};
//                         perimeterCount++;
//                     }
//                 }
//             }
//             // up right
//             if (wallGrid[(nodes[i].y - 1) * width + nodes[i].x + 1] != 1 && isNodeFinished[(nodes[i].y - 1) * width + nodes[i].x + 1] != 1){
//                 if (gGrid[(nodes[i].y - 1) * width + nodes[i].x + 1] > gGrid[nodes[i].y * width + nodes[i].x] + 1.414f){
//                     gGrid[(nodes[i].y - 1) * width + nodes[i].x + 1] = gGrid[nodes[i].y * width + nodes[i].x] + 1.414f;
//                     if (isNodeChecked[(nodes[i].y - 1) * width + nodes[i].x + 1] != 1){
//                         isNodeChecked[(nodes[i].y - 1) * width + nodes[i].x + 1] = 1;
//                         newNodes[perimeterCount] = point{nodes[i].x + 1, nodes[i].y - 1};
//                         perimeterCount++;
//                     }
//                 }
//             }
//             // down left
//             if (wallGrid[(nodes[i].y + 1) * width + nodes[i].x - 1] != 1 && isNodeFinished[(nodes[i].y + 1) * width + nodes[i].x - 1] != 1){
//                 if (gGrid[(nodes[i].y + 1) * width + nodes[i].x - 1] > gGrid[nodes[i].y * width + nodes[i].x] + 1.414f){
//                     gGrid[(nodes[i].y + 1) * width + nodes[i].x - 1] = gGrid[nodes[i].y * width + nodes[i].x] + 1.414f;
//                     if (isNodeChecked[(nodes[i].y + 1) * width + nodes[i].x - 1] != 1){
//                         isNodeChecked[(nodes[i].y + 1) * width + nodes[i].x - 1] = 1;
//                         newNodes[perimeterCount] = point{nodes[i].x - 1, nodes[i].y + 1};
//                         perimeterCount++;
//                     }
//                 }
//             }
//             // down right
//             if (wallGrid[(nodes[i].y + 1) * width + nodes[i].x + 1] != 1 && isNodeFinished[(nodes[i].y + 1) * width + nodes[i].x + 1] != 1){
//                 if (gGrid[(nodes[i].y + 1) * width + nodes[i].x + 1] > gGrid[nodes[i].y * width + nodes[i].x] + 1.414f){
//                     gGrid[(nodes[i].y + 1) * width + nodes[i].x + 1] = gGrid[nodes[i].y * width + nodes[i].x] + 1.414f;
//                     if (isNodeChecked[(nodes[i].y + 1) * width + nodes[i].x + 1] != 1){
//                         isNodeChecked[(nodes[i].y + 1) * width + nodes[i].x + 1] = 1;
//                         newNodes[perimeterCount] = point{nodes[i].x + 1, nodes[i].y + 1};
//                         perimeterCount++;
//                     }
//                 }
//             }
//             if (perimeterCount == 0 || timesChecked == 0) finished = true;
//             else{
//                 for (int k = 0; k < perimeterCount; k++){
//                     nodes[k] = newNodes[k];
//                 }
//                 nodeCount = perimeterCount;
//                 timesChecked++;
//                 finished = true;
//             }
//         }
//     }

//     if (!wallsUpdated){
//         for (int i = 0; i < height; i++) {
//             for (int j = 0; j < width; j++) {
//                 // Calculate the 1D index for the 2D grid
//                 wallGrid[i * width + j] = 0;
//             }
//         }
    
//         for (int i = 0; i < wallCount; i++) {
//             for (int j = static_cast<int>(wallsRec[i].y); j < static_cast<int>(wallsRec[i].y + wallsRec[i].height); j++) {
//                 for (int k = static_cast<int>(wallsRec[i].x); k < static_cast<int>(wallsRec[i].x + wallsRec[i].width); k++) {
//                     if (j >= 0 && j < height * scale && k >= 0 && k < width * scale) {
//                         wallGrid[j * width + k] = 1; // Mark as a wall
//                     }
//                 }
//             }
//         }

//     }


    
//     return 0;
// };


// Character
Character::Character(int winWidth, int winHeight, Textures texture_s, float life_s, float damage_s, int wallCount, Rectangle walls[])
// : pathfinder(4, wallCount, 32, 24, walls, 128)
{
    texture = texture_s.idle;
    idle = texture_s.idle;
    movement = texture_s.movement;
    attack = texture_s.attack;
    maxAttackFrames = texture_s.maxAttackFrames;
    updateTimeAttack = texture_s.attackUpdateTime;
    death = texture_s.death;
    maxDeathFrames = texture_s.maxDeathFrames;
    dimensions[0] = (float)idle.width / (float)maxIdleFrames; //width
    dimensions[1] = (float)texture.height; //height
    screenPos = {static_cast<float>(winWidth)/2.0f - scale * dimensions[0] / 2.0f, 
                static_cast<float>(winHeight)/2.0f - scale * dimensions[1] / 2.0f};
    worldPos = {0.0, 0.0};
    controlled = true;
    life = life_s;
    damage = damage_s;
    distancedMoved = 0.0f;
    for (int i = 0; i < 2; i++) attackFrames_w_damage[i] = texture_s.attackFrames_w_damage[i];
    // pathfinder = Pathfinder(4, wallCount, 32, 24, walls, 128);
}

void Character::tick(float deltaTime){
    // if (!getAlive()) return;
    Vector2 direction = {0.0, 0.0};
    worldPosLastFrame = worldPos;

    if (IsKeyDown(KEY_SPACE) && !attacking){
        attacking = true;
        frame = 0;
    }
    if (!attacking && getAlive()){
        if (IsKeyDown(KEY_W)) direction.y -= 1.0;
        if (IsKeyDown(KEY_S)) direction.y += 1.0;
        if (IsKeyDown(KEY_A)) direction.x -= 1.0;
        if (IsKeyDown(KEY_D)) direction.x += 1.0;
        if (Vector2Length(direction) != 0.0){
            direction = Vector2Normalize(direction);
            direction.x *= speed;
            direction.y *= speed;
            if (IsKeyDown(KEY_LEFT_SHIFT)) {
                direction.x *= 2.0f;
                direction.y *= 2.0f;
            }
            worldPos.x -= direction.x;
            worldPos.y -= direction.y;
            distancedMoved += Vector2Length(direction);
            if (distancedMoved > 128.0f){
                distancedMoved = 0.0f;
                path->createGrid(getCollisionRec(), Vector2 {-worldPos.x, -worldPos.y});
            }
            // if (direction.x > 0) rightleft = 1.f;
            // else if (direction.x < 0) rightleft = -1.f;
            moving = true;
        }
        else moving = false;
    }

    BaseCharacter::tick(deltaTime);

    // Rectangle source = {frame * dimensions[0], 0.0f, dimensions[0] * rightleft, dimensions[1]};
    // Rectangle dest = {screenPos.x + 16, screenPos.y - 48, scale * dimensions[0], scale * dimensions[1]};
    // DrawTexturePro(texture, source, dest, (Vector2){0.0, 0.0}, 0.0f, WHITE);
}

Character::~Character(){
//     // pathfinder.~Pathfinder();
//     // delete pathfinder;
}