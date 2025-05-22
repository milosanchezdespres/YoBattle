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
    test->add<Test>("ooooooo");

    debug(test->get()->str_id());
    debug(test->get(0)->name());
    debug(test->get("test")->type());
    debug(test->get<Test>()->answer);

    debug("=========================================");

    test->get(1)->answer = 84;
    debug(test->get("dddd")->str_id());
    debug(test->get(1)->name());
    debug(test->get("dddd")->type());
    debug(test->get<Test>("dddd")->answer);

    debug("=========================================");

    test->get(1)->answer = 102;
    debug(test->get("ooooooo")->str_id());
    debug(test->get(1)->name());
    debug(test->get("ooooooo")->type());
    debug(test->get<Test>("ooooooo")->answer);

    debug("=========================================");

    debug(test->get(1) == test->get(1));
    debug(test->get(0) == test->get(1));

    debug("=========================================");

    test->remove("ooooooo");
    test->remove<Test>();

    for (auto* item : *test) { if (item) debug(item->str_id() + " : " + item->name()); }

    test->clean();

    debug("=========================================");

    for (auto* item : *test) { if (item) debug(item->str_id() + " : " + item->name()); }

    debug("=========================================");

    delete test;

    return 0;
}