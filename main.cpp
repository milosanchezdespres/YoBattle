#include "RetroCS/RetroCS.h"

struct Test : public object { Test() : object() {} };
struct TestBox : public box<Test> { TestBox() : box<Test>() {} };

int main()
{
    hub::init();

    TestBox* test_box = new TestBox();
    test_box->init(0);

    debug(type_to_string(hub::game));

    //...

    return 0;
}