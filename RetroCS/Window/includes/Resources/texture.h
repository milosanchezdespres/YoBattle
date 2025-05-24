#pragma once

#include "../../../Utils/Utils.h"

namespace retrocs
{
    namespace window
    {
        struct texture : public Resource<Texture2D>
        {
            texture() : Resource<Texture2D>() { }

            texture(string _name, string _folders = "") { load(_name, _folders); }
                        
            void load(string _name, string _folders = "") override
            {
                const char* path = __get_path("png", _name, _folders);

                data = new Texture2D(LoadTexture(path));
                name = _name;
            }


            void unload() override
            {
                if (data != nullptr)
                {
                    UnloadTexture(*data);
                    data = nullptr;
                }
            }
        };
    }
}