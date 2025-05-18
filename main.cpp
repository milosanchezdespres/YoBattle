#include "ECS/includes.h"

int main()
{
    Entity* test = new Entity();
    test->init(1, "TestEntity");
    test->attach<Component>("TestComponent1");
    test->attach<Component>("TestComponent2");
    test->attach<Component>("TestComponent3");
    test->attach<Component>("TestComponent4");
    test->attach<Component>("TestComponent5");

    for (auto* obj : *test)
    {
        print(to_string(obj->ID) + " :: " + obj->alias);
    }

    return 0;
}