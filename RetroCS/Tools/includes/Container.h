#pragma once

#include "Externals.h"

namespace RetroCS
{
    namespace Tools
    {
        struct Alias
        {
            int id;
            string name;
            type_index type;
            string str_type;

            Alias() : id(-1), name("no_name"), type(typeid(void)), str_type("no_type") {}

            template <typename T>
            Alias(const T& obj, int _id, string _name = "") : id(_id), name(_name), type(typeid(obj))
            {
                if (obj == nullptr)
                {
                    type = std::type_index(typeid(void));
                    str_type = "no_type";
                    if (name == "") name = "no_name";
                    return;
                }

                type = std::type_index(typeid(*obj));

                str_type = to_string(type);

                if (name == "") name = str_type;
            }

            bool operator==(const Alias& other) const
            {
                return name == other.name && type == other.type;
            }

            static inline string to_string(type_index type)
            {
                int status = 0;
                char* demangled = abi::__cxa_demangle(type.name(), nullptr, nullptr, &status);
                string result = (status == 0) ? demangled : type.name();
                free(demangled);

                size_t pos = result.rfind("::");
                if (pos != string::npos)
                    result = result.substr(pos + 2);

                while (!result.empty() && result.back() == '*')
                    result.pop_back();

                while (!result.empty() && isspace(result.back()))
                    result.pop_back();

                transform(result.begin(), result.end(), result.begin(), ::tolower);

                return result;
            }
        };

        struct BaseObject
        {
            Alias alias;
            BaseObject* parent = nullptr; 

            BaseObject() {}
            ~BaseObject() { parent = nullptr; }

            void init() { OnInit(); }
            virtual void OnInit() {}

            int id() { return alias.id; }
            string str_id() { return to_string(alias.id); }
            string name() { return alias.name; }
            string type() { return alias.str_type; }

            void set_as(int _id, string _name = "") { alias = Alias(this, _id, _name); }

            BaseObject* owner() { return parent; }

            template <typename T>
            T* owner() { return dynamic_cast<T*>(parent); }

            bool operator==(const BaseObject& other) const
            {
                return alias.id == other.alias.id &&
                    alias.name == other.alias.name &&
                    alias.type == other.alias.type &&
                    alias.str_type == other.alias.str_type;
            }

            bool operator!=(const BaseObject& other) const { return !(*this == other); }
        };
    }
}

namespace std
{
    template <>
    struct hash<RetroCS::Tools::Alias>
    {
        size_t operator()(const RetroCS::Tools::Alias& alias) const
        {
            return hash<string>()(alias.name) ^ hash<type_index>()(alias.type);
        }
    };
}

namespace RetroCS
{
    namespace Tools
    {
        template <typename T>
        struct Container : public BaseObject
        {
            static_assert(is_base_of_v<BaseObject, T>, "T must derive from BaseObject");

            vector<T*> items;
            unordered_map<Alias, int> item_by_alias;
            unordered_set<string> alias_names;
            unordered_map<string, int> item_by_name;

            Container() : BaseObject() {}
            ~Container() { clear(); }

            template <typename M, typename = enable_if_t<is_base_of_v<T, M>>>
            void add(string name = "")
            {
                if (name == "") name = Alias::to_string(type_index(typeid(M)));

                M* obj = new M();
                int index = (int)items.size();

                Alias alias(obj, index, name);

                if (!alias_names.contains(name) &&
                    item_by_alias.find(alias) == item_by_alias.end() &&
                    item_by_name.find(name) == item_by_name.end())
                {
                    items.push_back(obj);
                    item_by_alias[alias] = index;
                    alias_names.insert(alias.name);
                    item_by_name[alias.name] = index;

                    obj->alias = alias;
                    obj->parent = dynamic_cast<BaseObject*>(this);
                    obj->init();

                    OnAdd(alias.name);
                }
                else
                {
                    delete obj;
                }
            }

            T* get(int id) const
            {
                Alias dummy_alias;
                dummy_alias.id = id;

                auto it = item_by_alias.find(dummy_alias);
                if (it != item_by_alias.end())
                {
                    int index = it->second;
                    return items[index];
                }

                return nullptr;
            }

            T* get(string name = "") const
            {
                if (name == "") name = Alias::to_string(type_index(typeid(T)));

                auto it = item_by_name.find(name);
                if (it != item_by_name.end())
                {
                    int index = it->second;
                    return items[index];
                }
                return nullptr;
            }

            template <typename M, typename = enable_if_t<is_base_of_v<T, M>>>
            M* get(int id) { return dynamic_cast<M*>(this->get(id)); }

            template <typename M, typename = enable_if_t<is_base_of_v<T, M>>>
            M* get(string name = "")
            {
                if (name == "") name = Alias::to_string(type_index(typeid(M)));

                auto it = item_by_name.find(name);
                if (it != item_by_name.end())
                {
                    int index = it->second;
                    return dynamic_cast<M*>(items[index]);  // <-- explicit cast here
                }
                return nullptr;
            }

            bool has(const string& name) const { return alias_names.find(name) != alias_names.end(); }

            void remove(int id)
            {
                Alias dummy;
                dummy.id = id;

                auto it = item_by_alias.find(dummy);
                if (it == item_by_alias.end()) return;

                int index = it->second;
                T* obj = items[index];
                if (!obj) return;

                alias_names.erase(obj->alias.name);
                item_by_name.erase(obj->alias.name);
                item_by_alias.erase(obj->alias);

                delete obj;
                items[index] = nullptr;
            }

            void remove(string name = "")
            {
                auto it = item_by_name.find(name);
                if (it == item_by_name.end()) return;

                int index = it->second;
                T* obj = items[index];
                if (!obj) return;

                alias_names.erase(obj->alias.name);
                item_by_name.erase(obj->alias.name);
                item_by_alias.erase(obj->alias);

                delete obj;
                items[index] = nullptr;
            }

            template <typename M, typename = enable_if_t<is_base_of_v<T, M>>>
            void remove(string name = "")
            {
                if (name == "") name = Alias::to_string(type_index(typeid(M)));
                remove(name);
            }

            virtual void clear()
            {
                for (T* obj : items) { if (obj) delete obj; }

                items.clear();
                item_by_alias.clear();
                item_by_name.clear();
                alias_names.clear();
            }

            virtual void OnAdd(string name) {}

            vector<T*> valid_items() const
            {
                vector<T*> valid;
                for (T* item : items)
                    if (item)
                        valid.push_back(item);
                return valid;
            }

            auto begin() { return items.begin(); }
            auto end()   { return items.end(); }
            auto begin() const { return items.begin(); }
            auto end()   const { return items.end(); }

            size_t size() const { return items.size(); }
        };
    }
}