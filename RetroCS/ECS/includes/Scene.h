#pragma once

#include "Entity.h"

namespace retrocs
{
    namespace ecs
    {
        struct Scene : box<Entity>
        {
            Scene() : box<Entity>() {}

            void enter() { init(0); _on_enter(); }
            void exit() { _on_exit(); }

            virtual void _on_enter() {}
            virtual void _on_exit() {}

            virtual Scene* clone() const { return new Scene(*this);  }
        };
    }
}