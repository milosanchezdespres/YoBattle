#include "retrocs/retrocs.h"

int main()
{
    Scene scene;

    Entity entity = scene.spawn<Entity>({7, 2});
    Entity entity2 = scene.spawn<Entity>({4, 8});
    Entity entity4 = scene.spawn<Entity>({1, 1});

    debug(entity.id);
    debug(entity2.id);
    debug(entity.transform().i(), entity.transform().j());

    Entity entity3 = scene.get_at<Entity>({4, 8});
    debug(entity3.transform().j());
    debug(entity4.transform().id);

    debug("....................................................................");

    for(int id : scene.screen_space.in_bounds_ids)
    {
        debug(id);
        debug(TO_POS(scene.get<Entity>(id).transform().i(), scene.get<Entity>(id).transform().j()).x, TO_POS(scene.get<Entity>(id).transform().i(), scene.get<Entity>(id).transform().j()).y);
    }

    return 0;
}