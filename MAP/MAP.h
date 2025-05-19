#pragma once

#include <raylib.h>

#include <cstdint>
#include <string>
using namespace std;

#include "../WINDOW/WINDOW.h"
using namespace RAYWIN;

#include "Camera.h"

namespace U8INT_MAP
{
    struct metatile
    {
        uint8_t top_left;
        uint8_t top_right;
        uint8_t bottom_left;
        uint8_t bottom_right;
        uint8_t collision_type;

        metatile()
        {
            top_left = 0;
            top_right = 0;
            bottom_left = 0;
            bottom_right = 0;
            collision_type = 0;
        }

        metatile(uint8_t index)
        {
            top_left = index;
            top_right = index;
            bottom_left = index;
            bottom_right = index;
            collision_type = 0;
        }
    };

    struct mapsurface
    {
        U8INT_MAP::Camera* camera;

        bool map_refresh;

        string texture_name;

        uint8_t tile_size;
        uint8_t width, height;

        Rectangle map_source;
        Rectangle map_dest;
        Vector2 map_origin;

        metatile* map;
        RenderTexture2D texture;

        mapsurface()
        {
            map_refresh = true;

            texture_name = "tileset";

            tile_size = 8;
            width = 0;
            height = 0;

            map_source = {0, 0, 0, 0};
            map_dest = {0, 0, 0, 0};

            map_origin = {0, 0};

            map = nullptr;
            camera = new U8INT_MAP::Camera();
        }

        void init(int _width, int _height)
        {
            width = _width;
            height = _height;

            vector<metatile> tiles;

            map = new metatile[width * height];

            for(int i = 0; i < width * height; i++) { tiles.push_back(metatile()); }

            for (int i = 0; i < 100; ++i) { map[i] = tiles[i]; }
        }

        Rectangle tile_rect_make(string texture, uint8_t tileID)
        {
            int tileWidth = 8;
            int tileHeight = 8;
            int tilesPerRow = Game::instance().texture(texture).width / tileWidth;

            int tx = tileID % tilesPerRow;
            int ty = tileID / tilesPerRow;

            return Rectangle{ float(tx * tileWidth), float(ty * tileHeight), float(tileWidth), float(tileHeight) };
        }

        void refresh()
        {
            if (map_refresh)
            {
                texture = LoadRenderTexture(width * tile_size, height * tile_size);

                BeginTextureMode(texture);
                ClearBackground(BLANK);

                for (int y = 0; y < height; ++y)
                {
                    for (int x = 0; x < width; ++x) 
                    {
                        metatile& meta = map[y * width + x];

                        int px = x * tile_size;
                        int py = y * tile_size;

                        DrawTextureRec(Game::instance().texture(texture_name), tile_rect_make(texture_name, meta.top_left),  { (float)(px),     (float)(py)     }, WHITE);
                        DrawTextureRec(Game::instance().texture(texture_name), tile_rect_make(texture_name, meta.top_right),    { (float)(px + 8), (float)(py)     }, WHITE);
                        DrawTextureRec(Game::instance().texture(texture_name), tile_rect_make(texture_name, meta.bottom_left),  { (float)(px),     (float)(py + 8) }, WHITE);
                        DrawTextureRec(Game::instance().texture(texture_name), tile_rect_make(texture_name, meta.bottom_right), { (float)(px + 8), (float)(py + 8) }, WHITE);
                    }
                }

                EndTextureMode();

                map_refresh = false;
            }
        }

        void draw()
        {
            map_source.x = 0;
            map_source.y = 0;
            map_source.width = (float) texture.texture.width;
            map_source.height = - (float) texture.texture.height;

            map_dest.x = (float) camera->x;
            map_dest.y = (float) camera->y;
            map_dest.width = (float) texture.texture.width * camera->zoom;
            map_dest.height = (float) texture.texture.height * camera->zoom;

            DrawTexturePro(texture.texture, map_source, map_dest, map_origin, 0.0f, WHITE);
        }

        void clear()
        {
            UnloadRenderTexture(texture);

            delete map;
            delete camera;
        }
    };
}

