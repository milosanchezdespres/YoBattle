#pragma once

#include "../utils.h"

namespace retrocs
{
    namespace ecs
    {
        struct VirtualScreen
        {
            unordered_map<size_t, int> screen_space;
            vector<cell> coordinates;
            vector<pos> precise_positions;
            vector<int> in_bounds_ids;
            vector<bool> validity;
            deque<int> free_ids;

            VirtualScreen()
            {
                screen_space.reserve(ALLOWED_ENTITY_MAX);
                coordinates.reserve(ALLOWED_ENTITY_MAX);
                precise_positions.reserve(ALLOWED_ENTITY_MAX);
                validity.reserve(ALLOWED_ENTITY_MAX);
            }

            bool update(int id, const cell& _new_cell)
            {
                auto it = screen_space.find(hash_id(_new_cell));
                bool item_found = it != screen_space.end();

                int occupied_id = -1;
                if(item_found) occupied_id = it->second;
                if(!is_valid(occupied_id)) occupied_id = -1;

                if(occupied_id == -1 && has(id) && is_valid(id))
                {
                    screen_space[hash_id(tile(id))] = -1;

                    if (id >= coordinates.size())
                    {
                        coordinates.resize(id + 1);
                        validity.resize(id + 1);
                        precise_positions.resize(id + 1);
                    }

                    coordinates[id] = _new_cell;
                    screen_space[hash_id(_new_cell)] = id;
                    validity[id] = true;

                    precise_positions[id] = pos{_new_cell.i + 0.5f, _new_cell.j + 0.5f};

                    auto it_inbounds = find(in_bounds_ids.begin(), in_bounds_ids.end(), id);

                    bool new_cell_in_bounds = in_bounds(TO_POS(_new_cell));
                    bool already_in_bounds_array = it_inbounds != in_bounds_ids.end();

                    if(new_cell_in_bounds) { if(!already_in_bounds_array)  in_bounds_ids.push_back(id); }
                    else { if(already_in_bounds_array) in_bounds_ids.erase(it_inbounds); }

                    return true;
                }
                else { return false; }
            }

            bool update(int id, const int& newi, const int& newj) { return update(id, {newi, newj}); }

            int entity_id_at(const cell& _cell)
            {
                if(is_occupied(_cell)) return screen_space[hash_id(_cell)];
                return -1;
            }

            int entity_id_at(const int& i, const int& j) { return entity_id_at({i, j}); }

            cell tile(int id)
            {
                if(has(id) && is_valid(id)) return coordinates[id];
                return INVALID_CELL;
            }

            int spawn_at(const cell& _cell)
            {
                auto it = screen_space.find(hash_id(_cell));
                bool item_found = it != screen_space.end();

                int id = -1;
                if(item_found) id = it->second;

                bool found_unvalid_slot = item_found && !is_valid(id);
                bool can_spawn = !item_found || found_unvalid_slot;

                if (can_spawn)
                {
                    if (!item_found)
                    {
                        if (!free_ids.empty()) 
                        {
                            id = free_ids.front();
                            free_ids.pop_front();
                            coordinates[id] = _cell;
                            validity[id] = true;
                            precise_positions[id] = pos{_cell.i + 0.5f, _cell.j + 0.5f};
                        } 
                        else 
                        {
                            coordinates.push_back(_cell);
                            validity.push_back(true);
                            precise_positions.push_back(pos{_cell.i + 0.5f, _cell.j + 0.5f});
                            id = coordinates.size() - 1;
                        }
                    }
                    else
                    {
                        coordinates[id] = _cell;
                        validity[id] = true;
                        precise_positions[id] = pos{_cell.i + 0.5f, _cell.j + 0.5f};
                    }

                    screen_space[hash_id(_cell)] = id;

                    if(in_bounds(TO_POS(_cell))) { in_bounds_ids.push_back(id); }

                    return id;
                }

                return -1;
            }

            int spawn_at(const int& i, const int& j) { return spawn_at({i, j}); }

            void remove(int id)
            {
                if (!is_valid(id)) return;
                validity[id] = false;

                cell _cell = tile(id);
                if (_cell.i != -999999)
                {
                    screen_space.erase(hash_id(_cell));
                }

                auto it_inbounds = find(in_bounds_ids.begin(), in_bounds_ids.end(), id);
                if (it_inbounds != in_bounds_ids.end())
                {
                    in_bounds_ids.erase(it_inbounds);
                }

                free_ids.push_back(id);
                precise_positions[id] = pos{-9999.0f, -9999.0f}; // optional sentinel
            }

            void remove_at(const cell& _cell)
            {
                auto it = screen_space.find(hash_id(_cell));
                if (it != screen_space.end())
                {
                    int id = it->second;
                    remove(id);
                }
            }

            void remove_at(const int& i, const int& j) { remove_at({i, j}); }

            bool is_occupied(const cell& _cell)
            {
                auto it = screen_space.find(hash_id(_cell));
                bool item_found = it != screen_space.end();
                if(item_found)
                {
                    int id = it->second;
                    return is_valid(id);
                }
                else return false;
            }

            bool is_occupied(const int& i, const int& j) { return is_occupied({i, j}); }

            bool is_valid(int id) { return has(id) && validity[id]; }

            bool has(int id) { return id >= 0 && id < coordinates.size(); }

            bool in_bounds(pos _pos, int obj_width = 1, int obj_height = 1)
            {
                return _pos.x >= 0 && _pos.y >= 0 &&
                       _pos.x + obj_width <= SCREEN_WIDTH &&
                       _pos.y + obj_height <= SCREEN_HEIGHT;
            }

            bool in_bounds(float x, float y, int obj_width = 1, int obj_height = 1)
            { return in_bounds(pos({x, y}), obj_width, obj_height); }
        };
    }
}
