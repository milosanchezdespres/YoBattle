#include "ECS/Seri.h"
#include "ECS/Factory.h"
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

class CustomFactory : public Factory
{
    public:
        CustomFactory() : Factory() {}

        Seri* OnExtraFactor(json json_data) override
        {
            if (json_data["type"] == "CustomSeri") { return (new CustomSeri())->load(json_data); }

            return __default;
        }
};

int main()
{
    CustomFactory* factory = new CustomFactory();

    CustomSeri* test = new CustomSeri();
    test->load("debug/test", false);

    auto* test_copy = factory->factor(TO_JSON(test));

    cout << test << endl;
    cout << "=============" << endl;
    cout << test_copy << endl;

    return 0;
}