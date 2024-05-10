#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "character.h"
#include "prop.h"
#include "enemy.h"
#include <string>
using namespace std;

int main()
{
    const int windowWidth{500}; // 384
    const int windowHeight{500};
    InitWindow(windowWidth, windowHeight, "Dagmara's game");
    SetTargetFPS(60);

    Texture2D map = LoadTexture("nature_tileset/map.png");
    Vector2 mapPosition{0.0, 0.0}; // lewy gorny rog
    // skaluje szybkosc ruchu planszy
    const float mapscale{4.0f};

    Character knight{windowWidth, windowHeight};

    Prop rock{Vector2{0.f, 0.f}, LoadTexture("nature_tileset/Rock.png")};

    Enemy goblin{Vector2{0.f, 0.f}, LoadTexture("characters/goblin_idle_spritesheet.png"),
                 LoadTexture("characters/goblin_run_spritesheet.png")};
    Enemy goblin1{Vector2{300.f, 400.f}, LoadTexture("characters/goblin_idle_spritesheet.png"),
                  LoadTexture("characters/goblin_run_spritesheet.png")};

    Enemy slime{Vector2{500.f, 700.f}, LoadTexture("characters/slime_idle_spritesheet.png"),
                LoadTexture("characters/slime_run_spritesheet.png")};

    Enemy slime1{Vector2{450.f, 800.f}, LoadTexture("characters/slime_idle_spritesheet.png"),
                 LoadTexture("characters/slime_run_spritesheet.png")};

    Enemy goblin2{Vector2{800.f, 900.f}, LoadTexture("characters/goblin_idle_spritesheet.png"),
                  LoadTexture("characters/goblin_run_spritesheet.png")};

    Enemy goblin3{Vector2{100.f, 20.f}, LoadTexture("characters/goblin_idle_spritesheet.png"),
                  LoadTexture("characters/goblin_run_spritesheet.png")};

    Enemy goblin4{Vector2{750.f, 200.f}, LoadTexture("characters/goblin_idle_spritesheet.png"),
                  LoadTexture("characters/goblin_run_spritesheet.png")};

    Enemy goblin5{Vector2{980.f, 0.f}, LoadTexture("characters/goblin_idle_spritesheet.png"),
                  LoadTexture("characters/goblin_run_spritesheet.png")};

    Enemy slime2{Vector2{1450.f, 900.f}, LoadTexture("characters/slime_idle_spritesheet.png"),
                 LoadTexture("characters/slime_run_spritesheet.png")};

    Enemy slime3{Vector2{1800.f, 970.f}, LoadTexture("characters/slime_idle_spritesheet.png"),
                 LoadTexture("characters/slime_run_spritesheet.png")};

    Enemy slime4{Vector2{459.f, 830.f}, LoadTexture("characters/slime_idle_spritesheet.png"),
                 LoadTexture("characters/slime_run_spritesheet.png")};

    Enemy slime5{Vector2{1239.f, 160.f}, LoadTexture("characters/slime_idle_spritesheet.png"),
                 LoadTexture("characters/slime_run_spritesheet.png")};

    Enemy slime6{Vector2{203.f, 801.f}, LoadTexture("characters/slime_idle_spritesheet.png"),
                 LoadTexture("characters/slime_run_spritesheet.png")};

    Enemy *enemies[]{
        &goblin, &slime, &goblin1, &slime1, &goblin2, &goblin3, &goblin4, &goblin5, &slime2, &slime3, &slime4, &slime5, &slime6};
    for (auto enemy : enemies)
    {
        enemy->setTarget(&knight);
    }

    goblin.setTarget(&knight);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        mapPosition = Vector2Scale(knight.getWorlspos(), -1.f); // przesuwamy swiat przez mnozenie przez -1

        DrawTextureEx(map, mapPosition, 0.0, 4.0, WHITE);
        rock.Rendering(knight.getWorlspos());
        int how{13}; // Initialize outside the loop

        for (auto enemy : enemies)
        {
            if (!enemy->getAlive())
                how -= 1;
        }

        if (how == 0)
        {
            DrawText("You won!", 55.f, 45.f, 40, BLACK);
            EndDrawing();
            continue;
        }
        if (!knight.getAlive())
        {
            DrawText("Game over!!", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        }
        else
        {
            std::string ourcharhealth = "Health: ";
            ourcharhealth.append(std::to_string(knight.getHealth()), 0, 5); // 5 cyft bo 12.34 to 5 w string
            DrawText(ourcharhealth.c_str(), 55.f, 45.f, 40, RED);
        }

        knight.tick(GetFrameTime());

        // wymiary mapy zeby postac nie wychodzila poza bialy frame
        if (knight.getWorlspos().x < 0.f or knight.getWorlspos().y < 0.f or knight.getWorlspos().x + windowWidth > map.width * mapscale or knight.getWorlspos().y + windowHeight > map.height * mapscale)
        {
            knight.undomovement(); // jezeli wyjdziemy poza mape to musimy undo charakter
        }
        for (auto enemy : enemies)
        {
            enemy->tick(GetFrameTime());
        }
        if (IsKeyDown(KEY_M))
        {
            for (auto enemy : enemies)
            {
                if (CheckCollisionRecs(enemy->getCollisionRec(), knight.getweaponcollision()))
                {
                    enemy->setAlive(false);
                }
            }
        }

        EndDrawing();
    }

    CloseWindow();
}