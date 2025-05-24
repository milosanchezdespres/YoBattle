#pragma once

#include "../../Utils/Utils.h"
#include "../../ECS/ECS.h"

namespace retrocs
{
    namespace window
    {
        bool ___window__logic_initialized;

        Scene* scene;

        struct GameLogic
        {
            GameLogic()
            {
                if (___window__logic_initialized) { throw std::runtime_error("GameData already initialized"); }
                else { ___window__logic_initialized = true; }

                scene = nullptr;
            }

            //void upload(.....component......)
            //{
                //...
                //so it can be used in draw function
                //there is a vector by textures that has all component draw there
                //this function will figure out if already added in current texture
                //if not same, remove from this texture batch, add to the new one
                //component call this function itself
            //}

            void init(Scene* entry_point)
            {
                scene = entry_point->clone(); 

                delete entry_point;
                entry_point = nullptr;

                scene->enter();
            }

            void update()
            {
                //...
                //entity states....
                //scenes systems...
            }

            void draw(Color color)
            {
                ::BeginDrawing();
                ::ClearBackground(color);

                //::BeginMode2D({ 0 });

                //::rlBegin(RL_QUADS);
                //::rlSetTexture(texture.id);

                //...
                //batch draw for all textures/registered components...

                //::rlEnd();
                //::rlSetTexture(0);

                //::EndMode2D();
                ::EndDrawing();
            }

            ~GameLogic() { }
        };
    }
}