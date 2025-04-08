#include "Raylib\raylib\src\raylib.h"

class Prop{
public:
    Prop(Texture2D* tex, Vector2 pos, float base);
    void Render(Vector2 pos);
    void updateAnimation(float deltaTime);
    Rectangle GetCollisionRec();
private:
    Texture2D texture[4];
    Vector2 worldPos{};
    float scale = 8.0f;
    Vector2 screenPos{};
    int frame = 0;
    float runningTime = 0.0f;
    float updateTime = 1.0f/8.0f;
    int maxFrames = 4;
    float baseFooting = 1.0f;
};