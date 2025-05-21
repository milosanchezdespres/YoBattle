#pragma once

#include "../../RetroCS/RetroCS.h"

#include "../Systems/ImageRenderSystem.h"

//...

namespace YoBattleGame
{
    namespace ECS
    {
        struct UIBOX1 : public Entity
        {
            UIBOX1 () : Entity()
            {
                add<Image>("background");

                get<Image>("background")->texture_alias = "uibox1";
                get<Image>("background")->scale_h = 10;
                get<Image>("background")->scale_v = 17;

                upload_to<ImageRenderSystem, Image>(Game::instance().scene(), "background");

                disable();
            }

            void place(float x, float y)
            {
                get<Image>("background")->x = x;
                get<Image>("background")->y = y;
            }

            void enable() { get<Image>("background")->enabled = true; }
            void disable() { get<Image>("background")->enabled = false; }
            bool is_enabled() { return get<Image>("background")->enabled; }
            bool is_disabled() { return !get<Image>("background")->enabled; }
        };
    }
}
