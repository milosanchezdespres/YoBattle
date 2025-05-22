#include "RetroCS/RetroCS.h"

int main()
{
    SceneManager* test = new SceneManager();
    test->go_to<Scene>();

    debug(scene->name());

    scene->add<Entity>("test_entity");
    scene->get("test_entity")->add<Component>("debug_component");

    debug(scene->get("test_entity")->name());
    debug(scene->get("test_entity")->get("debug_component")->name());

    test->render();

    return 0;
}