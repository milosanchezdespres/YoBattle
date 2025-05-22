#pragma once

#include "../../Tools/Tools.h"

namespace RetroCS
{
    namespace ECS
    {
        struct Component : public BaseObject
        {
            bool initialized;

            Component() : BaseObject() { initialized = false; }
            
            void init()
            {
                if(!initialized)
                {
                    OnInit();
                    initialized = true;
                }
            }

            virtual void OnInit() {}
        };
    }
}