#include "C:/raylib/raylib/src/raylib.h"
#include "BaseCharacter.h"
#include "Character.h"


class Enemy: public BaseCharacter{
public:
    Enemy(Vector2 pos, Textures texture_s, float life_s, float damage_s);
    void tick(float deltaTime) override;
    void setTarget(Character* target){this->target = target;}
    void setWall(Rectangle rec[], int wallcount){
        for (int i = 0; i < wallcount; i++){
            wallsRec[i] = rec[i];
        }
        wallCount = wallcount;
    }
    Vector2 toTarget();
    bool getCanSeeTarget();
    void attackPlayer(){attacking = true;}
    bool getDealtdamage(){return dealtdamage;}
    void setDealtdamage(bool dealt){dealtdamage = dealt;}
    bool getRecieveddamage(){return recieveddamage;}
    void setRecieveddamage(bool recieved){recieveddamage = recieved;}
    int getFrameDamageRecieved(){return frameDamageRecieved;}
    void setFrameDamageRecieved(int frame){frameDamageRecieved = frame;}
    int getFrameDamageDealt(){return frameDamageDealt;}
    void setFrameDamageDealt(int frame){frameDamageDealt = frame;}
    
private:
    Character* target{};
    bool dealtdamage = false;
    bool recieveddamage = false;
    int frameDamageRecieved{};
    int frameDamageDealt{};
    Rectangle wallsRec[15]{};
    int wallCount{};
};