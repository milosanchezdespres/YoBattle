#include "includes.h"

int main()
{
    Entity* test = new Entity();
    test->add<Component>();

    test->save("");
    test->component<Component>()->save("");

    return 0;
}