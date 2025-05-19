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
        
        bool is_out_of_bound(float obj_x, float obj_y, int obj_w, int obj_h, float obj_scale)
        {
            float scaled_w = obj_w * obj_scale * zoom;
            float scaled_h = obj_h * obj_scale * zoom;

            return (obj_x + scaled_w < 0) || (obj_x > Game::instance().width) || (obj_y + scaled_h < 0) || (obj_y > Game::instance().height);
        }
    };
}