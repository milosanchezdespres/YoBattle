#pragma once

#include "Component.h"

#include <vector>
using namespace std;

namespace ECS
{
	struct Entity : public Component
	{
		vector<Component*> components;
		unordered_map<type_index, int> componentIndexByType;

		Entity() : Component() { __init(); }

		json OnJson(json json_data) const override
		{
			__json__buffer2 = json();

			for (auto* component : components)
				{ __json__buffer2.push_back(component->JSON()); }

			if (__json__buffer2.empty()) { json_data["components"] = json::object();  }
			else { json_data["components"] = __json__buffer2; }

			return Component::OnJson(json_data);
		}

		template<typename T, typename... Args>
		void add(Args&&... args)
		{
			components.push_back(ComponentFactory::factory().create<T>(forward<Args>(args)...));
			components.back()->ID = components.size() - 1;
			components.back()->alias = typeid(T);
			componentIndexByType[type_index(typeid(T))] = components[components.size() - 1]->ID;
		}

		Component* component(int ID) { return components[ID]; }

		template <typename T>
		T* component()
		{
			auto it = componentIndexByType.find(type_index(typeid(T)));
			if (it != componentIndexByType.end()) { return dynamic_cast<T*>(components[it->second]); }
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
}