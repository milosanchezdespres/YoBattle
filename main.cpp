#include "RetroCS/RetroCS.h"

int main()
{
    Scene* test = new Scene();
    test->set_as(0, "test1");

    test->add<Entity>("entity1");
    test->get("entity1")->add<Component>("component1");

    cout << test->get("entity1")->get("component1")->owner<Entity>()->name() << endl;

    return 0;
}