#ifndef ASTAR_H
#define ASTAR_H

#include "raylib.h"
#include <vector>

struct Node {
    int x, y;
    int gCost, hCost;
    Node* parent;

    int fCost() const { return gCost + hCost; }
    bool operator==(const Node& other) const { return x == other.x && y == other.y; }
};

// Returns a path as a list of grid positions (Vector2s with x = col, y = row)
std::vector<Vector2> FindPath(Vector2 start, Vector2 end, const int grid[][24], int width, int height);

#endif
