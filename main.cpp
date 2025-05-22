#include "RetroCS/RetroCS.h"

int main()
{
    SceneManager* test = new SceneManager();
    test->go_to<Scene>();

    debug(test->scene()->name());

    test->scene()->add<Entity>("test_entity");
    test->scene()->get("test_entity")->add<Component>("debug_component");

    debug(test->scene()->get("test_entity")->name());
    debug(test->scene()->get("test_entity")->get("debug_component")->name());

    return 0;
}