#pragma once

namespace U8INT_MAP
{
    struct Camera
    {
        int mode;
        float speed;
        int zoom;

        float x, y;

        Entity* target;

        Camera()
        {
            //MODES : 0 = static, 1 = free, 2 = follow
            mode = 0;
            speed = 450;
            zoom = 1;

            x = 0;
            y = 0;

            target = nullptr;
        }
    };
}