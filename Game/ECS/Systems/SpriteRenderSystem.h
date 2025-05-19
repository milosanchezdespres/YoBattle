#pragma once

#include "../../../ECS/ECS.h"
#include "../Components/Sprite.h"

namespace YOBATTLE
{
    struct SpriteRenderSystem : System<Sprite>
    {
        SpriteRenderSystem() : System() { standalone = true; }

        void OnUpdate(float delta, Component* _component) override
        {
            Sprite* component = cast(_component);

            DrawText(component->alias.c_str(), 190, 200, 20, DARKGRAY);
        }
    };
}