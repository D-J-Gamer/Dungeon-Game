#include "Grid.h"

Vector2 WorldToGrid(Vector2 worldPos) {
    return Vector2{ (worldPos.x / TILE_SIZE), (worldPos.y / TILE_SIZE) };
}

Vector2 GridToWorld(Vector2 gridPos) {
    return Vector2{ gridPos.x * TILE_SIZE, gridPos.y * TILE_SIZE };
}

void InitGrid(int grid[][MAP_WIDTH], Rectangle* walls, int wallCount) {
    // Start with everything walkable
    for (int x = 0; x < MAP_WIDTH; x++) {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            grid[x][y] = 0;
        }
    }

    // Mark wall tiles as non-walkable
    for (int i = 0; i < wallCount; i++) {
        int xStart = (int)(walls[i].x / TILE_SIZE);
        int yStart = (int)(walls[i].y / TILE_SIZE);
        int w = (int)(walls[i].width / TILE_SIZE);
        int h = (int)(walls[i].height / TILE_SIZE);

        for (int x = xStart; x < xStart + w; x++) {
            for (int y = yStart; y < yStart + h; y++) {
                if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT) {
                    grid[x][y] = 1;
                }
            }
        }
    }
}
