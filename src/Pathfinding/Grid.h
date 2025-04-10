#ifndef GRID_H
#define GRID_H

#include "raylib.h"

// Constants
const int TILE_SIZE = 128;
const int MAP_WIDTH = 24;
const int MAP_HEIGHT = 24;

// World <-> Grid conversion
Vector2 WorldToGrid(Vector2 worldPos);
Vector2 GridToWorld(Vector2 gridPos);

// Grid initialization
void InitGrid(int grid[][MAP_WIDTH], Rectangle* walls, int wallCount);

#endif
