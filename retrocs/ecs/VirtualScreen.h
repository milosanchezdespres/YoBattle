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

            void update(int id, int newi, int newj)
            {
                if(has(id) && is_valid(id))
                {
                    //...
                }
            }

            int entity_id_at(const cell& _cell)
            {
                if(is_occupied(_cell)) return screen_space[hash_id(_cell)];
                return -1;
            }

            int entity_id_at(const int& i, const int& j) { return entity_id_at({i, j}); }

            cell tile(int id)
            {
                if(has(id) && is_valid(id)) return coordinates[id];
                return {-999999, -999999};
            }

            int spawn_at(const cell& _cell)
            {
                auto it = screen_space.find(hash_id(_cell));
                bool item_found = it != screen_space.end();

                if(!item_found)
                {
                    coordinates.push_back(_cell);
                    screen_space[hash_id(_cell)] = coordinates.size() - 1;
                    validity.push_back(true);
                    return coordinates.size() - 1;
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
                    
                    validity[id] = !is_valid(id);
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

            bool is_valid(int id) { return validity[id]; }

            bool has(int id) { return id >= 0 && id < coordinates.size(); }

        };
    }
}