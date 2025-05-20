#pragma once

#include "Externals.h"

namespace RetroCS
{
    namespace Tools
    {
        template <typename T>
        struct Container : public BaseObject
        {
            static_assert(is_base_of_v<BaseObject, T>, "T must derive from BaseObject");
            public:
                Container() : BaseObject() {}
                ~Container() { clear(); }
                
                using iterator = typename vector<T*>::iterator;
                using const_iterator = typename vector<T*>::const_iterator;

                template <typename M, typename = enable_if_t<is_base_of_v<T, M>>>
                void add(string _alias)
                {
                    if(!has(_alias))
                    {
                        objects.push_back(new M());
                        objects[objects.size() - 1]->init(objects.size() - 1, _alias, this);
                        object_by_alias[_alias] = objects.size() - 1;
                        objects_by_type[type_index(typeid(T))].push_back(objects.back()->ID);
                    }
                }

                void add(T* item)
                {
                    objects.push_back(item);
                    object_by_alias[item->alias] = item->ID;
                    objects_by_type[type_index(typeid(*item))].push_back(item->ID);
                }

                bool has(string _alias) { return object_by_alias.find(_alias) != object_by_alias.end(); }

                template <typename M, typename = enable_if_t<is_base_of_v<T, M>>>
                bool has() const
                {
                    auto it = objects_by_type.find(type_index(typeid(M)));
                    return (it != objects_by_type.end() && !it->second.empty());
                }

                T* get(string _alias)
                {
                    auto aliasIt = object_by_alias.find(_alias);
                    if (aliasIt == object_by_alias.end()) { return nullptr; }

                    size_t globalIndex = aliasIt->second;
                    if (globalIndex >= objects.size()) { return nullptr; }

                    return objects[globalIndex];
                }

                template <typename M, typename = enable_if_t<is_base_of_v<T, M>>>
                M* get(const string& _alias) { return dynamic_cast<M*>(get(_alias)); }

                vector<T*> all() const { return objects; }

                template <typename M, typename = enable_if_t<is_base_of_v<T, M>>>
                vector<M*> all() const
                {
                    vector<M*> results;
                    for (auto* obj : objects)
                    {
                        if (auto casted = dynamic_cast<M*>(obj))
                            results.push_back(casted);
                    }
                    
                    return results;
                }

                void remove(size_t id)
                {
                    if (id >= objects.size())
                        return;

                    delete objects[id];

                    for(auto it = object_by_alias.begin(); it != object_by_alias.end(); )
                    {
                        if(it->second == id)
                            it = object_by_alias.erase(it);
                        else
                            ++it;
                    }

                    for(auto& [type, vec] : objects_by_type)
                    {
                        vec.erase(std::remove(vec.begin(), vec.end(), static_cast<int>(id)), vec.end());
                    }

                    objects.erase(objects.begin() + id);

                    for(auto& [alias, index] : object_by_alias)
                    {
                        if(index > id)
                            --index;
                    }
                    for(auto& [type, vec] : objects_by_type)
                    {
                        for(auto& idx : vec)
                        {
                            if(idx > id)
                                --idx;
                        }
                    }
                }

                void remove(const string& alias)
                {
                    auto it = object_by_alias.find(alias);
                    if(it != object_by_alias.end()) { remove(it->second); }
                }
                
                template <typename M, typename = enable_if_t<is_base_of_v<T, M>>>
                void remove()
                {
                    auto typeIt = objects_by_type.find(type_index(typeid(T)));
                    if(typeIt == objects_by_type.end())
                        return;

                    auto& ids = typeIt->second;
                    sort(ids.begin(), ids.end(), greater<int>());

                    for(auto id : ids) { remove(id); }
                }

                void remove(T* object)
                {
                    auto& objs = this->objects;

                    auto it = std::find(objs.begin(), objs.end(), object);
                    if(it == objs.end()) return;

                    size_t id = std::distance(objs.begin(), it);

                    delete *it;

                    objs.erase(it);

                    for(auto itAlias = object_by_alias.begin(); itAlias != object_by_alias.end(); )
                    {
                        if(itAlias->second == static_cast<int>(id))
                            itAlias = object_by_alias.erase(itAlias);
                        else
                            ++itAlias;
                    }

                    for(auto& [type, vec] : objects_by_type)
                    {
                        vec.erase(std::remove(vec.begin(), vec.end(), static_cast<int>(id)), vec.end());
                    }

                    for(auto& [alias, index] : object_by_alias)
                    {
                        if(index > id)
                            --index;
                    }
                    
                    for(auto& [type, vec] : objects_by_type)
                    {
                        for(auto& idx : vec)
                        {
                            if(idx > id)
                                --idx;
                        }
                    }
                }

                void clear()
                {
                    for (auto* obj : objects) delete obj;
                    objects.clear();
                    objects_by_type.clear();
                    object_by_alias.clear();
                }

                iterator begin() { return objects.begin(); }
                iterator end() { return objects.end(); }

                const_iterator begin() const { return objects.begin(); }
                const_iterator end() const { return objects.end(); }
            
            private:
                vector<T*> objects;
                unordered_map<type_index, vector<int>> objects_by_type;
                unordered_map<string, int> object_by_alias;
        };
    }
}