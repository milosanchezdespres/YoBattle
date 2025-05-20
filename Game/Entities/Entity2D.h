#pragma once

#include "../../RetroCS/RetroCS.h"

#include "../Components/Sprite.h"
#include "../Systems/SpriteRenderSystem.h"

namespace YoBattleGame
{
    namespace ECS
    {
        struct Entity2D : public Entity
        {
            Entity2D () : Entity()
            {
                add<Sprite>("body");
                upload_to<SpriteRenderSystem, Sprite>(Game::instance().scene(), "body");
            }
        };
    }
}
