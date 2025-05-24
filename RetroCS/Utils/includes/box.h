#pragma once

#include "ext_includes.h"
#include "object.h"

namespace retrocs
{
    namespace utils
    {
        template <typename T, typename = enable_if_t<is_base_of_v<object, T>>>
        struct box : public object
        {
            vector<T*> items;
            unordered_map<string, int> items_by_alias;
            unordered_map<int, string> alias_by_index;

            box() : object() {}

            void _on_init() override {}

            template <typename U, typename = enable_if_t<is_base_of_v<T, U>>>
            void add(string _alias = "")
            {
                U* new_item = new U();
                new_item->init(items.size(), _alias, this);

                push(new_item);
            }

            void push(T* new_item)
            {
                if (items_by_alias.find(new_item->alias) == items_by_alias.end())
                {
                    items.push_back(new_item);
                    items_by_alias[new_item->alias] = items.size() - 1;
                    alias_by_index[items.size() - 1] = new_item->alias;

                    on_add(new_item);
                }
            }

            T* get(int id) { return items[id]; }

            template <typename U, typename = enable_if_t<is_base_of_v<T, U>>>
            U* get(int id) { return dynamic_cast<U*>(items[id]); }

            T* get(const string& alias)
            {
                auto it = items_by_alias.find(alias);
                if (it == items_by_alias.end()) return nullptr;
                return get(it->second);
            }

            template <typename U, typename = enable_if_t<is_base_of_v<T, U>>>
            U* get(const string& alias)
            {
                auto it = items_by_alias.find(alias);
                if (it == items_by_alias.end()) return nullptr;
                return get<U>(it->second);
            }

            template <typename U, typename = enable_if_t<is_base_of_v<T, U>>>
            U* get()
            {
                const string alias = type_to_string<U>();
                auto it = items_by_alias.find(alias);
                if (it == items_by_alias.end()) return nullptr;
                return dynamic_cast<U*>(items[it->second]);
            }

            void remove(int id)
            {
                auto alias_it = alias_by_index.find(id);
                if (alias_it != alias_by_index.end())
                {
                    items_by_alias.erase(alias_it->second);
                    alias_by_index.erase(alias_it);
                }

                delete items[id];
                items.erase(items.begin() + id);

                unordered_map<int, string> new_alias_by_index;
                new_alias_by_index.reserve(alias_by_index.size());

                for (auto& [old_index, alias] : alias_by_index)
                {
                    int new_index = old_index > id ? old_index - 1 : old_index;
                    new_alias_by_index[new_index] = alias;
                    items_by_alias[alias] = new_index;
                }

                alias_by_index = std::move(new_alias_by_index);
            }

            void remove(const string& alias)
            {
                auto it = items_by_alias.find(alias);
                if (it == items_by_alias.end()) return;

                int id = it->second;

                items_by_alias.erase(it);
                alias_by_index.erase(id);

                delete items[id];
                items.erase(items.begin() + id);

                unordered_map<int, string> new_alias_by_index;
                new_alias_by_index.reserve(alias_by_index.size());

                for (const auto& [old_index, a] : alias_by_index)
                {
                    int new_index = old_index > id ? old_index - 1 : old_index;
                    new_alias_by_index[new_index] = a;
                    items_by_alias[a] = new_index;
                }

                alias_by_index = std::move(new_alias_by_index);
            }

            template <typename U, typename = enable_if_t<is_base_of_v<T, U>>>
            void remove() { remove(type_to_string<U>()); }

            void update() { for(T* item : items) on_update(item); }

            void clear()
            {
                items.clear();
                items_by_alias.clear();
            }

            auto begin() { return items.begin(); }
            auto end()   { return items.end(); }
            auto begin() const { return items.begin(); }
            auto end()   const { return items.end(); }

            size_t size() const { return items.size(); }

            void _on_destroy() override
            {
                for (T* item : items) { delete item; }
                clear();
            }

            virtual void on_add(T* item) {}
            virtual void on_update(T* item) {}
        };
    }
}