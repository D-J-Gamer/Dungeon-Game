#ifndef ENEMY_H
#define ENEMY_H

#include "C:/raylib/raylib/src/raylib.h"
#include "BaseCharacter.h"
#include "Character.h"
#include "Item.h"
#include <string>
#include <iostream>


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
    Vector2 distanceToTarget();
    bool getCanSeeTarget(float deltaTime);
    void attackPlayer(){attacking = true;}
    bool getDealtdamage(){return dealtdamage;}
    void setDealtdamage(bool dealt){dealtdamage = dealt;}
    bool getRecieveddamage(){return recieveddamage;}
    void setRecieveddamage(bool recieved){recieveddamage = recieved;}
    int getFrameDamageRecieved(){return frameDamageRecieved;}
    void setFrameDamageRecieved(int frame){frameDamageRecieved = frame;}
    int getFrameDamageDealt(){return frameDamageDealt;}
    void setFrameDamageDealt(int frame){frameDamageDealt = frame;}
    Item getItem(int ind){return item[ind];}
    void addItem(Item object){
        item[index] = object;
        index++;
        bool breakLoop = false;
        for (int i = 0; i < 5; i++){
            for (int j = 0; j < 5; j++){
                if (itemsPosInventory[i * 5 + j] == false){
                    itemsPosInventory[i * 5 + j] = true;
                    item[index - 1].position.x = j;
                    item[index - 1].position.y = i;
                    breakLoop = true;
                    break;
                }
            }
            if (breakLoop == true) break;
        }
    }
    void addSpecificItem(Item addedItem, int x, int y){
        item[index] = addedItem;
        item[index].position.x = x;
        item[index].position.y = y;
        index++;
        itemsPosInventory[y * 5 + x] = true;
    }
    void replaceItem(int ind, Item object){item[ind] = object;}
    void discardItem(int ind){
        item[ind] = Item{};
        index--;
        fixItemArray(ind);
    }
    void fixItemArray(int ind){
        for (int i = ind; i < index; i++){
            item[i] = item[i + 1];
        }
    }
    bool openInventoryCheck(){
        if (openInventory == true){
            openInventory = false;
            return true;
        }
        else return false;
    }
    bool CheckCollision(){
        return CheckCollisionRecs(getCollisionRec(), target->getCollisionRec());
    }
    int getItemCount(){return index;}
    void toggleIsHeld(int ind){item[ind].isHeld = !item[ind].isHeld;}
    void setXItemPosition(int ind, float x){item[ind].position.x = x;}
    void setYItemPosition(int ind, float y){item[ind].position.y = y;}
    void setItemTexture(int ind, Texture2D texture){item[ind].texture = texture;}
    void toggleInventoryPos(int x, int y){
        if (itemsPosInventory[x + y * 5] == false){
            itemsPosInventory[x + y * 5] = true;
        }
        else itemsPosInventory[x + y * 5] = false;
    }
    bool getInventoryPos(int x, int y){return itemsPosInventory[x + y * 5];}
    
private:
    Character* target{};
    bool dealtdamage = false;
    bool recieveddamage = false;
    int frameDamageRecieved{};
    int frameDamageDealt{};
    Rectangle wallsRec[15]{};
    int wallCount{};
    float lastSeenTargetTime = 3.0f;
    Item item[25]{};
    int goldCount{};
    int index{};
    bool openInventory = false;
    bool itemsPosInventory[25]{};
};

#endif