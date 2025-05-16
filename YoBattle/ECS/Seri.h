#pragma once

#include "Utils.h"

namespace ECS
{
	struct Seri
	{
		json __json;

		int ID;
		string type;
		string alias;

		Seri() { __OnInit(); }

		void load(string path, bool use_alias = true)
		{
			if(use_alias) { __json = file_2_json(path + "/" + alias); }
			else { __json = file_2_json(path); }

			ID = __json["ID"];
			type = __json["type"];
			alias = __json["alias"];

			__OnLoad();
		}

		void load(json json_data)
		{
			__json = json_data;

			ID = __json["ID"];
			type = __json["type"];
			alias = __json["alias"];

			__OnLoad();
		}

		void save(string path, string as_alias = "")
		{
			if (as_alias == "") { as_alias = alias; }
			ofstream* file = open_file(path, as_alias, "json");

			if (file->is_open())
			{
				*file << setw(4) << JSON() << endl;
				file->close();
			}
		}

		json JSON()
		{
			__json = json::object();

			__json["ID"] = ID;
			__json["type"] = type;
			__json["alias"] = alias;

			__OnJson();

			return __json;
		}

		virtual void __OnInit()
		{
			ID = -1;
			type = class_name(this);
			alias = "unnamed";
		}

		virtual void __OnJson() { }

		virtual void __OnLoad() {}
	};

	ostream& operator<<(ostream& os, Seri& c) { return os << c.JSON().dump(4); }
	ostream& operator<<(ostream& os, Seri* c) { return os << c->JSON().dump(4); }
}