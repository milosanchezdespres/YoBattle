#include "includes.h"

int main()
{
    Entity* test = new Entity();
    test->load("test", "entities");

    cout << test << endl;

    return 0;
}