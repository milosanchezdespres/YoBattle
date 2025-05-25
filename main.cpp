#include "RetroCS/RetroCS.h"

int main()
{
    unordered_map<size_t, int> screen;
    vector<float> X;
    vector<float> Y;

    X.reserve(1'000'000);
    Y.reserve(1'000'000);
    screen.reserve(1'000'000);

    X.push_back(12);
    Y.push_back(34);

    int cell_x = 12 / 16;
    int cell_y = 34 / 16;
    int entity_id = X.size() - 1;

    size_t hashid = hash_coordinates(cell_x, cell_y);
    screen[hashid] = entity_id;

    entity_view entity = entity_view {screen[hashid], X, Y};
    debug(entity.x());

    int old_cell_x = cell_x;
    int old_cell_y = cell_y;

    cell_x = 182 / 16;
    cell_y = 246 / 16;

    size_t old_hashid = hash_coordinates(old_cell_x, old_cell_y);
    hashid = hash_coordinates(cell_x, cell_y);

    X[entity_id] = 182;
    Y[entity_id] = 246;

    if (old_hashid != hashid)
    {
        auto it = screen.find(old_hashid);

        if (it != screen.end() && it->second == entity_id) { screen.erase(it); }
        
        screen[hashid] = entity_id;
    }
    //if entity out of boundarie, remove it from world

    debug(entity.x());

    return 0;
}