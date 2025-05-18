#include "ECS/ECS.h"

int main()
{
    Entity* test = new Entity();
    test->init(0, "test_entity", nullptr);

    test->add<Component>("test_component1");
    test->add<Component>("test_component2");
    test->add<Component>("test_component3");
    test->add<Component>("test_component4");
    test->add<Component>("test_component5");
    test->add<Component>("test_component6");
    test->add<Component>("test_component7");

    test->remove("test_component5");

    for(auto* component : *test)
    {
        print(to_string(component->ID) + " :: " + component->alias);
    }

    return 0;
}