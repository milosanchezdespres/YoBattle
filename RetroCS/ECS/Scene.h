#pragma once

#include "../Tools/Container.h"
using namespace RetroCS::Tools;

#include "Entity.h"
#include "System.h"

namespace RetroCS
{
    namespace ECS
    {
        struct Scene : public Container<Entity>
        {
            vector<BaseSystem*> systems;

            template <typename T>
            void attach() { systems.push_back(new T()); }

            Scene() : Container() {}

            virtual void enter() {}
            virtual void events() { for(auto* sys : systems) { sys->events(); } }
            virtual void update(float delta) { for(auto* sys : systems) { sys->update(delta); } }
            virtual void draw() { for(auto* sys : systems) { sys->draw(); } }
            virtual void exit() {}
        };
    }
}