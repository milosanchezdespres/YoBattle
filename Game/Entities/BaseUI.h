#pragma once

#include "../../RetroCS/RetroCS.h"

#include "../Systems/ImageRenderSystem.h"
#include "../Systems/UIRenderSystem.h"

//...

namespace YoBattleGame
{
    namespace ECS
    {
        struct UIChoice {
            int index;
            std::string label;
            std::function<void()> action;

            void set(std::function<void()> cb) { action = std::move(cb); }

            void execute() {
                if (action) action();
            }
        };

        struct BaseUI : public Entity
        {
            vector<UIChoice*> choices;
            int previous_selected_choice;
            int selected_choice;
            bool choice_confirmed;

            bool freeze_events;

            int font_size;
            Color font_color;

            int choice_padding_h = 10;
            int choice_padding_v = 10;

            bool refuse_external_disabling;
            bool execute_on_select;
            bool reset_selection_cursor_on_disabling;

            BaseUI () : Entity()
            {
                add<Image>("background");
                upload_to<ImageRenderSystem, Image>(Game::instance().scene(), "background");
                upload_to<UIRenderSystem, Image>(Game::instance().scene(), "background");

                font_size = 20;
                font_color = WHITE;

                freeze_events = false;
                refuse_external_disabling = false;
                execute_on_select = false;

                disable();
            }

            void init() { OnInit(); }
            virtual void OnInit() {}

            virtual void fill_screen_width() { get<Image>("background")->scale_h = Game::instance().width / (float) Game::instance().texture(get<Image>("background")->texture_alias).width; }
            virtual void fill_screen_height() { get<Image>("background")->scale_v = Game::instance().height / (float) Game::instance().texture(get<Image>("background")->texture_alias).height; }

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
            void addChoice(std::string label, Ret (T::*method)(Args...), T* obj, Args&&... args)
            {
                auto choice = new UIChoice();

                auto args_tuple = std::make_tuple(std::decay_t<Args>(args)...);

                choice->set([obj, method, args_tuple = std::move(args_tuple)]() mutable {
                    std::apply([obj, method](auto&&... unpacked_args) {
                        (obj->*method)(std::forward<decltype(unpacked_args)>(unpacked_args)...);
                    }, args_tuple);
                });

                choice->index = static_cast<int>(choices.size());
                choice->label = std::move(label);
                choices.push_back(choice);
            }

            UIChoice* choice(int index) { return choices[index]; }

            bool is_open(BaseUI* ui) { return ui != nullptr && ui->is_enabled(); }
            bool can_be_disabled(BaseUI* ui) { return ui != nullptr && ui->is_enabled(); }
            bool can_be_disabled_externally(BaseUI* ui) { return ui != nullptr && ui->is_enabled() && !ui->refuse_external_disabling; }

            virtual void __draw_choice(UIChoice* _choice) {}
            void display_choices() { for(UIChoice* choice : choices) { if(is_enabled()){ __draw_choice(choice); } } }

            void extra_events(float delta) override { if(!freeze_events) { OnEvents(delta); } }
            void extra_draw() override { display_choices(); }

            virtual void OnEvents(float delta) {}
            virtual void OnChoiceAdd() {}
        };
    }
}
