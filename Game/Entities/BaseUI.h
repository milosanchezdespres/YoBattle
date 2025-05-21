#pragma once

#include "../../RetroCS/RetroCS.h"

#include "../Systems/ImageRenderSystem.h"

//...

namespace YoBattleGame
{
    namespace ECS
    {
        struct BaseUI : public Entity
        {
            BaseUI () : Entity()
            {
                add<Image>("background");
                upload_to<ImageRenderSystem, Image>(Game::instance().scene(), "background");

                disable();
            }

            virtual void fill_screen_width() { get<Image>("background")->scale_h = Game::instance().width / (float) Game::instance().texture("uibox1").width; }
            virtual void fill_screen_height() { get<Image>("background")->scale_v = Game::instance().height / (float) Game::instance().texture("uibox1").height; }

            virtual void place(float x, float y)
            {
                get<Image>("background")->x = x;
                get<Image>("background")->y = y;
            }

            virtual void enable() { get<Image>("background")->enabled = true; }
            virtual void disable() { get<Image>("background")->enabled = false; }
            virtual bool is_enabled() { return get<Image>("background")->enabled; }
            virtual bool is_disabled() { return !get<Image>("background")->enabled; }
        };
    }
}
