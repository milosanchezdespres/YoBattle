#include "ECS/ECS_includes.h"

int main()
{
    Entity* test = new Entity();
    test->attach<Component>("test");

    cout << test->component<Component>("test")->ID << endl;

    return 0;
}