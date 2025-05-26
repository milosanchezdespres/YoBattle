#include "retrocs/retrocs.h"

int main()
{
    Scene scene;

    Entity entity = scene.spawn<Entity>({7, 2});
    Entity entity2 = scene.spawn<Entity>({4, 8});

    debug(entity.id);
    debug(entity2.id);
    debug(entity.transform().i(), entity.transform().j());

    Entity entity3 = scene.get_at<Entity>({4, 8});
    debug(entity3.transform().j());

    return 0;
}