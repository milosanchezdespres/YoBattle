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
            SceneManager() : Container<Scene>() {}
        };
    }
}