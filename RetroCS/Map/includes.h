#pragma once

#include <raylib.h>

#include "../Tools/Externals.h"

#include "../Window/Game.h"
using namespace RetroCS::GameWindow;

//do not use in calculations - only use when drawing -----------------------------------
#include "RCamera.h"
//do not use in calculations - only use when drawing -----------------------------------

namespace RetroCS
{
    namespace MAP
    {
        const uint8_t& __METATILE_SIZE = 4;
        const uint8_t& ___TILE_SIZE = 8;

        inline int width;
        inline int height;

        inline int tilesize() { return (__METATILE_SIZE / 2) * ___TILE_SIZE; }

        struct Vector2i
        {
            int i;
            int j;

            Vector2i() : i(0), j(0) {}

            Vector2i(int I, int J) : i(I), j(J) {}

            bool operator==(const Vector2i& other) const
            {
                return i == other.i && j == other.j;
            }

            bool operator!=(const Vector2i& other) const
            {
                return !(*this == other);
            }
        };

        struct metatile
        {
            uint8_t top_left;
            uint8_t top_right;
            uint8_t bottom_left;
            uint8_t bottom_right;
            uint8_t collision_type;
        };

        struct metatexture;

        struct metamap
        {
            uint8_t width;
            uint8_t height;
            metatile* metatiles;

            metatexture* texture = nullptr;
        };

        struct metatexture
        {
            string alias;

            bool refresh_signal;
            RenderTexture2D data;

            Rectangle __source;
            Rectangle __dest;
            Vector2 __origin;

            metamap* map = nullptr;
        };

        inline Vector2i screen_to_tile(float x, float y)
        {
            return {
                static_cast<int>(std::floor(x / tilesize())),
                static_cast<int>(std::floor(y / tilesize()))
            };
        }
                
        inline Vector2 tile_to_screen(int i, int j)
        {
            return {
                i * tilesize(),
                j * tilesize()
            };
        }

        inline void init(metamap& map, int _width, int _height)
        {
            width = _width;
            height = _height;

            map.width = _width;
            map.height = height;

            vector<metatile> metatiles;

            map.metatiles = new metatile[width * height];

            for(int i = 0; i < width * height; i++) { metatiles.push_back(metatile()); }

            for (int i = 0; i < width * height; ++i) { map.metatiles[i] = metatiles[i]; }
        }

        inline metamap* map;

        inline void bind(metamap& _map, metatexture& texture)
        {
            _map.texture = &texture;
            texture.map = &_map;

            map = &_map;
        }

        inline void init(metatexture& texture, string texture_alias)
        {
            texture.alias = texture_alias;
            texture.data = LoadRenderTexture(texture.map->width * tilesize(), texture.map->height * tilesize());
            texture.refresh_signal = true;
        }

        Rectangle __tile_rect_make(string texture, uint8_t tileID)
        {
            int tileWidth = 8;
            int tileHeight = 8;
            int tilesPerRow = Game::instance().texture(texture).width / tileWidth;

            int tx = tileID % tilesPerRow;
            int ty = tileID / tilesPerRow;

            return Rectangle{ float(tx * tileWidth), float(ty * tileHeight), float(tileWidth), float(tileHeight) };

            return {};
        }

       inline void render(metatexture& texture)
        {
            if (texture.refresh_signal)
            {
                BeginTextureMode(texture.data);
                ClearBackground(BLANK);

                for (int y = 0; y < texture.map->height; ++y)
                {
                    for (int x = 0; x < texture.map->width; ++x) 
                    {
                        metatile& meta = texture.map->metatiles[y * texture.map->width + x];

                        int px = x * tilesize();
                        int py = y * tilesize();

                        DrawTextureRec(Game::instance().texture(texture.alias), __tile_rect_make(texture.alias, meta.top_left), { (float)(px),     (float)(py)     }, WHITE);
                        DrawTextureRec(Game::instance().texture(texture.alias), __tile_rect_make(texture.alias, meta.top_right), { (float)(px + 8), (float)(py)     }, WHITE);
                        DrawTextureRec(Game::instance().texture(texture.alias), __tile_rect_make(texture.alias, meta.bottom_left), { (float)(px),     (float)(py + 8) }, WHITE);
                        DrawTextureRec(Game::instance().texture(texture.alias), __tile_rect_make(texture.alias, meta.bottom_right), { (float)(px + 8), (float)(py + 8) }, WHITE);
                    }
                }

                EndTextureMode();

                texture.refresh_signal = false;
            }
        }

        inline void draw(metatexture& texture, float rotation = 0)
        {
            texture.__source.x = 0;
            texture.__source.y = 0;
            texture.__source.width = (float) texture.data.texture.width;
            texture.__source.height = - (float) texture.data.texture.height;

            texture.__dest.x = - (int) (Game::instance().camera()->x);
            texture.__dest.y = - (int) (Game::instance().camera()->y);
            texture.__dest.width = Game::instance().camera()->zoom * (float) texture.data.texture.width;
            texture.__dest.height = Game::instance().camera()->zoom * (float) texture.data.texture.height;

            DrawTexturePro(texture.data.texture, texture.__source, texture.__dest, texture.__origin, rotation, WHITE);
        }

        inline void unbind(metamap& _map)
        {
            UnloadRenderTexture(_map.texture->data);

            _map.texture->map = nullptr;
            _map.texture = nullptr;

            map = nullptr;
        }

        inline void unbind(metatexture& texture)
        {
            UnloadRenderTexture(texture.data);

            texture.map->texture = nullptr;
            texture.map = nullptr;

            map = nullptr;
        }
    }
}

using namespace RetroCS::MAP;

