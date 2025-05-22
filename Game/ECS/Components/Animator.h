#pragma once

#include "../../../RetroCS/RetroCS.h"

namespace YoKard
{
    namespace ECS
    {
        struct AnimationFrame
        {
            int index;
            float duration;

            AnimationFrame() {}

            AnimationFrame(int _index, float _duration)
            {
                index = _index;
                duration = _duration;
            }
        };

        struct Animation
        {
            string name;
            bool loop;

            vector<AnimationFrame*> frames;

            float timer;

            Animation()
            {
                name = "no_name";
                loop = false;
                timer = 0;
            }

            Animation(string _name, bool _loop)
            {
                name = _name;
                loop = _loop;
                timer = 0;
            }
        };

        struct Animator : public Component
        {
            unordered_map<string, Animation*> animations;

            string previous;
            string current;

            Animator() : Component() { }

            void OnInit() override { scene->system("animationsystem")->upload(this); }

            void add_animation(string _name, bool _loop = true) { animations[_name] = new Animation(_name, _loop); }

            void add_frame(string animation_name, int index, float duration)
            { animations[animation_name]->frames.push_back(new AnimationFrame(index, duration)); }

            Animation* animation(string name) { return animations[name]; }
            AnimationFrame* frame(string animation_name, int index) { return animations[animation_name]->frames[index]; }
        };
    }
}