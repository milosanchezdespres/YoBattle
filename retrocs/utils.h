#pragma once

#include "raylib.h"

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <unordered_map>
#include <cstdint>
#include <type_traits>
#include <utility>
#include <algorithm> 

namespace std
{
    struct pos { float x, y; };
    struct cell { int i, j; };// cell() : i(0), j(0) {} cell(int _i, int _j) : i(_i), j(_j) {} 
    const cell INVALID_CELL = { -999999, -999999 };
    const int ALLOWED_ENTITY_MAX = 1'000'000;

    const int SCREEN_WIDTH = 480;
    const int SCREEN_HEIGHT = 320;
    const int TILE_SIZE = 16;

    inline const pos TO_POS(cell _cell) { return pos({(float) _cell.i * TILE_SIZE, (float) _cell.j * TILE_SIZE}); }
    inline const pos TO_POS(int i, int j) { return TO_POS(cell({i, j})); }

    inline const cell TO_CELL(pos _pos) { return cell({(int)(_pos.x / TILE_SIZE), (int)(_pos.y / TILE_SIZE)}); }
    inline const cell TO_CELL(float x, float y) { return TO_CELL(pos({x, y})); }

    inline string debug(string value) { cout << "  << " + value  + " >>  " << endl << endl; return value; }
    inline string debug(float value) { return debug(to_string(value)); }
    inline string debug(int value) { return debug(to_string(value)); }
    inline string debug(int value1, int value2) { return debug(to_string(value1) + ", " + to_string(value2)); }
    inline string debug(float value1, float value2) { return debug(to_string(value1) + ", " + to_string(value2)); }
    inline string debug(cell _cell) { return debug(_cell.i, _cell.j); }

    inline size_t hash_id(const int& cell_x, const int& cell_y) { return ((size_t)cell_x * 73856093) ^ ((size_t)cell_y * 19349663); }
    inline size_t hash_id(const cell& _cell) { return hash_id(_cell.i, _cell.j); }
    //...
    
}

using namespace std;