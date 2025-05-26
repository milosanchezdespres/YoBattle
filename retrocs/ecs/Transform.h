#pragma once

#include "View.h"

namespace retrocs
{
    namespace ecs
    {
        struct Transform : public View<Transform>
        {
            vector<cell>* coordinates;
            vector<pos>* raw_coordinates;

            Transform() : View<Transform>() { coordinates = nullptr; raw_coordinates = nullptr; }

            Transform(int _id) : View<Transform>() { coordinates = nullptr; raw_coordinates = nullptr; }

            bool _on_init(VirtualScreen& screen_space, const int& i, const int& j)
            {
                coordinates = &screen_space.coordinates;

                int _id = screen_space.spawn_at(i, j);

                if(_id != -1 && coordinates != nullptr)
                {
                    id = _id;
                    populate_data(screen_space);
                    return true;
                }

                return false;
            }

            void populate_data(VirtualScreen& screen_space) override
            {
                coordinates = &screen_space.coordinates;
                raw_coordinates = &screen_space.precise_positions;
                //...
            }

            const int& i() const { return (*coordinates)[id].i; }
            const int& j() const { return (*coordinates)[id].j; }
            int& i() { return (*coordinates)[id].i; }
            int& j() { return (*coordinates)[id].j; }

            const float cell_x() const { return TO_POS(i(), j()).x; }
            const float cell_y() const { return TO_POS(i(), j()).y; }
            float cell_x() { return TO_POS(i(), j()).x; }
            float cell_y() { return TO_POS(i(), j()).y; }

            const float& x() const { return (*raw_coordinates)[id].x; }
            const float& y() const { return (*raw_coordinates)[id].y; }
            float& x() { return (*raw_coordinates)[id].x; }
            float& y() { return (*raw_coordinates)[id].y; }

            const cell cell_position() { return {i(), j()}; }
            const pos screen_cell_position() { return TO_POS(i(), j()); }
            const pos position() { return {(*raw_coordinates)[id].x, (*raw_coordinates)[id].y}; }
        };
    }
}