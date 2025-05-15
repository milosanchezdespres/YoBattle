#pragma once
#include "raylib.h"

#include <vector>
#include <iostream>
#include <any>
#include <string>
#include <unordered_map>
#include <typeindex>
#include <assert.h>
#include <initializer_list>
using namespace std;

#include "GameLoop/GameLoop.h" 

namespace ECS
{
    struct Component {
        int ID;
        virtual ~Component() { }
    };

    struct Scene;

    struct Entity {
        int ID;
        string alias;
        vector<Component*> components;
        unordered_map<type_index, int> componentIndexByType;
        vector<any> _params;

        virtual void OnLoad(Scene* scene, vector<any> _load_parameters)
            { _params = move(_load_parameters); }
        
        Entity()
        {
            ID = -1;
            alias = "unnamed";

            components.clear();
            componentIndexByType.clear();
        }

        template <typename T>
        T param(int index) { return any_cast<T>(_params[index]); }

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
            auto it = componentIndexByType.find(type_index(typeid(T)));
            if (it != componentIndexByType.end()) {  return dynamic_cast<T*>(components[it->second]); }
            return nullptr;
        }

        template <typename T>
        T* component(int index) { return dynamic_cast<T*>(components[index]); }

        Component* componentByType(const type_index& t)
        {
            auto it = componentIndexByType.find(t);
            if (it != componentIndexByType.end())
                return components[it->second];
            return nullptr;
        }
    };

    template<typename T>
    struct ComponentEntry {
        Entity* owner;
        T* component;
    };

    struct BaseSystem
    {
        int ID;

        virtual ~BaseSystem() = default;
        virtual void update(float deltaTime) = 0;
    };

    template<typename T>
    struct system : BaseSystem
    {
        vector<ComponentEntry<T>> components;
        unordered_map<T*, Entity*> componentToEntity;

        virtual ~system() = default;

        void _upload(T* component, Entity* entity)
        {
            components.push_back({ entity, component });
            componentToEntity[component] = entity;
        }

        void upload(Entity* entity)
        {
            T* component = entity->component<T>();
            if (component) _upload(component, entity);
        }

        Entity* owner(T* component) { return componentToEntity[component]; }

        virtual void update(float deltaTime) {}
    };

    struct Sprite : public Component
    {
        float x, y, scale;
        int size, tile_index;
        string texture;

        Sprite(string _texture, float _x, float _y, float _scale, int _size, int _tile_index)
        {
            x = _x;
            y = _y;
            scale = _scale;
            size = _size;
            tile_index = _tile_index;
            texture = _texture;
        }
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

    struct SpriteSystem : public system<Sprite>
    {
        SpriteSystem() { }
        
        void update(float deltaTime) override
        {
            for (auto& entry : components)
            {
                entry.component->x = entry.component->x + (entry.owner->component<Axis>()->x * entry.owner->component<Axis>()->speed * deltaTime);
                entry.component->y = entry.component->y + (entry.owner->component<Axis>()->y * entry.owner->component<Axis>()->speed * deltaTime);
            }
        }
    };

    struct Scene
    {
        int ID;
        string alias;

        vector<Entity*> entities;
        unordered_map<string, int> entityByAlias;

        vector<unique_ptr<BaseSystem>> systems;
        unordered_map<type_index, int> systemByAlias;

        template <typename TGame>
        Scene(TGame* game, vector<string> textures)
        {
            ID = -1;
            alias = "unnamed";

            entities.clear();
            entityByAlias.clear();

            systems.clear();
            systemByAlias.clear();

            add(new SpriteSystem());

            for (string texture : textures)
            {
                game->load_texture(texture);
            }
        }

        virtual ~Scene() = default;

        void update(float deltaTime)
        {
            for (auto& sys : systems) { sys->update(deltaTime); }
        }

        template <typename TGame>
        void draw(TGame* game)
        {
            for (Entity* entity : entities)
            {
                Component* baseComp = entity->componentByType(type_index(typeid(Sprite)));
                Sprite* sprite = dynamic_cast<Sprite*>(baseComp);
                if (sprite) game->blit(sprite);
            }
        }

        template <typename T>
        void push(string alias, T* entity)
        {
            entities.push_back(entity);
            entities.back()->ID = entities.size() - 1;
            entityByAlias[alias] = entities.back()->ID;
        }

        template <typename T>
        T* entity(string alias)
        {
            auto it = entityByAlias.find(alias);
            if (it != entityByAlias.end()) { return dynamic_cast<T*>(entities[it->second]); }
            return nullptr;
        }

        template <typename T>
        T* entity(int index) { return dynamic_cast<T*>(entities[index]); }

        Entity* entity(const string& alias)
        {
            auto it = entityByAlias.find(alias);
            if (it != entityByAlias.end()) return entities[it->second];
            return nullptr;
        }

        template <typename T>
        void add(T* system)
        {
            systems.emplace_back(std::unique_ptr<BaseSystem>(system));
            systems.back()->ID = systems.size() - 1;
            systemByAlias[type_index(typeid(T))] = systems.size() - 1;
        }

        template <typename T>
        T* sys()
        {
            auto it = systemByAlias.find(type_index(typeid(T)));
            if (it != systemByAlias.end())
            {
                BaseSystem* base = systems[it->second].get();
                return dynamic_cast<T*>(base);
            }
            return nullptr;
        }
    };
}