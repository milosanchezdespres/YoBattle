#pragma once

namespace U8INT_MAP
{
    struct Camera
    {
        float x, y;

        int zoom;

        Camera()
        {
            x = 0;
            y = 0;

            zoom = 1;

            //...
        }
    };
}