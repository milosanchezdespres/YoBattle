#include "ECS/ECS_includes.h"

int main()
{
    Scene* test = new Scene();
    test->add<Entity>("test");
    test->entity<Entity>("test")->attach<Component>("cddsq");

    cout << test->entity<Entity>("test")->component<Component>("cddsq")->alias << endl;

    return 0;
}