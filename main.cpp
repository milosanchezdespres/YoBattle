#include "ECS/ECS.h"

struct TestScene : public Scene
{
    TestScene() : Scene() {}

    void OnEnter() override
    {
        add<Entity>("test_entity1");
        get<Entity>("test_entity1")->add<Component>("test_component1");
        get<Entity>("test_entity1")->add<Component>("test_component2");
        get<Entity>("test_entity1")->add<Component>("test_component3");
        get<Entity>("test_entity1")->add<Component>("test_component4");
        get<Entity>("test_entity1")->remove("test_component3");
    }

    void OnUpdate(float delta)
    {
        for(auto* component : get<Entity>("test_entity1")->all()) { print(to_string(component->ID) + " :: " + component->alias); }
    }
};

int main()
{
    SceneManager* test = new SceneManager();
    test->go_to<TestScene>();

    test->update(0);

    return 0;
}