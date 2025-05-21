#pragma once

#include "../../RetroCS/RetroCS.h"
#include "../Components/Animations.h"

namespace YoBattleGame
{
    namespace ECS
    {
        struct AnimationSystem : public System<Animations>
        {
            AnimationSystem () : System<Animations>() { }

            void OnDraw(Entity* owner, Animations* component) override
            {
                if(!HUB::get<bool>("input_required"))
                {
                    component->previous = component->current;
                    component->current = component->animation(
                        owner->get<StateMachine>("states")->current(),
                        owner->get<StateMachine>("states")->axis
                    );

                    if (component->current != nullptr)
                    {
                        if (component->previous != component->current && component->previous != nullptr)
                        {
                            if (component->previous->index >= component->previous->frames.size())
                                component->previous->index = 0;

                            if (component->current->index >= component->current->frames.size())
                                component->current->index = 0;

                            component->current->timer = 0;
                            component->current->index = 0;
                        }

                        component->current->timer += Game::instance().delta();
                        float frame_time = 1.0f / component->speed;

                        while (component->current->timer >= frame_time)
                        {
                            component->current->timer -= frame_time;
                            component->current->index++;

                            if (component->current->index >= component->current->frames.size())
                                component->current->index = 0;
                        }

                        owner->get<Sprite>("body")->tile->index = component->current->frames[component->current->index];
                    }
                }
            }

        };
    }
}