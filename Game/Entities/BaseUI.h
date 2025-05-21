#pragma once

#include "../../RetroCS/RetroCS.h"

#include "../Systems/ImageRenderSystem.h"
#include "../Systems/UIRenderSystem.h"

//...

namespace YoBattleGame
{
    namespace ECS
    {
        struct UIChoice
        {
            int index;
            string label;

            function<void()> action;

            template<typename Callback, typename... Args>
            void set(Callback&& cb, Args&&... args) { action = std::bind(forward<Callback>(cb), forward<Args>(args)...); }

            void execute() { action(); }
        };

        struct BaseUI : public Entity
        {
            vector<UIChoice*> choices;
            int selected_choice;

            int font_size;
            Color font_color;

            int choice_padding_h = 10;
            int choice_padding_v = 10;

            BaseUI () : Entity()
            {
                add<Image>("background");
                upload_to<ImageRenderSystem, Image>(Game::instance().scene(), "background");
                upload_to<UIRenderSystem, Image>(Game::instance().scene(), "background");

                font_size = 20;
                font_color = WHITE;

                selected_choice = 0;

                disable();
            }

            virtual void fill_screen_width() { get<Image>("background")->scale_h = Game::instance().width / (float) Game::instance().texture("uibox1").width; }
            virtual void fill_screen_height() { get<Image>("background")->scale_v = Game::instance().height / (float) Game::instance().texture("uibox1").height; }

            virtual void place(float x, float y)
            {
                get<Image>("background")->x = x;
                get<Image>("background")->y = y;
            }

            void enable() { get<Image>("background")->enabled = true; OnEnable(); }
            void disable() { get<Image>("background")->enabled = false; OnDisable(); }
            virtual bool is_enabled() { return get<Image>("background")->enabled; }
            virtual bool is_disabled() { return !get<Image>("background")->enabled; }
            virtual void OnEnable() {}
            virtual void OnDisable() {}

            template<typename T, typename Ret, typename... Args>
            void add_choice(string label, Ret (T::*method)(Args...), T* obj, Args&&... args)
            {
                auto choice = new UIChoice();

                auto args_tuple = std::make_tuple(std::forward<Args>(args)...);

                choice->set([obj, method, args_tuple = std::move(args_tuple)]() mutable
                {
                    std::apply([obj, method](Args&&... unpacked_args)
                    {
                        (obj->*method)(std::forward<Args>(unpacked_args)...);
                    }, std::move(args_tuple));
                });

                choices.push_back(choice);

                choices[choices.size() - 1]->index = choices.size() - 1;
                choices[choices.size() - 1]->label = label;
            }

            UIChoice* choice(int index) { return choices[index]; }

            virtual void __draw_choice(UIChoice* _choice) {}
            void display_choices() { for(UIChoice* choice : choices) { if(is_enabled()){ __draw_choice(choice); } } }

            void extra_events(float delta) override { OnEvents(delta); }
            void extra_draw() override { display_choices(); }

            virtual void OnEvents(float delta) {}
        };
    }
}
