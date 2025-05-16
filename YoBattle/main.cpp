#include "includes.h"

int main()
{
    DebugEntity* test = new DebugEntity("test");
    test->load();

    cout << test << endl;

    return 0;
}