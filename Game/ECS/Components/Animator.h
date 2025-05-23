#pragma once

#include "../../../RetroCS/RetroCS.h"

#include "../Utils/Animation.h"

namespace YoKard
{
    namespace ECS
    {
        struct Animator : public Component
        {
            unordered_map<string, Animation*> animations;

            string previous_animation;
            string current_animation;

            Image* animated_image;
            Sprite* animated_sprite;

            bool playing;

            Animator() : Component()
            {
                animated_image = nullptr;
                animated_sprite = nullptr;
                playing = false;
            }

            void OnInit() override { scene->system("animationsystem")->upload(this); }

            void add_animation(string _name, string _texture, bool _loop = true) { animations[_name] = new Animation(_name, _texture, _loop); }

            void add_frame(string animation_name, int index, float duration)
            { animations[animation_name]->frames.push_back(new AnimationFrame(index, duration)); }

            void play(string animation_name, Image* image, Sprite* sprite)
            {
                current_animation = animation_name;
                current()->reset();

                animated_image = image;
                animated_sprite = sprite;

                resume();
            }

            void resume() { playing = true; }
            void pause() { playing = false; }
            bool is_playing() { return playing == true; }
            bool is_paused() { return playing == false; }

            void set_frame() { current()->set(animated_image, animated_sprite); }

            bool in_bound() { return animated_image != nullptr && animated_image->in_bound; }

            Animation* animation(string name) { return animations[name]; }

            Animation* current() { return animation(current_animation); }
            Animation* previous() { return animation(previous_animation); }
            bool has_previous() { return previous_animation != ""; }

            bool has_frame_index_maxed_out() { return current()->current_frame >= current()->frames.size(); }

            AnimationFrame* current_frame() { return current()->frames[current()->current_frame]; }
            int current_frame_index() { return current()->current_frame; }
            void set_current_frame_index(int value) { current()->current_frame = value; }
            void increase_current_frame_index() { current()->current_frame++; }
            void reset_current_frame_index() { current()->current_frame = 0; }
            void max_out_current_frame_index() { set_current_frame_index(current()->frames.size() - 1); }

            void reset_current_animation() { current()->reset(); }

            float duration() { return current_frame()->duration; }

            AnimationFrame* frame(string animation_name, int index) { return animations[animation_name]->frames[index]; }
        };
    }
}