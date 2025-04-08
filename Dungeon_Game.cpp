#include "Raylib\raylib\src\raylib.h"
#include "Raylib\raylib\src\raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include "Textures.h"
#include "Walls.h"
#include <string>

main(){
    int window_dimensions[2] = {768, 768};
    InitWindow(window_dimensions[0], window_dimensions[1], "Dungeon Game");

    // Dungeon Map
    Texture2D dungeon_map = LoadTexture("Dungeon_Tileset\\Dungeon_Map.png");
    Texture2D dungeon_background = LoadTexture("Dungeon_Tileset\\Dungeon_Background.png");
    Vector2 mapPos = {0.0, 0.0};
    
    // dungeon map dimensions 24*32 = 768
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
    const int enemy_count = 2;
    Enemy enemies[enemy_count]{
        Enemy(Vector2{128.0f * 4, 128.0f * 4}, enemy_skeleton2_textures, 3.0f, 3.0f),
        Enemy(Vector2{128.0f * 8, 128.0f * 5}, enemy_skeleton2_textures, 3.0f, 3.0f)
    };

    // Player
    Character player(window_dimensions[0], window_dimensions[1], player_textures, 9.0f, 1.0f);

    for (int i = 0; i < enemy_count; i++){
        enemies[i].setTarget(&player);
        // enemies[i].setWall(walls, wallCount);
    }

    // Strings
    std::string player_health = "Health: ";
    std::string player_level = "Level: ";
    std::string player_experience = "Experience: ";
    float life = 0.0f;

    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);


        mapPos = player.getWorldPos();


        // Draw Map
        DrawTextureEx(dungeon_background, Vector2 {0.0, 0.0}, 0.0, 1.0, WHITE);
        DrawTextureEx(dungeon_map, mapPos, 0.0, 4.0, WHITE);

        
        // DrawRectangleRec(player.getCollisionRec(), RED);

        // Check for collisions
        for (int i = 0; i < wallCount; i++){
            // DrawRectangleRec(walls[i].rec, BLUE);
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
            enemies[i].tick(GetFrameTime());
            if (CheckCollisionRecs(player.getCollisionRec(), enemies[i].getCollisionRec())){
                // player.undoMovement();
                enemies[i].undoMovement();
                enemies[i].attackPlayer();
            }
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
        
            // DrawRectangleRec(enemies[i].getCollisionRec(), RED);
        }
        // Rectangle rec = player.getCollisionRec();
        // DrawRectangleRec(player.getAttackRec(), RED);
        // DrawRectangleRec(player.getCollisionRec(), RED);
        // DrawRectangleRec(Rectangle{rec.x - 80, rec.y - 104, 112 + 112, 144}, GREEN);
        // DrawRectangleRec(Rectangle{rec.x + 80 - 112, rec.y - 104, 112 + 112, 144}, BLUE);
        // Rectangle{screenPos.x + 80, screenPos.y + 144, 112, 144 - 96}

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
        // mainWalls[0].x = player.getWorldPos().x + 128;
        // mainWalls[0].y = player.getWorldPos().y + 128;
        // mainWalls[1].x = player.getWorldPos().x + 128;
        // mainWalls[1].y = player.getWorldPos().y + 128;
        // mainWalls[2].x = player.getWorldPos().x + 128;
        // mainWalls[2].y = player.getWorldPos().y + 128 * 22;
        // mainWalls[3].x = player.getWorldPos().x + 128 * 22;
        // mainWalls[3].y = player.getWorldPos().y + 128;

        if (!player.getAlive()){
            DrawText("You Died", window_dimensions[0]/2 - 170, window_dimensions[1]/2 - 80, 80, RED);
        }

        player_health = "Health: ";
        life = player.getLife();
        DrawText(player_health.append(std::to_string(life), 0, 4).c_str(), 55, 55.f, 40, RED);
        // DrawText(player_level.append(std::to_string(player.getLevel())).c_str(), 10, 40, 20, RED);
        // DrawText(player_experience.append(std::to_string(player.getExperience())).c_str(), 10, 70, 20, RED);
        

        EndDrawing();
    }

    CloseWindow();
}