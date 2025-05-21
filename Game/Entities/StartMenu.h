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
            StartMenu () : BaseVerticalMenu() { }

            void test(string testvar) { cout << testvar << endl; }

            void OnChoiceAdd() override
            {
                add_choice("robodex", &StartMenu::test, string("robodex"));
                add_choice("team", &StartMenu::test, string("team"));
                add_choice("bag", &StartMenu::test, string("bag"));
                add_choice("save", &StartMenu::test, string("save"));
                add_choice("quit", &StartMenu::test, string("quit"));
            }
        };
    }
}
