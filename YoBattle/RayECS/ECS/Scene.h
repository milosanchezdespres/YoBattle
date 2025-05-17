#pragma once

#include "Utils.h"
#include "System.h"

namespace ECS
{
	struct Scene : public BaseObj
	{
		vector<Entity*> entities;
		unordered_map<string, int> entityByAlias;

		vector<BaseSystem*> systems;
		unordered_map<type_index, int> systemByTypeIndex;

		template <typename T>
		void add(string _alias)
		{
			if (entityByAlias.find(alias) == entityByAlias.end())
			{
				entities.push_back(new T());
				entities.back()->ID = entities.size() - 1;
				entities.back()->alias = _alias;
				entities.back()->parent = this;
				entityByAlias[_alias] = entities[entities.size() - 1]->ID;
			}
		}

		template <typename T>
		T* entity(string _alias)
		{
			auto it = entityByAlias.find(_alias);
			if (it != entityByAlias.end()) { return dynamic_cast<T*>(entities[it->second]); }
			return nullptr;
		}

		template <typename T>
		void start()
		{
			if (!has_system<T>())
			{
				systems.push_back(new T());
				systemByTypeIndex[type_index(typeid(T))] = systems.size() - 1;
			}
		}

		template <typename T>
		T* sys()
		{
			auto it = systemByTypeIndex.find(type_index(typeid(T)));
			if (it != systemByTypeIndex.end()) { return dynamic_cast<T*>(systems[it->second]); }
			return nullptr;
		}

		template <typename T>
		bool has_system() const
		{ return systemByTypeIndex.find(type_index(typeid(T))) != systemByTypeIndex.end(); }

		Scene() : BaseObj() { __OnSetup(); }

		template <typename T, typename M>
		void upload(string entity_alias, string component_alias)
		{
			auto* comp = entity<Entity>(entity_alias)->component<M>(component_alias);
			auto* system = sys<T>();
			system->upload(comp);
		}

		template <typename T>
		T* component(string entity_alias, string component_alias)
		{ return entity<Entity>(entity_alias)->component<T>(component_alias); }

		void Update(float delta)
		{
			for (auto it = systems.begin(); it != systems.end(); ++it)
			{
				auto* sys = *it;
				if (!sys->standalone) { sys->update(delta); }
			}
		}

		virtual void __OnSetup() {}
	};
}