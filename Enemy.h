#include "C:/raylib/raylib/src/raylib.h"
#include "BaseCharacter.h"
#include "Character.h"

class Enemy: public BaseCharacter{
public:
    Enemy(Vector2 pos, Texture2D idle, Texture2D movement);
    void tick(float deltaTime) override;
    void setTarget(Character* target){this->target = target;}
    Vector2 toTarget();
private:
    Character* target{};
};