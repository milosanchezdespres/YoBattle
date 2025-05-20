#pragma once

namespace RetroCS
{
    namespace MAP
    {
        struct RCamera
        {
            float zoom, minus_zoom, max_zoom;
            float x, y;

            float speed;
            float __speed_scaling;

            RCamera()
            {
                minus_zoom = 1;
                max_zoom = 10;
                __speed_scaling = 60;

                zoom = minus_zoom;
                speed = 8;

                //...
            }
 
            void move_up(float delta) { y -= (speed * __speed_scaling) * delta; }
            void move_down(float delta) { y += (speed * __speed_scaling) * delta; }
            void move_left(float delta) { x -= (speed * __speed_scaling) * delta; }
            void move_right(float delta) { x += (speed * __speed_scaling) * delta; }

            void zoom_plus(int screen_width, int screen_height)
            {
                if (zoom < max_zoom)
                {
                    float oldZoom = zoom;
                    float newZoom = oldZoom + 1;

                    float screenCenterX = screen_width / 2.0f;
                    float screenCenterY = screen_height / 2.0f;

                    float worldCenterX = x + screenCenterX / oldZoom;
                    float worldCenterY = y + screenCenterY / oldZoom;

                    x = worldCenterX - screenCenterX / newZoom;
                    y = worldCenterY - screenCenterY / newZoom;

                    zoom = newZoom;
                }
            }

            void zoom_minus(int screen_width, int screen_height)
            {
                if (zoom > minus_zoom)
                {
                    float oldZoom = zoom;
                    float newZoom = oldZoom - 1;

                    float screenCenterX = screen_width / 2.0f;
                    float screenCenterY = screen_height / 2.0f;

                    float worldCenterX = x + screenCenterX / oldZoom;
                    float worldCenterY = y + screenCenterY / oldZoom;

                    x = worldCenterX - screenCenterX / newZoom;
                    y = worldCenterY - screenCenterY / newZoom;

                    zoom = newZoom;
                }
            }

        };
    }
}
