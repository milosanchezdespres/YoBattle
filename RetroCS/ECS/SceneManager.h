#pragma once

#include "../Tools/Container.h"
using namespace RetroCS::Tools;

#include "Scene.h"

namespace RetroCS
{
    namespace ECS
    {
        struct SceneManager : public Container<Scene>
        {
            string __current;

            SceneManager() : Container<Scene>() {}

            template <typename T>
            void go_to()
            {
                if(__current != "") { scene()->exit(); }

                __current = to_lower(typeid(T).name());

                if(!has<T>()) { add<T>(__current); }

                scene()->enter();
            }

            Scene* scene() { return get(__current); }
        };
    }
}