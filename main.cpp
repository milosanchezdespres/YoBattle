#include "RetroCS/RetroCS.h"

struct Test : public BaseObject
{
    Test() : BaseObject() {}

    int answer = 42;
};

int main()
{
    Container<Test>* test = new Container<Test>();

    test->add<Test>();
    test->add<Test>("dddd");

    debug(test->get()->str_id());
    debug(test->get(0)->name());
    debug(test->get("test")->type());
    debug(test->get<Test>()->answer);

    test->get(1)->answer = 84;
    debug(test->get("dddd")->str_id());
    debug(test->get(1)->name());
    debug(test->get("dddd")->type());
    debug(test->get<Test>("dddd")->answer);

    return 0;
}