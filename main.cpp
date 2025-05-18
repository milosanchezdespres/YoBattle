#include "ECS/includes.h"
//#include "Game/TestSystem.h"

int main()
{
    Scene* test = new Scene();
    test->init(1, "my_scene");
    //test->start<TestSystem>();

    test->add<Entity>("TestEntity1");

    test->attach<Component>("TestEntity1", "TestComponent1");
    test->attach<Component>("TestEntity1", "TestComponent2");
    test->attach<Component>("TestEntity1", "TestComponent3");
    test->attach<Component>("TestEntity1", "TestComponent4");
    test->attach<Component>("TestEntity1", "TestComponent5");

    test->entity("TestEntity1")->remove("TestComponent3");

    for (auto* obj : *test->entity("TestEntity1"))
    {
        print(to_string(obj->ID) + " :: " + obj->alias);
    }

    test->Update();

    test->Exit();

    return 0;
}