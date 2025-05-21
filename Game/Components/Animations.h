#pragma once

#include "../../RetroCS/RetroCS.h"

namespace YoBattleGame
{
    namespace ECS
    {
        struct Animation
        {
            string name;
            float timer;
            int index;

            vector<uint8_t> frames;
        };

        struct Animations : public Component
        {
            Animation* previous;
            Animation* current;

            unordered_map<string, Animation*> animations;

            float speed;

            Animations () : Component() { speed = 0; }

            Animation* animation(string action, int direction = -1)
            {
                previous = nullptr;
                current = nullptr;
                
                string finite_name = action;
                if(direction > -1) { finite_name += "_" + to_string(direction); }


                return animations[finite_name];
            }

            void add_animation(string action, int direction = -1)
            {
                string finite_name = action;
                if(direction > -1) { finite_name += "_" + to_string(direction); }

                animations[finite_name] = new Animation();
                animations[finite_name]->name = finite_name;
                animations[finite_name]->timer = 0;
            }
            
            void add_frame(int tile_index, string action, int direction = -1)
            {
                string finite_name = action;
                if(direction > -1) { finite_name += "_" + to_string(direction); }

                animations[finite_name]->frames.push_back(tile_index);
            }
        };
    }
}
