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

                add_choice("yolo", &StartMenu::test, this, string("yolo ! ---------------------------------------------------------------------------------------"));
                add_choice("nope", &StartMenu::test, this, string("nope ! ---------------------------------------------------------------------------------------"));
                add_choice("delivery", &StartMenu::test, this, string("delivery ! ---------------------------------------------------------------------------------------"));
            
                font_size = 70;
                font_color = BLACK;

                choice_padding_h = (Game::instance().texture("uibox1").width * get<Image>("background")->scale_h) / 4;
                choice_padding_v = Game::instance().height / 7;
            }

            void test(string testvar) { cout << testvar << endl; }

            void __display_choice(UIChoice* choice) override
            {
                DrawText(
                    choice->label.c_str(), 
                    get<Image>("background")->x + choice_padding_h, 
                    get<Image>("background")->y + choice_padding_v + (choice->index * 100), 
                    font_size, 
                    font_color
                );
            }
        };
    }
}
