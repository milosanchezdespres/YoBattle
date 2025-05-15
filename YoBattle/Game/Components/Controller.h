#pragma once

#include "../../ECS/ECS.h"
using namespace ECS;

struct Controller : public Component
{
    int x, y;

    Controller() { x = 0; y = 0; }

    void listen()
    {
        if (IsKeyDown(KEY_W)) { y = -1; }
        if (IsKeyDown(KEY_A)) { x = -1; }
        if (IsKeyDown(KEY_S)) { y = 1; }
        if (IsKeyDown(KEY_D)) { x = 1; }
    }
};

struct ControllerSystem : public ECS::system<Controller>
{
    ControllerSystem() {}

    void listen() override
    {
        for (auto& entry : components)
        {
            entry.component->x = 0;
            entry.component->y = 0;
            entry.component->listen();
            entry.owner->component<Axis>()->x = entry.component->x;
            entry.owner->component<Axis>()->y = entry.component->y;
        }
    }
};