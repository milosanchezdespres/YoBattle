#pragma once

#include "../../Utils/Utils.h"
#include "GameData.h"
#include "Resources/input.h"

namespace retrocs
{
    namespace window
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

        struct SimpleCamera
        {
            bool mode;

            float zoom;
            float x, y;

            float speed;
            float lerp;

            float* target_x;
            float* target_y;

            Viewport* viewport;

            SimpleCamera()
            {
                mode = 0;
                
                lerp = 5.0f;
                speed = 1.5f;

                zoom = 1;
                x = 0;
                y = 0;

                target_x = nullptr;
                target_y = nullptr;
            }

            void init(int screen_width, int screen_height)
            {
                viewport = new Viewport();
                viewport->screen_width = screen_width;
                viewport->screen_height = screen_height;
            }

            void update(BaseGameData* data)
            {
                if(mode == 0) __free_mode(data);
                else if(mode == 1) __follow_mode(data->delta);
            }

            void follow(float& _target_x, float& _target_y)
            {
                target_x = &_target_x;
                target_y = &_target_y;
                mode = 1;
            }

            void unfollow()
            {
                target_x = nullptr;
                target_y = nullptr;
                mode = 0;
            }

            ~SimpleCamera()
            {
                delete viewport;
                viewport = nullptr;

                target_x = nullptr;
                target_y = nullptr;
            }

            bool apply(int texture_width, int texture_height, float& screen_x, float& screen_y, float& obj_width, float& obj_height, 
                int tile_index, Vector4& rect)
            {
                if(tile_index == -1)
                {
                    obj_width *= zoom;
                    obj_height *= zoom;

                    float X = screen_x;
                    float Y = screen_y;

                    screen_x = (X - viewport->x) * zoom - obj_width / 2.0f;
                    screen_y = (Y - viewport->y) * zoom - obj_height / 2.0f;
                }
                else
                {
                    int tile_size = obj_width;
                    int tiles_per_row = texture_width / tile_size;

                    float source_width = tile_size;
                    float source_height = tile_size;

                    float destination_width = zoom * source_width;
                    float destination_height = zoom * source_height;

                    float orig_screen_x = screen_x;
                    float orig_screen_y = screen_y;

                    // Get screen position WITHOUT zoom, then apply zoom *only* on size and offset
                    screen_x = (int)(world_to_screen(orig_screen_x, orig_screen_y).x) - destination_width / 2;
                    screen_y = (int)(world_to_screen(orig_screen_x, orig_screen_y).y) - destination_height / 2;

                    float source_x = (tile_index % tiles_per_row) * source_width;
                    float source_y = (tile_index / tiles_per_row) * source_height;

                    obj_width = destination_width;
                    obj_height = destination_height;

                    rect = {
                        source_x / texture_width,
                        source_y / texture_height,
                        (source_x + source_width) / texture_width,
                        (source_y + source_height) / texture_height
                    };
                }

                return is_within_bounds(screen_x, screen_y, obj_width, obj_height);
            }

            bool is_within_bounds(float screen_x, float screen_y, float obj_width, float obj_height)
            {
                const int sw = viewport->screen_width;
                const int sh = viewport->screen_height;

                return (screen_x + obj_width > 0) && (screen_x < sw) &&
                    (screen_y + obj_height > 0) && (screen_y < sh);
            }
            
            bool is_out_of_bounds(float obj_x, float obj_y, float obj_width, float obj_height) { return !is_within_bounds(obj_x, obj_y, obj_width, obj_height); }

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

            float __lerp(float start, float end, float t) { return start + t * (end - start); }

            void __follow_mode(float delta)//TARGET_SIZE ?
            {
                viewport->width  = viewport->screen_width  / zoom;
                viewport->height = viewport->screen_height / zoom;

                float targetViewportX = *target_x - viewport->width / 2;
                float targetViewportY = *target_y - viewport->height / 2;

                viewport->x = __lerp(viewport->x, targetViewportX, lerp * delta);
                viewport->y = __lerp(viewport->y, targetViewportY, lerp * delta);
            }

            void __free_mode(BaseGameData* data)
            {
                viewport->width  = viewport->screen_width  / zoom;
                viewport->height = viewport->screen_height / zoom;

                viewport->x = x - viewport->width / 2;
                viewport->y = y - viewport->height / 2;

                if (data->get<retrocs::window::button>("up")->is_down()) y -= (speed * 100) * data->delta;
                if (data->get<retrocs::window::button>("down")->is_down()) y += (speed * 100) * data->delta;
                if (data->get<retrocs::window::button>("left")->is_down()) x -= (speed * 100) * data->delta;
                if (data->get<retrocs::window::button>("right")->is_down()) x += (speed * 100) * data->delta;
            }
        };
    }
}