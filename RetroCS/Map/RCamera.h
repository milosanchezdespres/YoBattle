#pragma once

namespace RetroCS
{
    namespace MAP
    {
        struct RCamera
        {
            float zoom;
            float x, y;

            float speed;
            float __speed_scaling;

            RCamera()
            {
                zoom = 1;

                speed = 8;
                __speed_scaling = 60;

                //...
            }

            void move_up(float delta) { y -= (speed * __speed_scaling) * delta; }
            void move_down(float delta) { y += (speed * __speed_scaling) * delta; }
            void move_left(float delta) { x -= (speed * __speed_scaling) * delta; }
            void move_right(float delta) { x += (speed * __speed_scaling) * delta; }
        };
    }
}
