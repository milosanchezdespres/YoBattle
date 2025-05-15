#pragma once

#include "NlohmanJson.hpp"
using namespace nlohmann;

#include <typeindex>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;
using namespace fs;

namespace ECS
{
	json __json__buffer;
	json __json__buffer2;
	string __typename__buffer;

	struct Component
	{
		int ID;
		type_index alias;

		Component() : ID(-1), alias(typeid(Component)) { __init(); }

		void save(string _path = "") const
		{
			json j = JSON();

			path directory = "data";
			if (!exists(directory)) { create_directories(directory); }

			string outPath = "";

			if (_path == "") { outPath = "data/" + j["alias"].get<std::string>() + ".json"; }
			else { outPath = "data/" + _path + "/" + j["alias"].get<std::string>() + ".json"; }

			ofstream outFile(outPath);

			if (outFile.is_open())
			{
				outFile << std::setw(4) << j << std::endl;
				outFile.close();
			}
		}

		json JSON() const
		{
			__json__buffer = json();
			__json__buffer["ID"] = ID;

			__typename__buffer = typeid(*this).name();
			size_t pos = __typename__buffer.rfind("::");
			if (pos != std::string::npos) { __typename__buffer = __typename__buffer.substr(pos + 2); }
			if (__typename__buffer.find("struct ") == 0) { __typename__buffer = __typename__buffer.substr(7); }
			__json__buffer["alias"] = __typename__buffer;

			__json__buffer = OnJson(__json__buffer);

			return __json__buffer;
		}

		virtual json OnJson(json json_data) const { return json_data; }

		virtual void __init() { alias = typeid(*this); }
	};

	template<typename T>
	json TO_JSON(T component) { return component.JSON(); }

	template<typename T>
	json TO_JSON(T* component) { return component->JSON(); }

	template<typename T>
	json TO_JSON(const T* component) { return component->JSON(); }

	class ComponentFactory
	{
		public:
			ComponentFactory(const ComponentFactory&) = delete;
			ComponentFactory& operator=(const ComponentFactory&) = delete;

			static ComponentFactory& factory() {
				static ComponentFactory instance;
				return instance;
			}

			template <typename T, typename... Args>
			T* create(Args&&... args) { return new T(forward<Args>(args)...); }

		private:
			ComponentFactory() { }
			~ComponentFactory() { }
	};
}