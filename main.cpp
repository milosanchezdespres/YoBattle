#include "RetroCS/RetroCS.h"

struct Test : public object { Test() : object() {} };
struct Test2 : public Test { Test2() : Test() {} };

int main()
{
    hub::init();

    Test2* test2 = new Test2();
    test2->init();

    Test* test = new Test();
    test->init(0, "", test2);

    debug(test->owner()->alias);
    debug(test->owner<Test2>()->alias);

    return 0;
}