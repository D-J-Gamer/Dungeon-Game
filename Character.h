#ifndef CHARACTER_H
#define CHARACTER_H

#include "Raylib\raylib\src\raylib.h"
#include "BaseCharacter.h"
#include "Textures.h"

class Character : public BaseCharacter{
    public:
        Character(int winWidth, int winHeight, Textures Texture_s, float life_s, float damage_s);
        void tick(float deltaTime) override;
        Vector2 getScreenPos(){return screenPos;}
    private:
};

#endif