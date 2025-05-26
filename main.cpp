#include "retrocs/retrocs.h"

int main()
{
    Scene scene;

    Entity entity1 = scene.spawn<Entity>({7, 2});
    Entity entity2 = scene.spawn<Entity>({4, 8});
    Entity entity6 = scene.spawn<Entity>({1, 1});

    scene.remove_at(4, 8);

    for(cell _cell : scene)
    {
        auto entity = scene.get_at<Entity>(_cell);

        debug(entity.transform().x());
        debug(entity.transform().y());
    }

    return 0;
}

