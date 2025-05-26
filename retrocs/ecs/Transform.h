#pragma once

#include "View.h"

namespace retrocs
{
    namespace ecs
    {
        struct Transform : public View<Transform>
        {
            vector<cell>* coordinates;

            Transform() : View<Transform>() { coordinates = nullptr; }

            Transform(int _id) : View<Transform>() { coordinates = nullptr; }

            bool _on_init(VirtualScreen& screen_space, const int& i, const int& j)
            {
                coordinates = &screen_space.coordinates;

                int _id = screen_space.spawn_at(i, j);

                if(_id != -1 && coordinates != nullptr)
                {
                    id = _id;
                    coordinates = &screen_space.coordinates;
                    return true;
                }

                return false;
            }

            void populate_data(VirtualScreen& screen_space) override
            {
                coordinates = &screen_space.coordinates;
                //...
            }

            const int& i() const { return (*coordinates)[id].i; }
            const int& j() const { return (*coordinates)[id].j; }
            int& i() { return (*coordinates)[id].i; }
            int& j() { return (*coordinates)[id].j; }
        };
    }
}