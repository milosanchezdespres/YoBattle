#pragma once

#include "BaseObject/BaseObject.h"
using namespace BaseECS;

namespace ECS
{
    struct Component : public BaseObject
    {
        Component() : BaseObject() {}

		virtual ~Component() = default;
    };
}