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

            void update(VirtualScreen& screen)
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

                _on_place(screen_space, x, y);
            }

            bool _on_init(VirtualScreen& screen_space) { return true; }

            void populate_data(VirtualScreen& screen_space)
            {
                transform_view = Transform();
                transform_view.id = id;
                transform_view.populate_data(screen_space);

                //...

                _on_populate_data(screen_space);
            }

            Transform& transform() { return transform_view; }
            const Transform& transform() const { return transform_view; }

            virtual void _on_populate_data(VirtualScreen& screen_space) {}
            virtual void _on_place(VirtualScreen& screen_space, float x, float y) {}
        };
    }
}