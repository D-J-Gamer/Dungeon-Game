#ifndef INVENTORY_H
#define INVENTORY_H
#include "Raylib\raylib\src\raylib.h"
#include "Item.h"
#include <vector>
#include "Enemy.h"

class Inventory{
    public:
        Inventory(Texture2D inventoryText, float windowWid, float windowHei);
        void IsItemSelected();
        void DrawAbsentItems();
        void DrawInventory();
        void OpenInventory(){
            inventoryOpen = true;
        }
        void OpenSubInventory(){
            subInventoryOpen = true;
        }
        void DrawSubInventory(Item item[5], int gold);
        void addItem(Item item){
            items[itemCount] = item;
            itemCount++;
            bool breakLoop = false;
            for (int i = 0; i < 5; i++){
                for (int j = 0; j < 5; j++){
                    if (itemPosInventory[i * 5 + j] == false){
                        itemPosInventory[i * 5 + j] = true;
                        items[itemCount - 1].position.x = j;
                        items[itemCount - 1].position.y = i;
                        breakLoop = true;
                        break;
                    }
                }
                if (breakLoop == true) break;
            }
        }
        void addSpecificItem(Item item, int x, int y){
            items[itemCount] = item;
            itemCount++;
            itemPosInventory[x + y * 5] = true;
            items[itemCount - 1].position.x = x;
            items[itemCount - 1].position.y = y;
        }
        void discardItem(int index){
            items[index] = defaultItem;
            itemCount--;
            fixItemArray(index);
        }
        void fixItemsPosition(/*args*/){/*code*/}
        void fixItemArray(int index){
            for (int i = index; i < itemCount; i++){
                items[i] = items[i + 1];
            }
        }
        void createDefaultItems();
        int getItemCount(){return itemCount;}
        void setEnemy(Enemy* enemy){this->enemy = enemy;}
        void getIsSubInventoryOpen(){
            if (subInventoryOpen){DrawText("Sub Inventory : Open", 120, 20, 80, WHITE);}
        }
        void getISItemHeld(){
            if (isItemHeld == true){
                DrawText("Item is held", 120, 110, 80, WHITE);
            }
        }
        void getIsHeldItemInSubInventory(){
            if (isHeldItemInSubInventory == true){
                DrawText("Item is held in sub inventory", 120, 200, 80, WHITE);
            }
        }
        void getHeldItemIndex(){
            if (isItemHeld == true){
                DrawText(TextFormat("Held Item Index: %i", heldItemIndex), 120, 290, 80, WHITE);
            }
        }
    private:
        int itemWidth = 7;
        int itemHeight = 9;
        Texture2D inventoryTexture{};
        Texture2D leftTexture = LoadTexture("Inventory\\EnemyInventory.png");
        Texture2D weaponAbsentTexture = LoadTexture("Inventory\\Weapon_Absent.png");
        Texture2D armorAbsentTexture = LoadTexture("Inventory\\Armor_Absent.png");
        Texture2D headgearAbsentTexture = LoadTexture("Inventory\\HeadGear_Absent.png");
        Texture2D pantsAbsentTexture = LoadTexture("Inventory\\Belt_Absent.png");
        Texture2D ringAbsentTexture = LoadTexture("Inventory\\Ring_Absent.png");
        Texture2D ring2AbsentTexture = LoadTexture("Inventory\\Ring2_Absent.png");
        Texture2D amuletAbsentTexture = LoadTexture("Inventory\\Amulet_Absent.png");
        Texture2D shieldAbsentTexture = LoadTexture("Inventory\\Shield_Absent.png");
        Texture2D bootAbsentTexture = LoadTexture("Inventory\\Boots_Absent.png");
        Texture2D glovesAbsentTexture = LoadTexture("Inventory\\Gloves_Absent.png");
        float windowWidth{};
        float windowHeight{};
        bool inventoryOpen = false;
        bool subInventoryOpen = false;
        float scale = 1.25f;
        int itemCount = 0;
        Item items[41]{};
        Item defaultItem{};
        Vector2 iDEquipPos[10]{};
        bool iDEquip[10]{};
        Vector2 iDEquipPosReference[10] = {{138.0f, 138.0f}, {372.0f, 138.0f}, {10.0f, 10.0f}, {10.0f, 10.0f}, {10.0f, 10.0f},
                                            {}, {}, {}, {}, {}};
        bool isItemHeld = false;
        int heldItemIndex = 0;
        Item lastHeldItem{};
        Vector2 inventoryPos{};
        Vector2 itemsPos[5]{};
        Vector2 itemsPosReference[6] = {{20, 515}, {110, 607}, {200, 698}, {290, 789}, {380, 880}};
        int xPos[5] = {0, 1, 2, 3, 4};
        int yPos[5] = {0, 1, 2, 3, 4};
        bool itemPosInventory[26]{};
        Item subItems[5]{};
        int goldCount = 0;
        Enemy* enemy{};
        bool isHeldItemInSubInventory = false;
        
};



#endif