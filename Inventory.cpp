#include "Inventory.h"
#include "Raylib\raylib\src\raylib.h"

Inventory::Inventory(Texture2D inventoryText, float windowWid, float windowHei){
    inventoryTexture = inventoryText;
    windowWidth = windowWid;
    windowHeight = windowHei;
    inventoryPos = {windowWidth - inventoryTexture.width * scale, windowHeight - inventoryTexture.height * scale};
    for (int i = 0; i < 5; i++){
        iDEquipPos[i].x = iDEquipPosReference[i].x * scale + inventoryPos.x;
        iDEquipPos[i].y = iDEquipPosReference[i].y * scale + inventoryPos.y;
    }
    for (int i = 0; i < 5; i++){
        itemsPos[i].x = itemsPosReference[i].x * scale + inventoryPos.x;
        itemsPos[i].y = itemsPosReference[i].y * scale + inventoryPos.y;
    }
}

void Inventory::IsItemSelected(){
    Vector2 mousePos = GetMousePosition();
    if (isItemHeld == true){
        if (isHeldItemInSubInventory){
            enemy->setXItemPosition(heldItemIndex, mousePos.x - inventoryPos.x - items[heldItemIndex].texture.width * scale * 2);
            enemy->setYItemPosition(heldItemIndex, mousePos.y - inventoryPos.y - items[heldItemIndex].texture.height * scale * 2);
            enemy->setItemTexture(heldItemIndex, enemy->getItem(heldItemIndex).notSelectedTexture);
        }
        else{
            items[heldItemIndex].position.x = mousePos.x - inventoryPos.x - items[heldItemIndex].texture.width * scale * 2;
            items[heldItemIndex].position.y = mousePos.y - inventoryPos.y - items[heldItemIndex].texture.height * scale * 2;
            items[heldItemIndex].texture = items[heldItemIndex].notSelectedTexture;
        }
        // Placing Held Item in Inventory
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)){
            if (subInventoryOpen == true){
                for (int x = 0; x < 5; x++){
                    for (int y = 0; y < 5; y++){
                        if (!enemy->getInventoryPos(x, y)){
                            if (isHeldItemInSubInventory && CheckCollisionPointRec(mousePos, Rectangle{itemsPos[x].x + enemy->getItem(heldItemIndex).texture.width * 2 - inventoryPos.x, itemsPos[y].y + enemy->getItem(heldItemIndex).texture.height * 2, enemy->getItem(heldItemIndex).texture.width * scale * 4, enemy->getItem(heldItemIndex).texture.height * scale * 4})){
                                enemy->setXItemPosition(heldItemIndex, x);
                                enemy->setYItemPosition(heldItemIndex, y);
                                enemy->setItemTexture(heldItemIndex, enemy->getItem(heldItemIndex).notSelectedTexture);
                                if (enemy->getItem(heldItemIndex).isHeld){enemy->toggleIsHeld(heldItemIndex);}
                                isHeldItemInSubInventory = false;
                                isItemHeld = false;
                                heldItemIndex = 99;
                                enemy->toggleInventoryPos(x, y);
                                return;
                            }
                            else if (CheckCollisionPointRec(mousePos, Rectangle{itemsPos[x].x + items[heldItemIndex].texture.width * 2 - inventoryPos.x, itemsPos[y].y + items[heldItemIndex].texture.height * 2, items[heldItemIndex].texture.width * scale * 4, items[heldItemIndex].texture.height * scale * 4})){
                                items[heldItemIndex].isEquipped = false;
                                items[heldItemIndex].isHeld = false;
                                enemy->addSpecificItem(items[heldItemIndex], x, y);
                                discardItem(heldItemIndex);
                                isItemHeld = false;
                                heldItemIndex = 99;
                                return;
                            }
                        }
                    }
                }
            }
            if (!iDEquip[items[heldItemIndex].equippedSlot] && isHeldItemInSubInventory && CheckCollisionPointRec(mousePos, Rectangle{iDEquipPos[enemy->getItem(heldItemIndex).equippedSlot].x, iDEquipPos[enemy->getItem(heldItemIndex).equippedSlot].y, enemy->getItem(heldItemIndex).texture.width * scale * 6 , enemy->getItem(heldItemIndex).texture.height * scale * 6})){
                addSpecificItem(enemy->getItem(heldItemIndex), 0, 0);
                isItemHeld = false;
                iDEquip[items[heldItemIndex].equippedSlot] = true;
                isHeldItemInSubInventory = false;
                enemy->discardItem(heldItemIndex);
                items[itemCount - 1].isEquipped = true;
                items[itemCount - 1].isHeld = false;
                heldItemIndex = 99;
                return;
            }
            else if (!iDEquip[items[heldItemIndex].equippedSlot] && CheckCollisionPointRec(mousePos, Rectangle{iDEquipPos[items[heldItemIndex].equippedSlot].x, iDEquipPos[items[heldItemIndex].equippedSlot].y, items[heldItemIndex].texture.width * scale * 6, items[heldItemIndex].texture.height * scale * 6})){
                items[heldItemIndex].isEquipped = true;
                iDEquip[items[heldItemIndex].equippedSlot] = true;
                isItemHeld = false;
                items[heldItemIndex].isHeld = false;
                heldItemIndex = 99;
                return;
            }
            else{
                for (int x = 0; x < 5; x++){
                    for (int y = 0; y < 5; y++){
                        if (itemPosInventory[x + y * 5] == false){
                            if (isHeldItemInSubInventory && CheckCollisionPointRec(mousePos, Rectangle{itemsPos[x].x + enemy->getItem(heldItemIndex).texture.width * 2, itemsPos[y].y + enemy->getItem(heldItemIndex).texture.height * 2, enemy->getItem(heldItemIndex).texture.width * scale * 4, enemy->getItem(heldItemIndex).texture.height * scale * 4})){
                                addSpecificItem(enemy->getItem(heldItemIndex), x, y);
                                enemy->discardItem(heldItemIndex);
                                heldItemIndex = itemCount - 1;
                                items[heldItemIndex].isEquipped = false;
                                isItemHeld = false;
                                items[heldItemIndex].isHeld = false;
                                items[heldItemIndex].position.x = x;
                                items[heldItemIndex].position.y = y;
                                isHeldItemInSubInventory = false;
                                itemPosInventory[x + y * 5] = true;
                                heldItemIndex = 99;
                                return;
                            }
                            else if (CheckCollisionPointRec(mousePos, Rectangle{itemsPos[x].x + items[heldItemIndex].texture.width * 2, itemsPos[y].y + items[heldItemIndex].texture.height * 2, items[heldItemIndex].texture.width * scale * 4, items[heldItemIndex].texture.height * scale * 4})){
                                items[heldItemIndex].isEquipped = false;
                                isItemHeld = false;
                                items[heldItemIndex].isHeld = false;
                                items[heldItemIndex].position.x = x;
                                items[heldItemIndex].position.y = y;
                                isHeldItemInSubInventory = false;
                                itemPosInventory[x + y * 5] = true;
                                heldItemIndex = 99;
                                return;
                            }
                        }
                    }
                }
                if (isHeldItemInSubInventory){
                    enemy->replaceItem(heldItemIndex, lastHeldItem);
                    enemy->setItemTexture(heldItemIndex, enemy->getItem(heldItemIndex).notSelectedTexture);
                    isItemHeld = false;
                    isHeldItemInSubInventory = false;
                    if (enemy->getInventoryPos(lastHeldItem.position.x, lastHeldItem.position.y) == false){
                        enemy->toggleInventoryPos(lastHeldItem.position.x, lastHeldItem.position.y);
                    }
                    heldItemIndex = 99;
                    return;
                }
                items[heldItemIndex] = lastHeldItem;
                items[heldItemIndex].isHeld = false;
                items[heldItemIndex].texture = items[heldItemIndex].notSelectedTexture;
                isItemHeld = false;
                heldItemIndex = 99;
                if (!lastHeldItem.isEquipped) {itemPosInventory[static_cast<int>(lastHeldItem.position.x + lastHeldItem.position.y * 5)] = true;}
                else {iDEquip[lastHeldItem.equippedSlot] = true;}
            }
        }
    return;
    }
    
    // seclecting items (hovering over them) and grabbing them
    for (int i = 0; i < itemCount; i++){
        items[i].texture = items[i].notSelectedTexture;
        if (items[i].isEquipped == true){
            if (CheckCollisionPointRec(mousePos, Rectangle{iDEquipPos[items[i].equippedSlot].x, iDEquipPos[items[i].equippedSlot].y, items[i].texture.width * scale * 6, items[i].texture.height * scale * 6})){
                items[i].texture = items[i].selectedTexture;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    lastHeldItem = items[i];
                    items[i].isEquipped = false;
                    iDEquip[items[i].equippedSlot] = false;
                    heldItemIndex = i;
                    isItemHeld = true;
                    items[i].isHeld = true;
                    items[i].position.x = mousePos.x - inventoryPos.x - items[i].texture.width * scale * 2;
                    items[i].position.y = mousePos.y - inventoryPos.y - items[i].texture.height * scale * 2;
                }
            }
        }
        else{
            for (int x = 0; x < 5; x++){
                for (int y = 0; y < 5; y++){
                    if (items[i].position.x == x && items[i].position.y == y && CheckCollisionPointRec(mousePos, Rectangle{itemsPos[x].x + items[i].texture.width * 2, itemsPos[y].y + items[i].texture.height * 2, items[i].texture.width * scale * 4, items[i].texture.height * scale * 4})){
                        items[i].texture = items[i].selectedTexture;
                        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                            lastHeldItem = items[i];
                            items[i].isEquipped = false;
                            heldItemIndex = i;
                            isItemHeld = true;
                            items[i].isHeld = true;
                            items[i].position.x = mousePos.x - inventoryPos.x - items[i].texture.width * scale * 2;
                            items[i].position.y = mousePos.y - inventoryPos.y - items[i].texture.height * scale * 2;
                            itemPosInventory[x + y * 5] = false;

                        }
                    }
                }
            }
        }
    }
    if (subInventoryOpen){
        for (int i = 0; i < enemy->getItemCount(); i++){
            enemy->setItemTexture(i, enemy->getItem(i).notSelectedTexture);
            if (CheckCollisionPointRec(mousePos, Rectangle{itemsPos[static_cast<int>(enemy->getItem(i).position.x)].x + enemy->getItem(i).texture.width * 2 - inventoryPos.x, itemsPos[static_cast<int>(enemy->getItem(i).position.y)].y + enemy->getItem(i).texture.height * 2, enemy->getItem(i).texture.width * scale * 4, enemy->getItem(i).texture.height * scale * 4})){
                enemy->setItemTexture(i, enemy->getItem(i).selectedTexture);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    lastHeldItem = enemy->getItem(i);
                    heldItemIndex = i;
                    isHeldItemInSubInventory = true;
                    isItemHeld = true;
                    if (enemy->getItem(i).isHeld == false) enemy->toggleIsHeld(i);
                    if (enemy->getInventoryPos(enemy->getItem(i).position.x, enemy->getItem(i).position.y)){
                        enemy->toggleInventoryPos(enemy->getItem(i).position.x, enemy->getItem(i).position.y);
                    }
                    enemy->setXItemPosition(i, mousePos.x - inventoryPos.x - enemy->getItem(i).texture.width * scale * 2);
                    enemy->setYItemPosition(i, mousePos.y - inventoryPos.y - enemy->getItem(i).texture.height * scale * 2);
                }
            }
        }
    }
}

void Inventory::DrawAbsentItems(){
    bool isEquipped[10]{};
    int itemTypes[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int i = 0; i < itemCount; i++){
        for (int j = 0; j < 10; j++){
            if (items[i].equippedSlot == itemTypes[j] && items[i].isEquipped == true) isEquipped[j] = true;
        }
    }
    if (isEquipped[0] == false){
        DrawTextureEx(weaponAbsentTexture, inventoryPos, 0.0f, scale, WHITE);
    }
    if (isEquipped[1] == false){
        DrawTextureEx(shieldAbsentTexture, inventoryPos, 0.0f, scale, WHITE);
    }
    if (isEquipped[2] == false){
        DrawTextureEx(headgearAbsentTexture, inventoryPos, 0.0f, scale, WHITE);
    }
    if (isEquipped[3] == false){
        DrawTextureEx(pantsAbsentTexture, inventoryPos, 0.0f, scale, WHITE);
    }
    if (isEquipped[4] == false){
        DrawTextureEx(ringAbsentTexture, inventoryPos, 0.0f, scale, WHITE);
    }
    if (isEquipped[5] == false){
        DrawTextureEx(ring2AbsentTexture, inventoryPos, 0.0f, scale, WHITE);
    }
    if (isEquipped[6] == false){
        DrawTextureEx(amuletAbsentTexture, inventoryPos, 0.0f, scale, WHITE);
    }
    if (isEquipped[7] == false){
        DrawTextureEx(armorAbsentTexture, inventoryPos, 0.0f, scale, WHITE);
    }
    if (isEquipped[8] == false){
        DrawTextureEx(bootAbsentTexture, inventoryPos, 0.0f, scale, WHITE);
    }
    if (isEquipped[9] == false){
        DrawTextureEx(glovesAbsentTexture, inventoryPos, 0.0f, scale, WHITE);
    }
}

void Inventory::DrawInventory(){
    if (IsKeyPressed(KEY_I)){
        if (inventoryOpen == false) inventoryOpen = true;
        else{
            inventoryOpen = false;
            subInventoryOpen = false;
        }
    }
    if (inventoryOpen == false) return;
    DrawTextureEx(inventoryTexture, inventoryPos, 0.0f, scale, WHITE);
    if (subInventoryOpen == true){
        if (!enemy->CheckCollision()){
            subInventoryOpen = false;
        }
        else{
            DrawTextureEx(leftTexture, Vector2{0, windowHeight - leftTexture.height * scale}, 0.0f, scale, WHITE);
        }
    }

    IsItemSelected();
    DrawAbsentItems();

    for (int i = 0; i < itemCount; i++){
        if (items[i].isEquipped == true){
            DrawTextureEx(items[i].texture, Vector2{iDEquipPos[items[i].itemType].x + items[i].texture.width * 2.0f, iDEquipPos[items[i].itemType].y + items[i].texture.height * 2}, 0.0f, scale * 4, WHITE);
        }
        else {
            if (!items[i].isHeld){
                DrawTextureEx(items[i].texture, Vector2{itemsPos[static_cast<int>(items[i].position.x)].x + items[i].texture.width * 2, itemsPos[static_cast<int>(items[i].position.y)].y + items[i].texture.height * 2}, 0.0f, scale * 4, WHITE);
            }
        }
    }
    if (subInventoryOpen){
        for (int i = 0; i < enemy->getItemCount(); i++){
            if (!enemy->getItem(i).isHeld){
                DrawTextureEx(enemy->getItem(i).texture, Vector2{itemsPos[static_cast<int>(enemy->getItem(i).position.x)].x + enemy->getItem(i).texture.width * 2 - inventoryPos.x, itemsPos[static_cast<int>(enemy->getItem(i).position.y)].y + enemy->getItem(i).texture.height * 2}, 0.0f, scale * 4, WHITE);
            }
        }
        if (isHeldItemInSubInventory){
            DrawTextureEx(enemy->getItem(heldItemIndex).texture, Vector2{inventoryPos.x + enemy->getItem(heldItemIndex).position.x, inventoryPos.y + enemy->getItem(heldItemIndex).position.y}, 0.0f, scale * 4, WHITE);
        }
    }
    if (isItemHeld && !isHeldItemInSubInventory){
        DrawTextureEx(items[heldItemIndex].texture, Vector2{inventoryPos.x + items[heldItemIndex].position.x, inventoryPos.y + items[heldItemIndex].position.y}, 0.0f, scale * 4, WHITE);
    }
}

void Inventory::createDefaultItems(){
    bool equippedItems[6]{};
    for (int i = 0; i < itemCount; i++){
        for (int j = 0; j < 6; j++){
            if (items[i].itemType == j && items[i].isEquipped == true){
                equippedItems[j] = true;
            }
            
        }
    }
    if (equippedItems[0] == false){
        addSpecificItem(createDefaultWeapon(), 6, 5);
        iDEquip[0] = true;
    }
    if (equippedItems[1] == false){
        // addItem(createDefaultArmor());
    }
    if (equippedItems[4] == false){
        // addItem(createDefaultRing());
    }
    if (equippedItems[5] == false){
        // addItem(createDefaultAmulet());
    }
    itemPosInventory[25] = false;
}