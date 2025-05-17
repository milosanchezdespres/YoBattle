#include "ECS/ECS_includes.h"

int main()
{
    Scene* test = new Scene();
    test->start<RenderSystem>();
    test->add<Entity>("test");

    test->entity<Entity>("test")->attach<Sprite>("sprite1");
    test->entity<Entity>("test")->attach<Sprite>("sprite2");
    test->upload<RenderSystem, Sprite>("test", "sprite1");
    test->upload<RenderSystem, Sprite>("test", "sprite2");

    test->component<Sprite>("test", "sprite1")->x = 30;

    cout << test->component<Sprite>("test", "sprite1")->x << endl;

    test->Update(0.0f);
    //...

    return 0;
}