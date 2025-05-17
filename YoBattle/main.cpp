#include "ECS/ECS_includes.h"

int main()
{
    Scene* test = new Scene();
    test->start<RenderSystem>();
    test->add<Entity>("test");

    test->entity<Entity>("test")->attach<Sprite>("sprite1");
    test->sys<RenderSystem>()->upload(test->entity<Entity>("test")->component<Sprite>("sprite1"));

    test->Update(0.0f);
    //...

    return 0;
}