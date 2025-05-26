#pragma once

#include "View.h"
#include "Transform.h"

namespace retrocs
{
    namespace ecs
    {
        struct Entity: public View<Entity>
        {
            Transform transform_view;

            Entity(int _id) : View<Entity>(_id) { transform_view = Transform(); transform_view.id = id; }

            bool _on_init(VirtualScreen& screen_space) { return true; }

            void populate_data(VirtualScreen& screen_space)
            {
                transform_view.populate_data(screen_space);

                //...
            }

            Transform& transform() { return transform_view; }
            const Transform& transform() const { return transform_view; }
        };
    }
}