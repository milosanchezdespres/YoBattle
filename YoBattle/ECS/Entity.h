#pragma once

#include "Component.h"

namespace ECS
{
	struct Entity : public Component
	{
		string name;

		vector<Component*> components;
		unordered_map<type_index, int> componentIndexByType;

		Entity() : Component() { OnInit(); }

		template <typename T, typename... Args>
		void attach(Args&&... args)
		{
			components.push_back(new T(std::forward<Args>(args)...));
			components.back()->ID = components.size() - 1;
			components.back()->OnInit();
			componentIndexByType[type_index(typeid(T))] = components[components.size() - 1]->ID;
		}

		template <typename T>
		T* component(int index) { return dynamic_cast<T*>(components[index]); }

		template <typename T>
		T* component()
		{
			auto it = componentIndexByType.find(type_index(typeid(T)));
			if (it != componentIndexByType.end()) { return dynamic_cast<T*>(components[it->second]); }
			return nullptr;
		}

		void OnJson() override
		{
			__json2 = json::array();

			for (auto* component : components) { __json2.push_back(component->JSON()); }

			__json["components"] = __json2;
		}

		void OnLoad() override
		{ for (auto& [key, value] : __json["components"].items()) { OnLoadComponent(value); } }

		virtual void OnLoadComponent(json component_json)
		{
			if (component_json["alias"] == "Component")
			{
				attach<Component>();
				component<Component>()->standalone_load_from_current_json(component_json);
			}

			//...
		}
	};
}