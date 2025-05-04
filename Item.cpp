#include "Item.h"
#include "Raylib\raylib\src\raylib.h"

Item createRandomWeapon(){
    Item tempItem{};
    tempItem.itemType = 0; // weapon
    // tempItem.itemID = GetRandomValue(1, 10); // random weapon ID
    tempItem.itemID = 6; // will be removed code, temporary code
    if (tempItem.itemID == 1) { /*code*/}
    if (tempItem.itemID == 2) { /*code*/}
    if (tempItem.itemID == 3) { /*code*/}
    if (tempItem.itemID == 4) { /*code*/}
    if (tempItem.itemID == 5) { /*code*/}
    if (tempItem.itemID == 6) {
        tempItem.notSelectedTexture = LoadTexture("Inventory\\Items\\Weapons\\DaggerCommon.png");
        tempItem.selectedTexture = LoadTexture("Inventory\\Items\\Weapons\\Selected\\DaggerCommon.png");
        tempItem.texture = tempItem.notSelectedTexture;
        tempItem.size.width = 1;
        tempItem.size.height = 2;
    }
    if (tempItem.itemID == 7) { /*code*/}
    if (tempItem.itemID == 8) { /*code*/}
    if (tempItem.itemID == 9) { /*code*/}
    if (tempItem.itemID == 10) { /*code*/}
    tempItem.stats.damage = GetRandomValue(1, 10); // random damage value
    return tempItem;
}

Item createRandomShield(){
    Item tempItem{};
    tempItem.itemType = 1; // shield
    tempItem.itemID = GetRandomValue(11, 11); // random shield ID
    if (tempItem.itemID == 11) {
        tempItem.notSelectedTexture = LoadTexture("Inventory\\Items\\Shield\\ShieldCommon.png");
        tempItem.selectedTexture = LoadTexture("Inventory\\Items\\Shield\\Selected\\ShieldCommon.png");
        tempItem.texture = tempItem.notSelectedTexture;
        tempItem.size.width = 2;
        tempItem.size.height = 2;
        tempItem.equippedSlot = 1; // shield slot
    }
    tempItem.stats.armor = GetRandomValue(1, 10); // random armor value
    return tempItem;
}

Item createRandomArmor(){
    Item tempItem{};
    tempItem.itemType = 2; // armor
    tempItem.itemID = GetRandomValue(21, 26); // random armor ID
    tempItem.stats.armor = GetRandomValue(1, 10); // random armor value
    return tempItem;
}

Item createRandomConsumable(){
    Item tempItem{};
    tempItem.itemType = 3; // consumable
    tempItem.itemID = GetRandomValue(31, 35); // random consumable ID
    tempItem.stats.life = GetRandomValue(1, 10); // random life value
    return tempItem;
}

Item createRandomTrinket(){
    Item tempItem{};
    tempItem.itemType = 4; // trinket
    tempItem.itemID = GetRandomValue(41, 48); // random trinket ID
    tempItem.stats.speed = GetRandomValue(1, 10); // random speed value
    return tempItem;
}

Item createRandomRing(){
    Item tempItem{};
    tempItem.itemType = 5; // ring
    tempItem.itemID = GetRandomValue(51, 51); // random ring ID
    tempItem.stats.attackSpeed = GetRandomValue(1, 10); // random attack speed value
    return tempItem;
}

Item createRandomAmulet(){
    Item tempItem{};
    tempItem.itemType = 6; // amulet
    tempItem.itemID = GetRandomValue(61, 61); // random amulet ID
    tempItem.stats.magicResistance = GetRandomValue(1, 10); // random magic resistance value
    return tempItem;
}

Item createRandomItem(){
    Item tempItem{};
    // tempItem.itemType = GetRandomValue(0, 5);
    tempItem.itemType = GetRandomValue(0, 1); // Temp code
    // if weapon
    if (tempItem.itemType == 0){
        tempItem = createRandomWeapon();
    }
    // if shield
    else if (tempItem.itemType == 1){
        tempItem = createRandomShield();
    }
    // if armor
    else if (tempItem.itemType == 2){
        tempItem = createRandomArmor();
    }
    // if consumable
    else if (tempItem.itemType == 3){
        tempItem = createRandomConsumable();
    }
    // if trinket
    else if (tempItem.itemType == 4){
        tempItem = createRandomTrinket();
    }
    // if ring
    else if (tempItem.itemType == 5){
        tempItem = createRandomRing();
    }
    // if amulet
    else if (tempItem.itemType == 6){
        tempItem = createRandomAmulet();
    }
    return tempItem;

}

Item createDefaultWeapon(){
    Item tempItem{};
    tempItem.itemType = 0; // weapon
    tempItem.itemID = 6; // default weapon ID
    tempItem.notSelectedTexture = LoadTexture("Inventory\\Items\\Weapons\\DaggerCommon.png");
    tempItem.selectedTexture = LoadTexture("Inventory\\Items\\Weapons\\Selected\\DaggerCommon.png");
    tempItem.texture = tempItem.notSelectedTexture;
    tempItem.size.width = 32;
    tempItem.size.height = 32;
    tempItem.stats.damage = 5; // default damage value
    tempItem.isEquippable = true;
    tempItem.isEquipped = true;
    return tempItem;
};