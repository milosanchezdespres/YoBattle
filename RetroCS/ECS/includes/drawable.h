#pragma once

#include "../../Utils/Utils.h"

namespace retrocs
{
    namespace ecs
    {
        struct raw_screen_data
        {
            char texture[512]; 
            float x, y;
            float w, h;

            raw_screen_data()
            {
                x = 0;
                y = 0;
                w = 0;
                h = 0;
            }
        };

        struct drawable : public object
        {
            raw_screen_data* ___screen_data;

            drawable() : object() { ___screen_data = new raw_screen_data(); }

            raw_screen_data* raw()
            {
                ___screen_data->x = 0;
                ___screen_data->y = 0;
                ___screen_data->w = 0;
                ___screen_data->h = 0;

                _on_raw_conversion();

                return ___screen_data;
            }

            virtual void _on_raw_conversion() {}
        };
    }
}