#pragma once

#include "Utils.h"

namespace ECS
{
	struct Scene
	{
		string alias;
		string type;

		vector<Entity*> entities;
		unordered_map<string, int> entitityIndexByAlias;

		//...
		json __json;
		json __json2;
		//...

		Scene() : alias("unnamed"), __json(nullptr) { }

		Scene(string _alias)
		{
			__json = nullptr;

			alias = _alias;
			type = class_name(this);
		}

		void save()
		{
			ofstream* file = to_file("scenes", alias, "json");

			if (file->is_open())
			{
				*file << setw(4) << JSON() << endl;
				file->close();
			}
		}

		void load(EntityFactory* factory)
		{
			entities.clear();
			entitityIndexByAlias.clear();

			json loaded_json(json::parse(file_2_string("scenes", alias, "json")));
			json loaded_entities(loaded_json["entities"]);

			alias = loaded_json["alias"];
			type = loaded_json["type"];

			for (const auto& entity : loaded_entities) { factory->factor(this, entity); }
		}

		template <typename T, typename... Args>
		void attach(string entity_alias, Args&&... args)
		{
			entities.push_back(new T(std::forward<Args>(args)...));
			entities.back()->ID = entities.size() - 1;
			entities.back()->alias = entity_alias;
			entities.back()->OnInit();
			entitityIndexByAlias[entity_alias] = entities[entities.size() - 1]->ID;
		}

		//template <typename T>
		//T* entity(int index) { return dynamic_cast<T*>(entities[index]); }

		template <typename T>
		T* entity(string entity_alias)
		{
			auto it = entitityIndexByAlias.find(entity_alias);
			if (it != entitityIndexByAlias.end()) { return dynamic_cast<T*>(entities[it->second]); }
			return nullptr;
		}

		template <typename T>
		bool has(string entity_alias) const
		{ return entitityIndexByAlias.find(entity_alias) != entitityIndexByAlias.end(); }

		json JSON()
		{
			__json = json();
			__json["alias"] = alias;
			__json["type"] = type;

			__json2 = json::array();

			for (auto* entity : entities) { __json2.push_back(entity->JSON()); }

			__json["entities"] = __json2;

			OnJson();

			return __json;
		}

		virtual void OnJson() {}
		virtual void OnLoad() {}
	};

	ostream& operator<<(ostream& os, Scene& c) { return os << c.JSON().dump(4); }
	ostream& operator<<(ostream& os, Scene* c) { return os << c->JSON().dump(4); }
}