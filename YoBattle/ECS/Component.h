#pragma once

#include "Utils.h"

namespace ECS
{
	struct Component
	{
		int ID;
		string alias;

		string __current_loaded_alias;
		string __current_loaded_folders;
		json __previous_json;
		json __json;
		json __json2;

		Component() : ID(-1), alias("Component"), __json(nullptr) { OnInit(); }

		void save(string folders = "")
		{
			ofstream* file = to_file(folders, alias, "json");

			if (file->is_open())
			{
				*file << setw(4) << JSON() << endl;
				file->close();
			}
		}

		void load(string alias, string folders = "")
		{
			__current_loaded_alias = alias;
			__current_loaded_folders = folders;

			__json = json::parse(file_2_string(__current_loaded_folders, __current_loaded_alias, "json"));

			load_from_current_json();
		}

		void _swap_json(json J)
		{
			__previous_json = __json;
			__json = J;
		}

		void _revert_json() { __json = __previous_json; }

		void load_from_current_json()
		{
			ID = __json["ID"];
			alias = __json["alias"];

			OnLoad();
		}

		void standalone_load_from_current_json(json J)
		{
			_swap_json(J);

			ID = __json["ID"];
			alias = __json["alias"];

			OnLoad();

			_revert_json();
		}

		json JSON() 
		{
			__json = json();
			__json["ID"] = ID;
			__json["alias"] = alias;

			OnJson();

			return __json;
		}

		virtual void OnInit() { alias = class_name(this); }
		virtual void OnJson() {}
		virtual void OnLoad() {}
	};

	ostream& operator<<(ostream& os, Component& c) { return os << c.JSON().dump(4); }
	ostream& operator<<(ostream& os, Component* c) { return os << c->JSON().dump(4); }
}