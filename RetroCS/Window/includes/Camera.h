#pragma once

#include "raylib.h"

#include "../../Tools/Tools.h"

namespace RetroCS
{
    namespace Window
    {
        struct Viewport
        {
            float x, y;
            int width, height;
            int screen_width, screen_height;

            Viewport()
            {
                x = 0;
                y = 0;
                width = 0;
                height = 0;
            }
        };

        struct Camera
        {
            float zoom;
            float x, y;
            float move_speed;
            float lerp_speed;

            float* target_x;
            float* target_y;

            Camera(const Camera&) = delete;
            Camera& operator=(const Camera&) = delete;

            static Camera& instance()
            {
                static Camera __instance;
                return __instance;
            }

            void init(int screen_width, int screen_height)
            {
                viewport->screen_width = screen_width;
                viewport->screen_height = screen_height;

                x = 0;
                y = 0;
            }

            void update(float delta)
            {
                if(_mode == 0) __free_mode(delta);
                else if(_mode == 1) __follow_mode(delta);
            }

            void follow(float& _target_x, float& _target_y)
            {
                target_x = &_target_x;
                target_y = &_target_y;
                _mode = 1;
            }

            void unfollow()
            {
                target_x = nullptr;
                target_y = nullptr;
                _mode = 0;
            }

            void set_zoom(float new_value) { zoom = new_value; }

            Vector2 world_to_screen(float world_x, float world_y)
            {
                float screen_x = (world_x - viewport->x) * zoom;
                float screen_y = (world_y - viewport->y) * zoom;

                return { screen_x, screen_y };
            }

            Vector2 screen_to_world(float screen_x, float screen_y)
            {
                float world_x = screen_x / zoom + viewport->x;
                float world_y = screen_y / zoom + viewport->y;

                return { world_x, world_y };
            }

            bool is_within_bounds(float screen_x, float screen_y, float obj_width, float obj_height)
            {
                const int sw = viewport->screen_width;
                const int sh = viewport->screen_height;

                return (screen_x + obj_width > 0) && (screen_x < sw) &&
                    (screen_y + obj_height > 0) && (screen_y < sh);
            }
            
            bool is_out_of_bounds(float obj_x, float obj_y, float obj_width, float obj_height) { return !is_within_bounds(obj_x, obj_y, obj_width, obj_height); }

            private:
                Viewport* viewport;
                bool _mode;

                Camera()
                {
                    viewport = new Viewport();
                    zoom = 1;
                    lerp_speed = 5.0f;
                    move_speed = 150;
                    _mode = 0;

                    target_x = nullptr;
                    target_y = nullptr;
                }

                ~Camera()
                {
                    delete viewport;
                    viewport = nullptr;
                }

                float __lerp(float start, float end, float t) { return start + t * (end - start); }

                void __follow_mode(float delta)//TARGET_SIZE ?
                {
                    viewport->width  = viewport->screen_width  / zoom;
                    viewport->height = viewport->screen_height / zoom;

                    float targetViewportX = *target_x - viewport->width / 2;
                    float targetViewportY = *target_y - viewport->height / 2;

                    viewport->x = __lerp(viewport->x, targetViewportX, lerp_speed * delta);
                    viewport->y = __lerp(viewport->y, targetViewportY, lerp_speed * delta);
                }

                void __free_mode(float delta)
                {
                    viewport->width  = viewport->screen_width  / zoom;
                    viewport->height = viewport->screen_height / zoom;

                    viewport->x = x - viewport->width / 2;
                    viewport->y = y - viewport->height / 2;

                    //debug.......................................................
                    if (IsKeyDown(KEY_W)) y -= move_speed * delta;
                    if (IsKeyDown(KEY_S)) y += move_speed * delta;
                    if (IsKeyDown(KEY_A)) x -= move_speed * delta;
                    if (IsKeyDown(KEY_D)) x += move_speed * delta;
                    //debug.......................................................
                }
        };

        inline Camera& camera() { return Camera::instance(); }
    }
}
