#pragma once

#include "../../RetroCS/RetroCS.h"

#include "BaseVerticalMenu.h"
//...

namespace YoBattleGame
{
    namespace ECS
    {
        struct StartMenu : public BaseVerticalMenu
        {
            BaseUI* bag_ui;

            StartMenu () : BaseVerticalMenu() { bag_ui = nullptr; }

            void test(string testvar) { cout << testvar << endl; }

            void open_bag() { if(bag_ui != nullptr && bag_ui->is_disabled()) bag_ui->enable(); }

            void OnChoiceAdd() override
            {
                add_choice("robodex", &StartMenu::test, string("robodex"));
                add_choice("team", &StartMenu::test, string("team"));
                add_choice("bag", &StartMenu::open_bag);
                add_choice("save", &StartMenu::test, string("save"));
                add_choice("quit", &StartMenu::test, string("quit"));
            }

            void OnDisable() override
            {
                BaseVerticalMenu::OnDisable();

                if(bag_ui != nullptr && !bag_ui->refuse_external_disabling) bag_ui->disable();
            }

            void OnPressConfirm() override
            {
                if(bag_ui != nullptr && bag_ui->is_enabled() && !is_current_choice("bag")) { bag_ui->disable(); }

                //...
            }
        };
    }
}
