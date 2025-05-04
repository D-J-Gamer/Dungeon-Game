#ifndef CHARACTER_H
#define CHARACTER_H

#include "Raylib\raylib\src\raylib.h"
#include "Raylib\raylib\src\raymath.h"
#include "BaseCharacter.h"
#include "Textures.h"
#include "Pathfinder.h"



class Character : public BaseCharacter{
    public:
        Character(int winWidth, int winHeight, Textures Texture_s, float life_s, float damage_s, int wallCount,Rectangle walls[], Vector2 pos);
        ~Character();
        void tick(float deltaTime) override;
        Vector2 getScreenPos(){return screenPos;}
        void setPath(Pathfinder* pathfinder){path = pathfinder;}
        Vector2 pathToTarget(Rectangle collisionRec, Vector2 worldPos){
            return path->nextStepPathfind(collisionRec, worldPos);
        }

    private:
        float distancedMoved{};
        Pathfinder* path{};
};

#endif