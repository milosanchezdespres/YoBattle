#include "ECS/ECS.h"

struct TestComponent : public Component
{
    float x;

    TestComponent() : Component()
    {
        x = 0;
    }
};

struct TestSystem : System<TestComponent>
{
    TestSystem() : System() { }

    void OnUpdate(float delta, Component* _component) override
    {
        TestComponent* component = cast(_component);

        print(to_string(component->ID) + " :: " + component->alias);
    }
};

struct TestScene : public Scene
{
    TestScene() : Scene() {}

    void OnEnter() override
    {
        add<Entity>("test_entity1");
        get("test_entity1")->add<Component>("test_component1");
        get("test_entity1")->add<TestComponent>("test_component2");
        get("test_entity1")->add<TestComponent>("test_component3");
        get("test_entity1")->add<TestComponent>("test_component4");

        attach<TestSystem>();
        sys<TestSystem>()->upload(get<Entity>("test_entity1")->get("test_component2"));
        sys<TestSystem>()->upload(get<Entity>("test_entity1")->get("test_component3"));
    }
};

int main()
{
    SceneManager* test = new SceneManager();
    test->go_to<TestScene>();

    test->update(0);

    test->scene()->get("test_entity1")->remove("test_component3");
    test->scene()->sys<TestSystem>()->remove(test->scene()->get("test_entity1")->get("test_component3"));

    test->update(0);

    test->go_to<Scene>();

    test->update(0);

    return 0;
}