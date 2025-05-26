#include "retrocs/retrocs.h"

int main()
{
    Scene scene;
    VirtualScreen& screen = scene.screen_space;

    Entity entity1 = scene.spawn<Entity>({7, 2});
    Entity entity2 = scene.spawn<Entity>({4, 8});
    Entity entity3 = scene.spawn<Entity>({1, 1});

    scene.remove_at(4, 8);

    for(int i = 0; i < 120; i++)
    {
        entity3.place(screen, entity3.transform().x() + 4000 * 1.16, entity3.transform().y() + 400 * 1.16);
    }

    for (int id : screen.in_bounds_ids)
    {
        cell _cell = screen.tile(id);
        auto entity = scene.get_at<Entity>(_cell);

        debug(entity.id);
        debug(entity.transform().i());
        debug(entity.transform().j());
        debug(entity.transform().x());
        debug(entity.transform().y());
        debug(".......................................");
    }

    return 0;
}

