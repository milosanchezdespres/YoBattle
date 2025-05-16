#include "includes.h"

int main()
{
    Entity* test = new Entity();
    test->load("Entity");

    cout << test << endl;

    return 0;
}