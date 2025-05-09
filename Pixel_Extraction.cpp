#include "Raylib\raylib\src\raylib.h"
#include "Raylib\raylib\src\raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include "Textures.h"
#include "Walls.h"
#include "Pathfinder.h"
#include "Inventory.h"
#include "nlohmann\json.hpp"
#include <string>
#include <fstream>
// #include <filesystem>




main(){

    using json = nlohmann::json;

    int windowSizeScaleX = 2;
    int windowSizeScaleY = 2;
    int window_dimensions[2] = {768 * windowSizeScaleX, 768 * windowSizeScaleY};
    InitWindow(window_dimensions[0], window_dimensions[1], "Dungeon Extraction");
    SetExitKey(0);

    // Dungeon Map
    Texture2D dungeon_map = LoadTexture("Dungeon_Tileset\\Dungeon_Map.png");
    Texture2D dungeon_background = LoadTexture("Dungeon_Tileset\\Dungeon_Background.png");
    Vector2 mapPos = {0.0, 0.0};
    
    // Inventory
    Texture2D inventoryTexture = LoadTexture("Inventory\\Inventory.png");
    Inventory inventory(inventoryTexture, window_dimensions[0], window_dimensions[1]);
    inventory.createDefaultItems();

    Rectangle mainWalls[2] = {
        getWall(22, 1),
        getWall(1, 22)
        // {0.0, 0.0, 128.0 * 22, 128.0},
        // {0.0, 0.0, 128.0, 128.0 * 22}, 

    };

    Rectangle innerWalls[] = {
        getWall(2, 3),
        getWall(2, 4),
        getWall(2, 6),
        getWall(2, 10),
        getWall(4, 1),
        getWall(10, 1)
    };

    Wall walls[] = {
        {mainWalls[0], 1.0f, 1.0f, 0.0f, 0.0f}, // Top Wall
        {mainWalls[1], 1.0f, 1.0f, 0.0f, 0.0f}, // Left Wall
        {mainWalls[0], 1.0f, 22.0f, 0.0f, 0.0f}, // Bottom Wall
        {mainWalls[1], 22.0f, 1.0f, 0.0f, 0.0f}, // Right Wall
        {innerWalls[1], 13.0f, 1.0f, 0.0f, 0.0f},
        {innerWalls[5], 2.0f, 4.0f, 0.0f, 0.0f},
        {innerWalls[0], 10.0f, 6.0f, 0.0f, 0.0f},
        {innerWalls[5], 13.0f, 6.0f, 0.0f, 0.0f},
        {innerWalls[5], 1.0f, 8.0f, 0.0f, 0.0f},
        {innerWalls[4], 14.0f, 8.0f, 0.0f, 0.0f},
        {innerWalls[3], 18.0f, 8.0f, 0.0f, 0.0f},
        {innerWalls[2], 16.0f, 16.0f, 0.0f, 0.0f},
    };

    int wallCount = sizeof(walls)/sizeof(walls[0]);

    SetTargetFPS(60);

    // Textures
    Texture2D candel_1_textures[4] = {LoadTexture("Dungeon_Tileset\\Props\\candlestick_1_1.png"), 
                    LoadTexture("Dungeon_Tileset\\Props\\candlestick_1_2.png"), 
                    LoadTexture("Dungeon_Tileset\\Props\\candlestick_1_3.png"), 
                    LoadTexture("Dungeon_Tileset\\Props\\candlestick_1_4.png")};
    
    Textures player_textures = {LoadTexture("Characters\\Main Character\\enemies-skeleton1_idle.png"),
                                        LoadTexture("Characters\\Main Character\\enemies-skeleton1_movement.png"),
                                        LoadTexture("Characters\\Main Character\\enemies-skeleton1_attack.png"),
                                        LoadTexture("Characters\\Main Character\\enemies-skeleton1_death.png"), 
                                        8, 1.0/8.0, {7, 20}, 17};
    
    Textures enemy_skeleton2_textures = {LoadTexture("Characters\\Enemy characters\\enemies-skeleton2_idle.png"), 
                                    LoadTexture("Characters\\Enemy characters\\enemies-skeleton2_movement.png"),
                                    LoadTexture("Characters\\Enemy characters\\enemies-skeleton2_attack.png"),
                                    LoadTexture("Characters\\Enemy characters\\enemies-skeleton2_death.png"),
                                    15, 1.0/7.0, {6, 11}, 15};
    
    // Props
    const int prop_count = 2;
    Prop props[prop_count]{
        Prop(candel_1_textures, Vector2{128.0f * 4, 128.0f * 2 - 32.0f}, 0.2f),
        Prop(candel_1_textures, Vector2{128.0f * 8, 128.0f * 3 - 32.0f}, 0.2f)
    };

    // Enemies
    const int enemy_count = 3;
    Enemy enemies[enemy_count]{
        Enemy(Vector2{128.0f * 4, 128.0f * 4}, enemy_skeleton2_textures, 3.0f, 3.0f),
        Enemy(Vector2{128.0f * 8, 128.0f * 5}, enemy_skeleton2_textures, 3.0f, 3.0f),
        Enemy(Vector2{128.0f * 10, 128.0f * 12}, enemy_skeleton2_textures, 3.0f, 3.0f)
    };

    Rectangle wallRecs_p[wallCount];
    for (int j = 0; j < wallCount; j++){
        wallRecs_p[j] = walls[j].rec;
    }

    // Player
    Vector2 startingSpot = {3.0f * 128.0f, 2.0f * 128.0f};
    Character player(window_dimensions[0], window_dimensions[1], player_textures, 20.0f, 1.0f, wallCount, wallRecs_p, startingSpot);

    for (int i = 0; i < wallCount; i++){
        wallRecs_p[i].x = player.getWorldPos().x + 128 * walls[i].xMultiplier + walls[i].xOffset;
        wallRecs_p[i].y = player.getWorldPos().y + 128 * walls[i].yMultiplier + walls[i].yOffset;
    }
    Pathfinder pathfinder(2, wallCount, 32, 24, wallRecs_p, 128, windowSizeScaleX, windowSizeScaleY);
    pathfinder.createGrid(player.getCollisionRec(), player.getWorldPos());
    player.setPath(&pathfinder);

    // 768 / 32 = 24

    // Enemies commented out for now
    for (int i = 0; i < enemy_count; i++){
        enemies[i].setTarget(&player);
    }

    // Strings
    std::string player_health = "Health: ";
    std::string player_level = "Level: ";
    std::string player_experience = "Experience: ";
    float life = 0.0f;

    bool mainMenuOpen = true;
    bool HubOpen = false;
    bool gameOpen = false;
    bool startingNewGame = false;
    unsigned char startingGameTransparency = 0;
    bool startingTransparency = false;

    // Main Menu Text
    std::string title = "Pixel Extraction";
    float titleWidth = MeasureText(title.c_str(), 80);
    float titleHeight = MeasureText(title.c_str(), 1);
    Vector2 titlePos = {window_dimensions[0]/2.0f - static_cast<float>(titleWidth) / 2.0f, window_dimensions[1]/8.0f - static_cast<float>(titleHeight) / 2.0f};
    int spacing = 200;
    std::string loadGame = "Load Game";
    float loadGameWidth = MeasureText(loadGame.c_str(), 60);
    float loadGameHeight = MeasureText(loadGame.c_str(), 1);
    Vector2 loadGamePos = {window_dimensions[0]/4.0f - static_cast<float>(loadGameWidth) / 2.0f, window_dimensions[1]/2.0f - static_cast<float>(loadGameHeight / 2)};
    Color loadGameColor = WHITE;
    std::string startGame = "New Game";
    float startGameWidth = MeasureText(startGame.c_str(), 60);
    float startGameHeight = MeasureText(startGame.c_str(), 1);
    Vector2 startGamePos = {window_dimensions[0]/4.0f - static_cast<float>(startGameWidth) / 2.0f, window_dimensions[1]/2.0f - static_cast<float>(startGameHeight / 2 + loadGameHeight + spacing)};
    Color startGameColor = WHITE;
    std::string exitGame = "Exit Game";
    float exitGameWidth = MeasureText(exitGame.c_str(), 60);
    float exitGameHeight = MeasureText(exitGame.c_str(), 1);
    Vector2 exitGamePos = {window_dimensions[0]/4.0f - static_cast<float>(exitGameWidth) / 2.0f, window_dimensions[1]/2.0f - static_cast<float>(exitGameHeight / 2 - loadGameHeight - spacing)};
    Color exitGameColor = WHITE;

    // Error Text
    std::string noMoreSaves = "No more save files!";
    Vector2 noMoreSavesSize = MeasureTextEx(GetFontDefault(), noMoreSaves.c_str(), 60, 1.0f);
    noMoreSavesSize.x = MeasureText(noMoreSaves.c_str(), 60);
    Vector2 noMoreSavesPos = {window_dimensions[0]/2.0f - noMoreSavesSize.x / 2.0f, window_dimensions[1]/5.0f * 4 - noMoreSavesSize.y / 2.0f};
    unsigned char noMoreSavesTransparency = 0;
    bool noMoreSavesOpen = false;
    int bordering = 15;

    // Starting New Game name creation
    std::string prompt = "Name your encampment: ";
    // float promptWidth = MeasureText(prompt.c_str(), 60);
    // float promptHeight = MeasureText(prompt.c_str(), 1);
    Vector2 promptSize = MeasureTextEx(GetFontDefault(), prompt.c_str(), 60, 1.0f);
    Vector2 promptPos = {window_dimensions[0]/2.0f - promptSize.x / 2.0f, window_dimensions[1]/4.0f - promptSize.y / 2.0f};
    std::string finishTyping = "Press Enter to finish";
    // float finishTypingWidth = MeasureText(finishTyping.c_str(), 60);
    // float finishTypingHeight = MeasureText(finishTyping.c_str(), 1);
    Vector2 finishTypingSize = MeasureTextEx(GetFontDefault(), finishTyping.c_str(), 60, 1.0f);
    Vector2 finishTypingPos = {window_dimensions[0]/2.0f - finishTypingSize.x / 2.0f, window_dimensions[1]/4.0f * 3.0f - finishTypingSize.y / 2.0f};
    std::string nameInput = "";
    // float nameInputWidth = MeasureText(nameInput.c_str(), 60);
    // float nameInputHeight = MeasureText(nameInput.c_str(), 1);
    Vector2 nameInputSize = MeasureTextEx(GetFontDefault(), nameInput.c_str(), 60, 1.0f);
    Vector2 nameInputPos = {window_dimensions[0]/2.0f - nameInputSize.x / 2.0f, window_dimensions[1]/2.0f - nameInputSize.y / 2.0f};
    char charInput = 0;

    // std::cout << startGameHeight << std::endl;

    // Create json file to hold name of saved files
    std::string saveDirectory = "Saves";
    std::string saveFilePath = saveDirectory + "/Saves.json";
    // // Check if the directory exists
    // if (!std::filesystem::exists(saveDirectory)){
    //     std::filesystem::create_directory(saveDirectory);
    // }

    std::ifstream savefile(saveFilePath);
    if (!savefile.good()){
        std::ofstream newSavefile(saveFilePath);
        json saveData = {
            {"Saves", json::array()}
        };
        newSavefile << saveData.dump(4);
        newSavefile.close();
        // std::cout << "Saves.json file created successfully!" << std::endl;
    } else {
        // std::cout << "Saves.json file already exists!" << std::endl;
    }
    json saveData;
    savefile >> saveData;
    std::string save1 = "";
    std::string save2 = "";
    std::string save3 = "";
    int saveCount = saveData["Saves"].size();
    for (int i = 0; i < saveCount; i++){
        std::cout << saveData["Saves"][i] << std::endl;
        if (i == 0){
            save1 = saveData["Saves"][i];
        }
        else if (i == 1){
            save2 = saveData["Saves"][i];
        }
        else if (i == 2){
            save3 = saveData["Saves"][i];
        }
    }
    savefile.close();

    // Start Game Loop
    while (!WindowShouldClose()){
        while (!WindowShouldClose() && mainMenuOpen){
            // mainMenuOpen = false;
            // gameOpen = true;
            BeginDrawing();
            ClearBackground(BLACK);
            if (startingNewGame){
                charInput = GetKeyPressed();
                if (charInput == KEY_LEFT_SHIFT || charInput == KEY_RIGHT_SHIFT){
                    charInput = GetKeyPressed();
                }
                DrawText(prompt.c_str(), promptPos.x, promptPos.y, 60, WHITE);
                DrawText(finishTyping.c_str(), finishTypingPos.x, finishTypingPos.y, 60, WHITE);
                DrawText(nameInput.c_str(), nameInputPos.x, nameInputPos.y, 60, WHITE);
                // append Letter to nameInput
                if (IsKeyPressed(KEY_BACKSPACE)){
                    if (nameInput.length() > 0){
                        nameInput.pop_back();
                    }
                    // nameInputSize.x = MeasureText(nameInput.c_str(), 60);
                    // nameInputSize.y = MeasureText(nameInput.c_str(), 1);
                    nameInputSize = MeasureTextEx(GetFontDefault(), nameInput.c_str(), 60, 1.0f);
                    nameInputPos = {window_dimensions[0]/2.0f - nameInputSize.x / 2.0f, window_dimensions[1]/2.0f - nameInputSize.y / 2.0f};
                }
                else if (IsKeyPressed(KEY_ENTER)){
                    if (nameInput.length() > 0){
                        // Take the current saveData and add the new save to it
                        std::ifstream loadfile(saveFilePath);
                        json saveData;
                        loadfile >> saveData;
                        loadfile.close();
                        
                        // Save Game
                        // json saveData;
                        json newSave = nameInput;
                        saveData["Saves"].push_back(newSave);
                        std::ofstream savefile(saveFilePath);
                        savefile << saveData.dump(4);
                        savefile.close();

                        // Create a new save file
                        std::string gameSaveFilePath = saveDirectory + "/" + nameInput + ".json";
                        std::ifstream newSaveFile(gameSaveFilePath);
                        if (!newSaveFile.good()){
                            std::ofstream gameSaveFile(gameSaveFilePath);
                            saveCount = saveData["Saves"].size();
                            json gameSaveData = {
                                {"Character", json::array()},
                                {"Collection", json::array()}
                            };
                            gameSaveFile << gameSaveData.dump(4);
                            gameSaveFile.close();
                        };
                        newSaveFile.close();

                    }

                    mainMenuOpen = false;
                    gameOpen = true;
                }
                else if (IsKeyPressed(KEY_SPACE)){
                    if (nameInput.length() < 16){
                        nameInput += " ";
                        nameInputSize = MeasureTextEx(GetFontDefault(), nameInput.c_str(), 60, 1.0f);
                        nameInputPos = {window_dimensions[0]/2.0f - nameInputSize.x / 2.0f, window_dimensions[1]/2.0f - nameInputSize.y / 2.0f};
                    }
                }
                else if (IsKeyPressed(charInput)){
                    if (nameInput.length() < 16){
                        if (charInput >= 60 && charInput <= 90){
                            if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)){
                                nameInput += static_cast<char>(charInput);
                            }
                            else {
                                nameInput += static_cast<char>(charInput + 32);
                            }
                            nameInputSize = MeasureTextEx(GetFontDefault(), nameInput.c_str(), 60, 1.0f);
                            nameInputPos = {window_dimensions[0]/2.0f - nameInputSize.x / 2.0f, window_dimensions[1]/2.0f - nameInputSize.y / 2.0f};
                        }
                    }
                }

            }
            else {
                DrawText(title.c_str(), titlePos.x, titlePos.y, 80, WHITE);
                if (CheckCollisionPointRec(GetMousePosition(), Rectangle{startGamePos.x, startGamePos.y, static_cast<float>(startGameWidth), static_cast<float>(startGameHeight)})) {startGameColor = RED;}
                else {startGameColor = WHITE;}
                DrawText(startGame.c_str(), startGamePos.x, startGamePos.y, 60, startGameColor);
                if (CheckCollisionPointRec(GetMousePosition(), Rectangle{loadGamePos.x, loadGamePos.y, static_cast<float>(loadGameWidth), static_cast<float>(loadGameHeight)})) {loadGameColor = RED;}
                else {loadGameColor = WHITE;}
                DrawText(loadGame.c_str(), loadGamePos.x, loadGamePos.y, 60, loadGameColor);
                if (CheckCollisionPointRec(GetMousePosition(), Rectangle{exitGamePos.x, exitGamePos.y, static_cast<float>(exitGameWidth), static_cast<float>(exitGameHeight)})) {exitGameColor = RED;}
                else {exitGameColor = WHITE;}
                DrawText(exitGame.c_str(), exitGamePos.x, exitGamePos.y, 60, exitGameColor);

                if (startingTransparency){
                    DrawRectangle(0, 0, window_dimensions[0], window_dimensions[1], Color{0, 0, 0, startingGameTransparency});
                    if (startingGameTransparency >= 255){
                        startingGameTransparency = 255;
                        startingNewGame = true;
                    }
                    else {
                        startingGameTransparency += 5;
                    }
                }

                if (noMoreSavesOpen){
                    DrawRectangle(noMoreSavesPos.x - bordering, noMoreSavesPos.y - bordering, noMoreSavesSize.x + bordering * 2, noMoreSavesSize.y + bordering * 2, Color{230, 41, 55, noMoreSavesTransparency});
                    DrawText(noMoreSaves.c_str(), noMoreSavesPos.x, noMoreSavesPos.y, 60, Color{255, 255, 255, noMoreSavesTransparency});
                    if (noMoreSavesTransparency <= 0){
                        noMoreSavesTransparency = 0;
                        noMoreSavesOpen = false;
                    }
                    else {
                        noMoreSavesTransparency -= 5;
                    }
                }

                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && startingTransparency == false){
                    if (CheckCollisionPointRec(GetMousePosition(), Rectangle{startGamePos.x, startGamePos.y, startGameWidth, startGameHeight})){
                        std::ifstream savefile(saveFilePath);
                        json saveData;
                        savefile >> saveData;
                        savefile.close();
                        // std::cout << saveData["Saves"].size() << std::endl;
                        if (saveData["Saves"].size() <= 2){
                            startingTransparency = true;
                        }
                        else {
                            noMoreSavesOpen = true;
                            noMoreSavesTransparency = 255;
                        }
                        // startingTransparency = true;
                    }
                    else if (CheckCollisionPointRec(GetMousePosition(), Rectangle{loadGamePos.x, loadGamePos.y, loadGameWidth, loadGameHeight})){
                        // Load Game
                    }
                    else if (CheckCollisionPointRec(GetMousePosition(), Rectangle{exitGamePos.x, exitGamePos.y, exitGameWidth, exitGameHeight})){
                        CloseWindow();
                        return 0;
                    }
                }
                
            }


            EndDrawing();
        }
        while (!WindowShouldClose() && HubOpen){
            // Hub Menu
        }
        while (!WindowShouldClose() && gameOpen){
            BeginDrawing();
            ClearBackground(WHITE);

            // Temporary Code
            if(IsKeyPressed(KEY_H)){
                inventory.addItem(createRandomItem());
                if (inventory.getItemCount() > 4){
                    // int breakpoint = 0;
                    // breakpoint;
                }
            }

            mapPos = player.getWorldPos();


            // Draw Map
            DrawTextureEx(dungeon_background, Vector2 {0.0, 0.0}, 0.0, 4.0, WHITE);
            DrawTextureEx(dungeon_map, mapPos, 0.0, 4.0, WHITE);

            // Check for collisions
            for (int i = 0; i < wallCount; i++){
                if (CheckCollisionRecs(player.getCollisionRec(), walls[i].rec)){
                    player.undoMovement();
                    break;
                }
            }
            for (int i = 0; i < prop_count; i++){
                if (CheckCollisionRecs(player.getCollisionRec(), props[i].GetCollisionRec())){
                    player.undoMovement();
                    break;
                }
            }
            
            for (int i = 0; i < enemy_count; i++){
                Rectangle wallRecs[wallCount];
                for (int j = 0; j < wallCount; j++){
                    wallRecs[j] = walls[j].rec;
                }
                enemies[i].setWall(wallRecs, wallCount);
                enemies[i].tick(GetFrameTime());

                // Player Dealing damage
                if (player.getIsAttacking() && CheckCollisionRecs(player.getAttackRec(), enemies[i].getCharacterRec())){
                    for (int j = 0; j < 2; j++){
                        if (player.getFrame() == player.getAttackFrames(j) && !enemies[i].getRecieveddamage()){
                            enemies[i].recieveDamage(player.getDamage());
                            enemies[i].setRecieveddamage(true);
                            enemies[i].setFrameDamageRecieved(player.getFrame());
                            break;
                        }
                    }
                }
                if (enemies[i].getRecieveddamage() && enemies[i].getFrameDamageRecieved() != player.getFrame()){
                    enemies[i].setRecieveddamage(false);
                }

                // Player Recieving Damage
                if (enemies[i].getIsAttacking() && CheckCollisionRecs(enemies[i].getAttackRec(), player.getCharacterRec())){
                    for (int j = 0; j < 2; j++){
                        if (enemies[i].getIsAttacking() && enemies[i].getFrame() == enemies[i].getAttackFrames(j) && !enemies[i].getDealtdamage() & enemies[i].getAlive()){
                            player.recieveDamage(enemies[i].getDamage());
                            enemies[i].setDealtdamage(true);
                            enemies[i].setFrameDamageDealt(enemies[i].getFrame());
                        }
                    }
                }
                if (enemies[i].getDealtdamage() && enemies[i].getFrameDamageDealt() != enemies[i].getFrame()){
                    enemies[i].setDealtdamage(false);
                }
            }

            for (int i = 0; i < prop_count; i++){
                // Draws Props
                if (player.getCollisionRec().y >= props[i].GetCollisionRec().y){
                    props[i].Render(mapPos);
                    // update prop animation
                    props[i].updateAnimation(GetFrameTime());
                };
            };

            player.tick(GetFrameTime());

            for (int i = 0; i < prop_count; i++){
                // Draws Props
                if (player.getCollisionRec().y < props[i].GetCollisionRec().y){
                    props[i].Render(mapPos);
                    // update prop animation
                    props[i].updateAnimation(GetFrameTime());
                };
            };        

            for (int i = 0; i < wallCount; i++){
                walls[i].rec.x = player.getWorldPos().x + 128 * walls[i].xMultiplier + walls[i].xOffset;
                walls[i].rec.y = player.getWorldPos().y + 128 * walls[i].yMultiplier + walls[i].yOffset;
            }

            if (!player.getAlive()){
                DrawText("You Died", window_dimensions[0]/2 - 170, window_dimensions[1]/2 - 80, 80, RED);
            }

            player_health = "Health: ";
            life = player.getLife();
            DrawText(player_health.append(std::to_string(life), 0, 4).c_str(), 55, 55.f, 40, RED);
            // DrawText(player_level.append(std::to_string(player.getLevel())).c_str(), 10, 40, 20, RED);
            // DrawText(player_experience.append(std::to_string(player.getExperience())).c_str(), 10, 70, 20, RED);
            
            pathfinder.drawGrid();
            //display gvalue text over the tiles.
            // for (int i = 0; i < pathfinder.getHeight(); i++){
            //     for (int j = 0; j < pathfinder.getWidth(); j++){
            //         DrawText(std::to_string(pathfinder.getGvalue(j, i)).c_str(), j * 128 / 2 + mapPos.x, i * 128 / 2 + mapPos.y, 10, BLUE);
            //     }
            // }
            // for (int i = 0; i < enemy_count; i++){
            //     enemies[i].toTarget();
            // }
            for (int i = 0; i < enemy_count; i++){
                if (enemies[i].openInventoryCheck()){
                    inventory.OpenInventory();
                    inventory.OpenSubInventory();
                    inventory.setEnemy(&enemies[i]);
                }
            }
            if (player.getAlive()){
                inventory.DrawInventory();
            }
            else {
                inventory.CloseInventory();
            }
            // inventory.getIsHeldItemInSubInventory();
            // inventory.getIsSubInventoryOpen();
            // inventory.getISItemHeld();
            // inventory.getHeldItemIndex();
            EndDrawing();
        }
    }
    CloseWindow();
    // player.~Character();
}