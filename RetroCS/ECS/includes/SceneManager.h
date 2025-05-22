#pragma once

#include "Scene.h"

namespace RetroCS
{
    namespace ECS
    {
        struct SceneManager
        {
            Scene* current;

            SceneManager() { current = nullptr; }

            template <typename M, typename = enable_if_t<is_base_of_v<Scene, M>>>
            void go_to()
            {
                if(has_scene()) current->exit();

                current = new M();
                current->set_as(0, Alias::to_string(type_index(typeid(M))));

                current->enter();
            }

            Scene* scene() { return current; }

            bool has_scene() { return current != nullptr; }
        };
    }
}