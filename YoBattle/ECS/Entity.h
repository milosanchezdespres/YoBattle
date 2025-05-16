#pragma once

#include "Component.h"

namespace ECS
{
	struct Entity : public Component
	{
		string type;

		vector<Component*> components;
		unordered_map<type_index, int> componentIndexByType;

		Entity() : Component()
		{
			OnInit();

			alias = "unnamed";
		}

		Entity(string _alias) : Component()
		{
			OnInit();

			alias = _alias;
		}

		void OnInit() override
		{
			type = class_name(this);

			OnSetup();
		}

		template <typename T, typename... Args>
		void attach(Args&&... args)
		{
			if (!has<T>())
			{
				components.push_back(new T(std::forward<Args>(args)...));
				components.back()->ID = components.size() - 1;
				components.back()->OnInit();
				componentIndexByType[type_index(typeid(T))] = components[components.size() - 1]->ID;
			}
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

		template <typename T>
		bool has() const
		{ return componentIndexByType.find(type_index(typeid(T))) != componentIndexByType.end(); }

		void OnJson() override
		{
			__json["type"] = type;

			__json2 = json::array();

			for (auto* component : components) { __json2.push_back(component->JSON()); }

			__json["components"] = __json2;
		}

		void OnLoad() override
		{
			components.clear();
			componentIndexByType.clear();

			for (auto& [key, value] : __json["components"].items()) { OnLoadComponent(value); }
		}

		virtual void OnLoadComponent(json component_json)
		{
			if (component_json["alias"] == "Component" && !has<Component>())
			{
				attach<Component>();
				component<Component>()->standalone_load_from_current_json(component_json);
			}

			//...
		}

		virtual void OnSetup() {}
	};
}