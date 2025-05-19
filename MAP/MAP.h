#pragma once

#include <raylib.h>

#include <cstdint>
#include <string>
using namespace std;

#include "../WINDOW/WINDOW.h"
using namespace RAYWIN;

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

    inline vector<metatile> map_make(int width, int height)
    {
        vector<metatile> tiles;

        for(int i = 0; i < width * height; i++) { tiles.push_back(metatile()); }

        return tiles;
    }

    inline Rectangle tile_rect_make(string texture, uint8_t tileID)
    {
        int tileWidth = 8;
        int tileHeight = 8;
        int tilesPerRow = Game::instance().texture(texture).width / tileWidth;

        int tx = tileID % tilesPerRow;
        int ty = tileID / tilesPerRow;

        return Rectangle{ float(tx * tileWidth), float(ty * tileHeight), float(tileWidth), float(tileHeight) };
    }

    inline RenderTexture2D map_draw(string texture, auto map, int tile_size, int width, int height)
    {
        RenderTexture2D tilemapTexture = LoadRenderTexture(width * tile_size, height * tile_size);

        BeginTextureMode(tilemapTexture);
        ClearBackground(BLANK);

        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x) 
            {
                metatile meta = map[y * width + x];

                int px = x * 16;
                int py = y * 16;

                DrawTextureRec(Game::instance().texture(texture), tile_rect_make(texture, meta.top_left),  { (float)(px),     (float)(py)     }, WHITE);
                DrawTextureRec(Game::instance().texture(texture), tile_rect_make(texture, meta.top_right),    { (float)(px + 8), (float)(py)     }, WHITE);
                DrawTextureRec(Game::instance().texture(texture), tile_rect_make(texture, meta.bottom_left),  { (float)(px),     (float)(py + 8) }, WHITE);
                DrawTextureRec(Game::instance().texture(texture), tile_rect_make(texture, meta.bottom_right), { (float)(px + 8), (float)(py + 8) }, WHITE);
            }
        }

        EndTextureMode();

        return tilemapTexture;
    }
}

