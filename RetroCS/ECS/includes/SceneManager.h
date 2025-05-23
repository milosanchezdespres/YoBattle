#pragma once

#include "Scene.h"

namespace RetroCS
{
    namespace ECS
    {
        inline Scene* scene;

        struct SceneManager
        {
            SceneManager() { scene = nullptr; }

            template <typename M, typename = enable_if_t<is_base_of_v<Scene, M>>>
            void go_to()
            {

                scene = new M();
                scene->set_as(0, Alias::to_string(type_index(typeid(M))));

                scene->enter();
            }

            void go_to(Scene* _scene)
            {
                if(has_scene()) scene->exit();
                
                scene = _scene;
                scene->set_as(0, Alias::to_string(type_index(typeid(Scene))));
                scene->enter();
            }

            void update(GameData* data) { scene->update(data); }

            void render() { scene->render(); }

            bool has_scene() { return scene != nullptr; }
        };
    }
}