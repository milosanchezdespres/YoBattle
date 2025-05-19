#pragma once

namespace U8INT_MAP
{
    struct Camera
    {
        float x, y;

        int zoom;

        Camera()
        {
            x = 200;
            y = 200;

            zoom = 1;

            //...
        }
    };
}