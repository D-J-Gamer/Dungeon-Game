#ifndef ITEM_H
#define ITEM_H

#include "Raylib\raylib\src\raylib.h"

struct Size{
    int width{};
    int height{};
};

struct Stats{
    int damage{};
    int life{};
    int speed{};
    int attackSpeed{};
    int armor{};
    int magicResistance{};
};

struct Item{
    Size size{};
    Vector2 position{};
    Texture2D texture{};
    Texture2D selectedTexture{};
    Texture2D notSelectedTexture{};
    bool isHeld{};
    bool isEquipped{};
    bool isEquippable{};
    int equippedSlot{}; // 0: weapon, 1: shield, 2: headgear, 3: chestplate, 4: pants, 5: boots, 6: gloves, 7: ring, 8: ring2, 9: amulet
    // bool isTwoHanded{};
    Stats stats{};
    int itemType{}; // 0: weapon, 1: shield, 2: armor, 3: consumable, 4: trinket, 5: ring, 6: amulet
    int itemID{}; /* 01: sword, 02: axe, 03: bow, 04: staff, 05: wand, 06: dagger, 07: spear, 08: mace, 09: crossbow,
    11: shield,
    21: helmet, 12: chestplate, 13: leggings, 14: boots, 15: gloves, //16: belt, 
    31: health potion, 22: mana potion, 23: stamina potion, 24: antidote, 25: elixir
    41: magic rock, 31: totem, 32: charm, 33: talisman, 34: relic, 35: artifact, 36: crystal, 37: fragment*/
};

Item createRandomWeapon();

Item createRandomShield();

Item createRandomArmor();

Item createRandomConsumable();

Item createRandomTrinket();

Item createRandomRing();

Item createRandomAmulet();

Item createRandomItem();

Item createDefaultWeapon();

#endif