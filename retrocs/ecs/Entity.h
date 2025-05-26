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

            void update()
            {
                //.....
                ///STATE MACHINE///
                //...
            }

            void place(VirtualScreen& screen_space, float x, float y)
            {
                transform_view.x() = x;
                transform_view.y() = y;

                int new_i = TO_CELL(x, y).i;
                int new_j = TO_CELL(x, y).j;

                if (transform_view.coordinates) { screen_space.update(id, {new_i, new_j}); }
            }

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