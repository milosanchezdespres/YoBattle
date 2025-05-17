#pragma once

#include "Utils.h"

namespace ECS
{
	struct Scene : public BaseObj
	{
		vector<Entity*> entities;
		unordered_map<string, int> entityByAlias;

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

		Scene() : BaseObj() { }
	};
}