#ifndef CHARACTER_H
#define CHARACTER_H

#include "C:/raylib/raylib/src/raylib.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter{
    public:
        Character(int winWidth, int winHeight, Texture2D idleTexture, Texture2D movementTexture);
        void tick(float deltaTime) override;
        Vector2 getScreenPos(){return screenPos;}
    private:
};

#endif