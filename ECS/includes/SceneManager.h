#pragma once

#include "Scene.h"

namespace ECS
{
    struct SceneManager : Container<Scene>
    {
        string __current;

        SceneManager() : Container() { __current = ""; }

        Scene* scene() { return get(__current); }

        template <typename T>
        void go_to()
        {
            if(__current != "") { scene()->Exit(); }

            __current = to_lower(typeid(T).name());

            if(!has<T>()) { add<T>(__current); }

            scene()->Enter();
        }

        void update(float delta)
        {
            for(auto* system : scene()->all_systems()) { system->update(delta); }
        }
    };
}