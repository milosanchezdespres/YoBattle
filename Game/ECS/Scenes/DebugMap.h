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

                display_fps = true;
                fps_display_x = 40;
                fps_display_y = 40;
                fps_display_size = 40;

                game()->load<texture>("player");
                //...

                attach<AnimationSystem>();
                //...

                //add<Player>();
                //get<Player>()->get<Image>()->x = 0;
                //get<Player>()->get<Image>()->y = 0;

                camera().set_zoom(8);
                //camera().follow(get<Player>()->get<Image>()->x, get<Player>()->get<Image>()->y);
///*
                int playersPerRow = 24;
                int totalPlayers = 5000;
                int spacingX = 25;
                int spacingY = 25; // Adjust vertical spacing as needed
                int startY = 0;

                for (int i = 0; i < totalPlayers; i++)
                {
                    add<Player>("player" + to_string(i));
                    auto image = get<Player>("player" + to_string(i))->get<Image>();
                    //image->scale = 5;

                    // Calculate x and y for grid layout
                    int col = i % playersPerRow;  // column number (0 to 7)
                    int row = i / playersPerRow;  // row number

                    image->x = col * spacingX;
                    image->y = startY + row * spacingY;
                }
//*/
            }

            void OnExit() override { }
        };
    }
}