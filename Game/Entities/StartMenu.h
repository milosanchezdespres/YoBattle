#pragma once

#include "../../RetroCS/RetroCS.h"

#include "BaseUI.h"
//...

namespace YoBattleGame
{
    namespace ECS
    {
        struct StartMenu : public BaseUI
        {
            StartMenu () : BaseUI()
            {
                get<Image>("background")->texture_alias = "uibox1";
                get<Image>("background")->scale_h = 10;
                fill_screen_height();
            }
        };
    }
}
