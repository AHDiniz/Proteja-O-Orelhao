#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"
#include "core/core.hpp"
#include "rendering/circlerenderer.hpp"
#include "player/playermovement.hpp"
#include "physics/physics.hpp"

int main(void)
{
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Proteja o Orelhão!!!");
    ToggleFullscreen();
    SetTargetFPS(60);

    // TODO: Game initialization function here...
    Core::Transform2DParser transform2DParser;
    Rendering::CircleRendererParser circleRendererParser;
    Player::PlayerMovementParser playerMovementParser;
    Physics::CircleColliderParser circleRendererParser;
    Physics::RectangleColliderParser rectRendererParser;
    Physics::RigidbodyParser rigidbodyParser;

    std::map<std::string, Core::IComponentParser*> parsers;
    parsers["Transform2D"] = &transform2DParser;
    parsers["CircleRenderer"] = &circleRendererParser;
    parsers["PlayerMovement"] = &playerMovementParser;
    parsers["CircleRenderer"] = &circleRendererParser;
    parsers["RectangleCollider"] = &rectRendererParser;
    parsers["Rigidbody"] = &rigidbodyParser;

    Core::Scene testScene("assets/scenes/test.json", parsers);

    Core::Game *game = Core::Game::Instance();

    game->AddScene(&testScene);

    game->Start();
    
    while (!WindowShouldClose())
    {
        // TODO: Game update function here...
        game->Update();

        // Drawing here:
        BeginDrawing();
        {
            ClearBackground(WHITE);

            game->Render();
        }
        EndDrawing();
    }

    game->Finish();

    CloseWindow();

    return EXIT_SUCCESS;
}
