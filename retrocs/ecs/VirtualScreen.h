#pragma once

#include "../utils.h"

#include "Component.h"
#include "Entity.h"

namespace retrocs
{
    namespace ecs
    {
        struct VirtualScreen
        {
            unordered_map<size_t, int> screen_space;
            vector<cell> coordinates;
            vector<int> validity;

            VirtualScreen()
            {
                //...
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
                    }

                    coordinates[id] = _new_cell;
                    screen_space[hash_id(_new_cell)] = id;
                    validity[id] = true;

                    return true;
                }

                return false;
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

                if(can_spawn)
                {
                    if(!item_found)
                    {
                        coordinates.push_back(_cell);
                        id = coordinates.size() - 1;
                    }

                    screen_space[hash_id(_cell)] = id;
                    
                    if(!item_found) validity.push_back(true);
                    else validity[id] = true;

                    return id;
                }

                return -1;
            }

            int spawn_at(const int& i, const int& j) { return spawn_at({i, j}); }

            void remove(int id)
            {
                cell _cell = tile(id);
                if(_cell.i != -999999) remove_at(_cell);
            }

            void remove_at(const cell& _cell)
            {
                auto it = screen_space.find(hash_id(_cell));
                bool item_found = it != screen_space.end();

                if(item_found)
                {
                    int id = it->second;
                    
                    validity[id] = false;
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

                    return is_valid(it->second);
                }
                else return false;
            }

            bool is_occupied(const int& i, const int& j) { return is_occupied({i, j}); }

            bool is_valid(int id) { return has(id) && validity[id]; }

            bool has(int id) { return id >= 0 && id < coordinates.size(); }

        };
    }
}