#pragma once

#include "raylib.h"

#include "../../ECS/NlohmanJson/json.hpp"
using json = nlohmann::json;

#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <filesystem>
#include <any>
#include <string>
#include <unordered_map>
#include <typeindex>
#include <assert.h>
#include <initializer_list>
using namespace std;
namespace fs = std::filesystem;
using namespace fs;

#include "GameLoop/GameLoop.h" 

namespace ECS
{
    struct Component {
        int ID;
        virtual ~Component() { }
        virtual json JSON() const = 0;
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

        virtual json JSON() const {
            json j;
            j["type"] = "Entity";
            j["ID"] = ID;
            j["alias"] = alias;

            json components_json;
            for (const auto& comp : components)
                { components_json.push_back(comp->JSON()); }
            j["components"] = components_json;

            return j;
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

        json JSON() const override {
            return json{
                {"type", "Sprite"},
                {"x", x},
                {"y", y},
                {"scale", scale},
                {"size", size},
                {"tile_index", tile_index},
                {"texture", texture}
            };
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

        json JSON() const override {
            return json{
                {"type", "Axis"},
                {"x", x},
                {"y", y},
                {"speed", speed}
            };
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
        Scene(TGame* game, string _alias, vector<string> textures)
        {
            ID = -1;
            alias = _alias;

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

        void update(float deltaTime) { for (auto& sys : systems) { sys->update(deltaTime); } }

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
            entities.back()->alias = alias;
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

        json JSON() const {
            json j;
            j["ID"] = ID;
            j["alias"] = alias;

            json entities_json;
            for (const auto& ent : entities)
            {
                entities_json.push_back(ent->JSON());
            }
            j["entities"] = entities_json;

            return j;
        }

        void save() const
        {
            json j = this->JSON();

            path directory = "data/scenes";
            if (!exists(directory)) { create_directories(directory); }

            ofstream outFile("data/scenes/ " + alias + ".json");

            if (outFile.is_open())
            {
                outFile << std::setw(4) << j << std::endl;
                outFile.close();
            }
        }

        void load()
        {
            path directory = "data/scenes/" + alias + ".json";
            ifstream inFile(directory);

            if (inFile.is_open()) {
                json j;
                inFile >> j;
                inFile.close();

                entities.clear();
                systems.clear();

                this->ID = j["ID"];
                this->alias = j["alias"];

                if (j.contains("entities")) {
                    for (const auto& entityJson : j["entities"]) {
                        Entity* entity = nullptr;
                        std::string entityType = entityJson["type"];

                        entity = new Entity();

                        entity->ID = entityJson["ID"];
                        entity->alias = entityJson["alias"];

                        if (entityJson.contains("components")) {
                            for (const auto& componentJson : entityJson["components"]) {
                                string componentType = componentJson["type"];
                                if (componentType == "Sprite") {
                                    Sprite* sprite = new Sprite(
                                        componentJson["texture"],
                                        componentJson["x"],
                                        componentJson["y"],
                                        componentJson["scale"],
                                        componentJson["size"],
                                        componentJson["tile_index"]
                                    );
                                    entity->push(sprite);
                                }
                                else if (componentType == "Axis") {
                                    Axis* axis = new Axis(componentJson["speed"]);
                                    entity->push(axis);
                                }
                            }
                        }

                        entities.push_back(entity);
                        entityByAlias[entity->alias] = entity->ID;
                    }
                }
            }
        }
    };
}