#pragma once

#include "Component.h"

namespace retrocs
{
    namespace ecs
    {
        struct Entity;

        struct StateMachine
        {
            Entity* owner;
        
            StateMachine() : owner(nullptr) {}

            void update();
        };

        struct Entity : public box<Component>
        {
            string main_drawable_name;

            StateMachine* states;

            Entity() : box<Component>()
            {
                states = new StateMachine();
                states->owner = this;

                //...
            }

            virtual bool is_in_bound() { return main_drawable_name != "" && get(main_drawable_name)->is_in_bound(); }
        };

        inline void StateMachine::update()
        {
            //...

            print(owner->alias);
        }
    }
}