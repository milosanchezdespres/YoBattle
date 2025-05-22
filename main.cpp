#include "RetroCS/RetroCS.h"

int main()
{
    Entity* test = new Entity();
    test->set_as(0, "test1");

    test->add<Component>("ddddd");

    cout << test->type() << endl;

    return 0;
}