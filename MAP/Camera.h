#pragma once

namespace U8INT_MAP
{
    struct Camera
    {
        int mode;
        float speed;
        int zoom;

        float x, y;

        Vector2 target_position;
        int target_width;
        int target_height;

        Camera()
        {
            //MODES : 0 = static, 1 = free, 2 = follow
            mode = 0;
            speed = 450;
            zoom = 1;

            x = 0;
            y = 0;

            target_position = {0, 0};
            target_width = 0;
            target_height = 0;
        }

        void go_to(Vector2 target, int width, int height, bool then_free_mode = false)
        {
            target_position = target;
            target_width = width;
            target_height = height;

            x = -((target_position.x + target_width * 0.5f) * zoom - Game::instance().width * 0.5f);
            y = -((target_position.y + target_height * 0.5f) * zoom - Game::instance().height * 0.5f);

            mode = then_free_mode;
        }

        void update(float delta)
        {
            if(mode == 1)
            {
                if (Game::instance().is_down("up")) y += speed * delta;
                if (Game::instance().is_down("down")) y -= speed * delta;
                if (Game::instance().is_down("left")) x += speed * delta;
                if (Game::instance().is_down("right")) x -= speed * delta;
            }

            if(mode == 2)
            {
                x = -((target_position.x + target_width * 0.5f) * zoom - Game::instance().width * 0.5f);
                y = -((target_position.y + target_height * 0.5f) * zoom - Game::instance().height * 0.5f);
            }
        }

        void update_follow(Vector2 target, int width, int height)
        {
            target_position = target;
            target_width = width;
            target_height = height;
        }
        
        bool is_out_of_bound(float obj_x, float obj_y, int obj_w, int obj_h, float obj_scale)
        {
            float scaled_w = obj_w * obj_scale * zoom;
            float scaled_h = obj_h * obj_scale * zoom;

            return (obj_x + scaled_w < 0) || (obj_x > Game::instance().width) || (obj_y + scaled_h < 0) || (obj_y > Game::instance().height);
        }
    };
}