#pragma once

#include "Component.h"

namespace RetroCS
{
    namespace ECS
    {
        struct Entity : public Container<Component>
        {
            bool initialized;

            Entity() : Container<Component>() { initialized = false; }

            void init()
            {
                if(!initialized)
                {
                    OnInit();
                    initialized = true;
                }
            }

            virtual void render() {}

            void OnAdd(string name) override { get(name)->init(); }
            virtual void OnInit() {}
        };
    }
}