#pragma once

#include "../../../ECS/ECS.h"
#include "../../../MAP/Camera.h"
using namespace U8INT_MAP;

#include "../Components/Sprite.h"

namespace YOBATTLE
{
    struct SpriteRenderSystem : System<Sprite>
    {
		Vector2 __position, __origin;
		Rectangle __source, __destination;

        U8INT_MAP::Camera* camera;
        int finite_scale;

        SpriteRenderSystem() : System()
        {
            standalone = true;

            __position = Vector2();
            __source = Rectangle();
            __destination = Rectangle();
            __origin = Vector2();

            camera = nullptr;
        }

        void OnUpdate(float delta, Component* _component) override
        {
            Sprite* sprite = cast(_component);

            if(sprite->visible)
            {
                __position.x = sprite->position.x;
                __position.y = sprite->position.y;

                finite_scale = sprite->scale;

                if(camera != nullptr)
                {
                    finite_scale *= camera->zoom;

                    __position.x += camera->x;
                    __position.y += camera->y;
                }

                if(Game::instance().is_texture_loaded(sprite->texture))
                {
                    if(sprite->tile_index < 0)
                    {
                        if(sprite->width > 0 && sprite->height > 0)
                        {
                            __source.x = 0;
                            __source.y = 0;
                            __source.width = finite_scale * sprite->width;
                            __source.height = finite_scale * sprite->height;

                            __destination.x = __position.x;
                            __destination.y = __position.y;
                            __destination.width = sprite->width;
                            __destination.height = sprite->height;

                            DrawTexturePro(Game::instance().texture(sprite->texture), __source, __destination, __origin, sprite->rotation, WHITE);
                        }
                        else
                        { DrawTextureEx(Game::instance().texture(sprite->texture), __position, sprite->rotation, finite_scale, WHITE); }
                    }
                    else
                    {
                        if(camera == nullptr || !camera->is_out_of_bound(__position.x, __position.y, sprite->tile_size, sprite->tile_size, sprite->scale))
                        {
                            int tiles_per_row = Game::instance().texture(sprite->texture).width / sprite->tile_size;

                            __source.x = (sprite->tile_index % tiles_per_row) * sprite->tile_size;
                            __source.y = (sprite->tile_index / tiles_per_row) * sprite->tile_size;
                            __source.width = sprite->tile_size;
                            __source.height = sprite->tile_size;

                            __destination.x = __position.x;
                            __destination.y = __position.y;
                            __destination.width = finite_scale * sprite->tile_size;
                            __destination.height = finite_scale * sprite->tile_size;

                            __origin.x = __source.width / 2.0f;
                            __origin.y = __source.height / 2.0f;


                            DrawTexturePro(Game::instance().texture(sprite->texture), __source, __destination, __origin, sprite->rotation, WHITE);
                        }
                    }
                }
            }
        }
    };
}