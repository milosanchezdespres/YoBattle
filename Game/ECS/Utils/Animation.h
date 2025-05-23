
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
            string texture;
            bool loop;

            vector<AnimationFrame*> frames;

            float timer;
            int current_frame;

            Animation()
            {
                name = "no_name";
                loop = false;
                timer = 0;
                current_frame = 0;
            }

            Animation(string _name, string _texture, bool _loop)
            {
                name = _name;
                texture = _texture;
                loop = _loop;
                timer = 0;
                current_frame = 0;
            }

            void set(Image* image, Sprite* sprite)
            {
                image->texture = texture;
                sprite->tile->index = frames[current_frame]->index;
            }

            void reset()
            {
                timer = 0;
                current_frame = 0;
            }
        };
    }
}