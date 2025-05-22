#pragma once

#include "../../../RetroCS/RetroCS.h"

#include "../Entities/Player.h"
#include "../Systems/AnimationSystem.h"

namespace YoKard
{
    namespace ECS
    {
        struct DebugMap : public Scene
        {
            DebugMap() : Scene() { }

            void OnEnter() override
            {
                window().background_color = BLUE;

                game()->load<texture>("player");
                //...

                attach<AnimationSystem>();
                //...

                //add<Player>();
                //get<Player>()->get<Image>()->scale = 10;
                //get<Player>()->get<Image>()->x = 450;
                //get<Player>()->get<Image>()->y = 0;

                int playersPerRow = 12;
                int totalPlayers = 150;
                int spacingX = 164;
                int spacingY = 200; // Adjust vertical spacing as needed
                int startY = 0;

                for (int i = 0; i < totalPlayers; i++)
                {
                    add<Player>("player" + to_string(i));
                    auto image = get<Player>("player" + to_string(i))->get<Image>();
                    image->scale = 10;

                    // Calculate x and y for grid layout
                    int col = i % playersPerRow;  // column number (0 to 7)
                    int row = i / playersPerRow;  // row number

                    image->x = col * spacingX;
                    image->y = startY + row * spacingY;
                }
            }

            void OnExit() override { }
        };
    }
}