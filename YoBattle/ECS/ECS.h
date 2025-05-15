#pragma once
#include "raylib.h"

#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <typeindex>
using namespace std;

namespace ECS
{
    struct Component {
        int ID;
        virtual ~Component() { ID = -1; }
    };

    struct Entity {
        int ID;
        string alias;
        vector<Component*> components;
        std::unordered_map<std::type_index, int> componentIndexByType;

        Entity()
        {
            ID = -1;
            alias = "unnamed";
            components = {};
        }

        template <typename T>
        void push(T* component)
        {
            components.push_back(component);
            components[components.size() - 1]->ID = components.size() - 1;
            componentIndexByType[type_index(typeid(T))] = components[components.size() - 1]->ID;
        }

        Component* component(int ID) { return components[ID]; }

        template <typename T>
        T* component()
        {
            auto it = componentIndexByType.find(std::type_index(typeid(T)));
            if (it != componentIndexByType.end()) {
                return dynamic_cast<T*>(components[it->second]);
            }
            return nullptr;
        }

        template <typename T>
        T* component(int index) {
            return dynamic_cast<T*>(components[index]);
        }
    };

    template<typename T>
    struct system
    {
        vector<T*> components;

        void upload(T* component) { components.push_back(component); }

        virtual ~system() = default;
        virtual void update(float deltaTime) {}
    };

    struct Axis : public Component
    {
        int x, y;
        float speed;

        Axis(float _speed)
        {
            x = 0;
            y = 0;
            speed = _speed;
        }
    };

    struct Sprite : public Component
    {
        float x, y, scale;
        int size, tile_index;
        string texture;
        Axis* axis;

        Sprite(string _texture, float _x, float _y, float _scale, int _size, int _tile_index)
        {
            axis = new Axis(0);
            x = _x;
            y = _y;
            scale = _scale;
            size = _size;
            tile_index = _tile_index;
            texture = _texture;
        }
    };

    struct SpriteSystem : public system<Sprite>
    {
        SpriteSystem() { }
        
        void update(float deltaTime) override
        {
            for (auto* sprite : components)
            {
                sprite->x = sprite->x + (sprite->axis->x * sprite->axis->speed * deltaTime);
                sprite->y = sprite->y + (sprite->axis->y * sprite->axis->speed * deltaTime);
            }
        }
    };
}