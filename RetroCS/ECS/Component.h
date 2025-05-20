#pragma once

#include "../Tools/includes.h"
#include "../Tools/BaseObject.h"
using namespace RetroCS::Tools;

namespace RetroCS
{
    namespace ECS
    {
        struct Component : public BaseObject
        {
            bool enabled;

            Component() : BaseObject() { enabled = true; }
        };
    }
}