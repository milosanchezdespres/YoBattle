#pragma once

#include "../utils.h"

namespace retrocs
{
    namespace ecs
    {
        struct Scene
        {
            VirtualScreen screen_space;

            Scene() { screen_space = VirtualScreen(); }

            template<typename T, typename... Args>
            const T spawn(const cell& _cell, Args&&... args)
            {
                Transform transform;
                if(transform.init(screen_space, _cell.i, _cell.j))
                {
                    T new_entity(transform.id);
                    new_entity.init(screen_space, std::forward<Args>(args)...);
                    new_entity.transform_view = transform;

                    return new_entity;
                }
                else return Entity(-1);
            }

            void remove_at(const int& i, const int& j)
            {
                screen_space.remove_at({i, j});

                //remove custom component data....

                //...
            }

            void remove_at(const cell& _cell) { remove_at(_cell.i, _cell.j); }

            void remove(int id)
            {
                if (!screen_space.is_valid(id))
                    return;

                cell _cell = screen_space.tile(id);
                screen_space.remove_at(_cell);

                //remove custom component data....
            }

            template<typename T>
            const T get(int id)
            {
                T obj(id);
                obj.populate_data(screen_space);
                return obj;
            }

            template<typename T>
            const T get_at(const cell& _cell)
            {
                int id = screen_space.entity_id_at(_cell.i, _cell.j);
                if (id == -1) return T(-1);
                return get<T>(id);
            }

            template<typename T>
            T get_at(const int& i, const int& j) { return get_at<T>({i, j}); }

            CellIterator begin() const { return CellIterator(screen_space.coordinates, screen_space.validity, 0); }
            CellIterator end() const { return CellIterator(screen_space.coordinates, screen_space.validity, screen_space.coordinates.size()); }
        };
    }
}