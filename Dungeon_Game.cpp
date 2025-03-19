#include "C:/raylib/raylib/src/raylib.h"
#include "C:/raylib/raylib/src/raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"


main(){
    int window_dimensions[2] = {768, 768};
    InitWindow(window_dimensions[0], window_dimensions[1], "Dungeon Game");

    // Dungeon Map
    Texture2D dungeon_map = LoadTexture("Dungeon_Tileset\\Dungeon_Map.png");
    Texture2D dungeon_background = LoadTexture("Dungeon_Tileset\\Dungeon_Background.png");
    Vector2 mapPos = {0.0, 0.0};
    
    // dungeon map dimensions 24*32 = 768
    Rectangle mainWalls[4] = {
        {360.0, 432.0, 128 * 22, 128},
        {352.0, 384.0, 128.0, 128.0 * 22},
        {352.0, 384.0, 128.0 * 22, 128.0},
        {352.0, 384.0, 128.0, 128.0 * 22}, 

    };

    SetTargetFPS(60);

    // Textures
    Texture2D candel_1_textures[4] = {LoadTexture("Dungeon_Tileset\\Props\\candlestick_1_1.png"), 
                    LoadTexture("Dungeon_Tileset\\Props\\candlestick_1_2.png"), 
                    LoadTexture("Dungeon_Tileset\\Props\\candlestick_1_3.png"), 
                    LoadTexture("Dungeon_Tileset\\Props\\candlestick_1_4.png")};
    
    Texture2D player_textures[2] = {LoadTexture("Characters\\Main Character\\enemies-skeleton1_idle.png"), 
                                    LoadTexture("Characters\\Main Character\\enemies-skeleton1_movement.png")};
    Texture2D enemy_skeleton2_textures[2] = {LoadTexture("Characters\\Enemy characters\\enemies-skeleton2_idle.png"), 
                                    LoadTexture("Characters\\Enemy characters\\enemies-skeleton2_movement.png")};
    

    // Props
    const int prop_count = 2;
    Prop props[prop_count]{
        Prop(candel_1_textures, Vector2{128.0f * 4, 128.0f * 2 - 32.0f}),
        Prop(candel_1_textures, Vector2{128.0f * 8, 128.0f * 3 - 32.0f})
    };

    // Enemies
    const int enemy_count = 2;
    Enemy enemies[enemy_count]{
        Enemy(Vector2{128.0f * 4, 128.0f * 4}, enemy_skeleton2_textures[0], enemy_skeleton2_textures[1]),
        Enemy(Vector2{128.0f * 8, 128.0f * 5}, enemy_skeleton2_textures[0], enemy_skeleton2_textures[1])
    };

    // Player
    Character player(window_dimensions[0], window_dimensions[1], player_textures[0], player_textures[1]);

    for (int i = 0; i < enemy_count; i++){
        enemies[i].setTarget(&player);
    }

    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);


        mapPos = player.getWorldPos();


        // Draw Map
        DrawTextureEx(dungeon_background, Vector2 {0.0, 0.0}, 0.0, 1.0, WHITE);
        DrawTextureEx(dungeon_map, mapPos, 0.0, 4.0, WHITE);
        // Draw Walls
        for (int i = 0; i < prop_count; i++){
            // Draws Props
            props[i].Render(mapPos);
            // update prop animation
            props[i].updateAnimation(GetFrameTime());
        };
        
        // DrawRectangleRec(player.getCollisionRec(), RED);

        // Check for collisions
        for (int i = 0; i < 4; i++){
            if (CheckCollisionRecs(player.getCollisionRec(), mainWalls[i])){
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
                player.undoMovement();
                break;
            }
            // DrawRectangleRec(enemies[i].getCollisionRec(), RED);
        }
        
        // DrawRectangleRec(player.getCollisionRec(), RED);

        player.tick(GetFrameTime());
        mainWalls[0].x = player.getWorldPos().x + 128;
        mainWalls[0].y = player.getWorldPos().y + 128;
        mainWalls[1].x = player.getWorldPos().x + 128;
        mainWalls[1].y = player.getWorldPos().y + 128;
        mainWalls[2].x = player.getWorldPos().x + 128;
        mainWalls[2].y = player.getWorldPos().y + 128 * 22;
        mainWalls[3].x = player.getWorldPos().x + 128 * 22;
        mainWalls[3].y = player.getWorldPos().y + 128;

        EndDrawing();
    }

    CloseWindow();
}