#include "AStar.h"
#include <queue>
#include <cmath>
#include <algorithm>

const int dx[4] = { 0, -1, 1, 0 };
const int dy[4] = { -1, 0, 0, 1 };

int Heuristic(Vector2 a, Vector2 b) {
    return abs((int)a.x - (int)b.x) + abs((int)a.y - (int)b.y); // Manhattan distance
}

bool IsInside(int x, int y, int width, int height) {
    return x >= 0 && x < width && y >= 0 && y < height;
}

std::vector<Vector2> FindPath(Vector2 start, Vector2 end, const int grid[][24], int width, int height) {
    std::vector<std::vector<Node>> nodes(width, std::vector<Node>(height));

    std::priority_queue<std::pair<int, Node*>, std::vector<std::pair<int, Node*>>, std::greater<>> openSet;

    Node* startNode = &nodes[(int)start.x][(int)start.y];
    startNode->x = (int)start.x;
    startNode->y = (int)start.y;
    startNode->gCost = 0;
    startNode->hCost = Heuristic(start, end);
    startNode->parent = nullptr;
    openSet.push({ startNode->fCost(), startNode });

    bool closed[24][24] = { false };

    while (!openSet.empty()) {
        Node* current = openSet.top().second;
        openSet.pop();

        if (current->x == (int)end.x && current->y == (int)end.y) {
            std::vector<Vector2> path;
            while (current != nullptr) {
                path.push_back({ (float)current->x, (float)current->y });
                current = current->parent;
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        closed[current->x][current->y] = true;

        for (int i = 0; i < 4; i++) {
            int nx = current->x + dx[i];
            int ny = current->y + dy[i];

            if (!IsInside(nx, ny, width, height) || grid[nx][ny] == 1 || closed[nx][ny]) continue;

            Node* neighbor = &nodes[nx][ny];
            int newG = current->gCost + 1;

            if (neighbor->parent == nullptr || newG < neighbor->gCost) {
                neighbor->x = nx;
                neighbor->y = ny;
                neighbor->gCost = newG;
                neighbor->hCost = Heuristic({ (float)nx, (float)ny }, end);
                neighbor->parent = current;
                openSet.push({ neighbor->fCost(), neighbor });
            }
        }
    }

    return {}; // No path found
}
