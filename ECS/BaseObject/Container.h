#pragma once

#include "BaseObject.h"

#include <vector>
#include <unordered_map>
#include <typeindex>
using namespace std;

namespace BaseECS
{
    struct Container : public BaseObject
    {
        public:
            Container() {}
            
            using iterator = vector<BaseObject*>::iterator;
            using const_iterator = vector<BaseObject*>::const_iterator;

            template <typename T>
            void add(string _alias = "")
            {
                if(_alias == "" || !has(_alias))
                {
                    objects.push_back(new T());
                    objects[objects.size() - 1]->init(objects.size() - 1, _alias, this);
                    object_by_alias[_alias] = objects.size() - 1;
			        objects_by_type[type_index(typeid(T))].push_back(objects.back()->ID);
                }
            }

            bool has(string _alias) { return object_by_alias.find(_alias) != object_by_alias.end(); }

            BaseObject* get(string _alias)
            {
                auto aliasIt = object_by_alias.find(_alias);
                if (aliasIt == object_by_alias.end()) 
                    return nullptr;

                size_t globalIndex = aliasIt->second;
                if (globalIndex >= objects.size()) { return nullptr; }

                return objects[globalIndex];
		    }

            template <typename T>
            T* get(string _alias) { return dynamic_cast<T*>(get(_alias)); }

            template <typename T>
            vector<T*> all() const
            {
                vector<T*> results;
                for (auto* obj : objects)
                {
                    if (auto casted = dynamic_cast<T*>(obj))
                        results.push_back(casted);
                }
                
                return results;
            }

            iterator begin() { return objects.begin(); }
            iterator end() { return objects.end(); }

            const_iterator begin() const { return objects.begin(); }
            const_iterator end() const { return objects.end(); }
        
        private:
            vector<BaseObject*> objects;
		    unordered_map<type_index, vector<int>> objects_by_type;
		    unordered_map<string, int> object_by_alias;
    };
}