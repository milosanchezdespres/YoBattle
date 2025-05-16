#include "ECS/Seri.h"
using namespace ECS;

struct CustomSeri : public Seri
{
    float x, y;

    CustomSeri() : Seri()
    {
        x = 0;
        y = 0;

        __OnInit();
    }

    void __OnJson()
    {
        __json["x"] = x;
        __json["y"] = y;
    }

    void __OnLoad()
    {
        x = __json["x"];
        y = __json["y"];
    }
};

int main()
{
    CustomSeri* test = new CustomSeri();
    test->load("debug/test", false);

    cout << test << endl;

    return 0;
}