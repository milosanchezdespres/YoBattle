#include "ECS/includes.h"

int main()
{
    Entity* test = new Entity();
    test->init(1, "TestEntity");
    test->attach<Component>("TestComponent");
    test->attach<Component>("TestComponent2");
    test->attach<Component>("TestComponent3");
    test->attach<Component>("TestComponent4");
    test->attach<Component>("TestComponent5");

    for (auto* obj : *test)
    {
        print(obj->alias);
    }

    return 0;
}