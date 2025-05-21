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
                add<Image>("cursor");
                get<Image>("cursor")->texture_alias = "uicursor1";
                upload_to<ImageRenderSystem, Image>(Game::instance().scene(), "cursor");

                get<Image>("background")->texture_alias = "uibox1";
                get<Image>("background")->scale_h = 10;
                fill_screen_height();

                get<Image>("cursor")->scale_h = get<Image>("background")->scale_h / 2;
                get<Image>("cursor")->scale_v = get<Image>("cursor")->scale_h;
                get<Image>("cursor")->x = get<Image>("background")->x + choice_padding_h + 50;

                add_choice("yolo", &StartMenu::test, this, string("yolo ! ---------------------------------------------------------------------------------------"));
                add_choice("nope", &StartMenu::test, this, string("nope ! ---------------------------------------------------------------------------------------"));
                add_choice("delivery", &StartMenu::test, this, string("delivery ! ---------------------------------------------------------------------------------------"));
            
                font_size = 70;
                font_color = BLACK;

                choice_padding_h = (Game::instance().texture("uibox1").width * get<Image>("background")->scale_h) / 4;
                choice_padding_v = Game::instance().height / 7;

                OnDisable();//FIX
            }

            void test(string testvar) { cout << testvar << endl; }

            void OnEnable() override
            {
                get<Image>("cursor")->enabled = true;
                //...
            }

            void OnDisable() override
            {
                get<Image>("cursor")->enabled = false;
                //...

                selected_choice = 0; 
                get<Image>("cursor")->y = choice_padding_v + (choice(selected_choice)->index * 100);
            }

            void OnEvents(float delta) override
            {
                if(Game::instance().is_pressed("up"))
                {
                    selected_choice--;
                    if(selected_choice < 0) selected_choice = choices.size() - 1;
                }

                if(Game::instance().is_pressed("down"))
                {
                    selected_choice++;
                    if(selected_choice > choices.size() - 1) selected_choice = 0;
                }

                if(Game::instance().is_pressed("confirm")) { choice(selected_choice)->execute(); }
            }

            void __draw_choice(UIChoice* _choice) override
            {
                get<Image>("cursor")->y = choice_padding_v + (choice(selected_choice)->index * 100);

                DrawText(
                    _choice->label.c_str(), 
                    get<Image>("background")->x + choice_padding_h, 
                    get<Image>("background")->y + choice_padding_v + (_choice->index * 100), 
                    font_size, 
                    font_color
                );
            }
        };
    }
}
