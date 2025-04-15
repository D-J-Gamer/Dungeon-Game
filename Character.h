#ifndef CHARACTER_H
#define CHARACTER_H

#include "Raylib\raylib\src\raylib.h"
// #include "Raylib\raylib\src\raymath.h"
#include "BaseCharacter.h"
#include "Textures.h"
// #include "src\Pathfinder.h"



class Character : public BaseCharacter{
    public:
        class Pathfinder{
            public:
                Pathfinder(int newScale, int newWallCount, int newWidth, int newHeight, Rectangle* walls, int newTileSize);
                ~Pathfinder(/* args */);
                Vector2 nextStepPathfind(float xPos, float yPos, float xTarget, float yTarget);
                int createGrid(Rectangle collisionRec, Vector2 worldPos);
            private:
                int scale{};
                int wallCount{};
                int* wallGrid;
                float* gGrid;
                int width{};
                int height{};
                Rectangle* wallsRec{};
                int tileSize{};
            };
        Character(int winWidth, int winHeight, Textures Texture_s, float life_s, float damage_s, int wallCount,Rectangle walls[]);
        ~Character();
        void tick(float deltaTime) override;
        Vector2 getScreenPos(){return screenPos;}
        Pathfinder pathfinder;

    private:
    float distancedMoved{};
};

#endif