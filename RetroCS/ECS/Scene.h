#pragma once

#include "../Tools/Container.h"
using namespace RetroCS::Tools;

#include "Entity.h"

namespace RetroCS
{
    namespace ECS
    {
        struct Scene : public Container<Entity>
        {
            Scene() : Container() {}

            virtual void enter() {}
            virtual void events() {}
            virtual void update(float delta) {}
            virtual void draw() {}
            virtual void exit() {}
        };
    }
}