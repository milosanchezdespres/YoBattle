#pragma once

#include "Utils.h"

namespace ECS
{
	struct Entity : public BaseObj
	{
		vector<Component*> components;
		unordered_map<type_index, vector<int>> componentsIndexByType;
		unordered_map<string, int> componentsIndexByAlias;

		Entity() : BaseObj() { OnSetup(); }

		template <typename T>
		void attach(string _alias = "")
		{
			if (_alias.empty()) { _alias = "unnamed"; }

			if (_alias != "unnamed" && componentsIndexByAlias.find(_alias) != componentsIndexByAlias.end())
			{ return; }

			components.push_back(new T());
			components.back()->ID = components.size() - 1;
			components.back()->alias = _alias;
			components.back()->parent = this;

			componentsIndexByType[type_index(typeid(T))].push_back(components.back()->ID);

			if (_alias != "unnamed")
			{ componentsIndexByAlias[components.back()->alias] = componentsIndexByType[type_index(typeid(T))].size() - 1; }
		}

		template <typename T>
		T* component(int index) { return dynamic_cast<T*>(components[index]); }

		template <typename T>
		T* component(string _alias)
		{
			auto typeIt = componentsIndexByType.find(type_index(typeid(T)));
			if (typeIt == componentsIndexByType.end()) return nullptr;

			auto aliasIt = componentsIndexByAlias.find(_alias);
			if (aliasIt == componentsIndexByAlias.end()) return nullptr;

			size_t subIndex = aliasIt->second;

			const auto& indices = typeIt->second;
			if (subIndex >= indices.size()) return nullptr;

			int globalIndex = indices[subIndex];

			return dynamic_cast<T*>(components[globalIndex]);
		}

		virtual void OnSetup() {}
	};
}