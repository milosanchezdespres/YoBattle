#pragma once

#include "../Tools/Container.h"
using namespace RetroCS::Tools;

#include "Component.h"

namespace RetroCS
{
    namespace ECS
    {
        struct Scene;

        struct Entity : public Container<Component>
        {
            Entity() : Container() {}

            template <typename T, typename M>
            void upload_to(Scene* scene, string component_alias) { scene->template upload_to<T, M>(this, component_alias); }

            virtual void extra_draw() {}
            virtual void extra_events(float delta) {}
        };
    }
}