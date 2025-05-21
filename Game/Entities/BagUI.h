#pragma once

#include "../../RetroCS/RetroCS.h"

#include "BaseUI.h"
//...

namespace YoBattleGame
{
    namespace ECS
    {
        struct BagUI : public BaseUI
        {
            BaseUI* start_menu;

            BagUI () : BaseUI()
            {
                get<Image>("background")->texture_alias = "whitebackground1";
                fill_screen_width();
                fill_screen_height();

                get<Image>("background")->x = -163;
                get<Image>("background")->y = -48;

                start_menu = nullptr;
            }

            void OnEvents(float delta) override
            {
                if(Game::instance().is_pressed("cancel"))
                {
                    if(start_menu != nullptr)
                    {
                        start_menu->enable();
                        disable();
                    }
                }
            }

            void OnEnable() override
            {
                if(start_menu != nullptr && start_menu->is_enabled())
                {
                    refuse_external_disabling = true;

                    start_menu->disable();

                    refuse_external_disabling = false;
                }
            }
        };
    }
}