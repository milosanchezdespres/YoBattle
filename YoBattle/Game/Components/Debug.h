#pragma once

#include "../../ECS/ECS.h"
using namespace ECS;

struct Debug : public Component
{
    string message;

    Debug(string _message)
    {
        message = _message;
    }
};

struct DebugSystem : public ECS::system<Debug>
{
    DebugSystem() {}

    void update(float deltaTime) override
    {
        for (auto& entry : components)
        {
            DrawText(entry.component->message.c_str(), entry.owner->component<Sprite>()->x, entry.owner->component<Sprite>()->y, 20, DARKGRAY);
        }
    }
};