#pragma once

#include <iomanip>
#include <iostream>
#include <fstream>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;
using namespace fs;

#include "NlohmanJson.hpp"
using namespace nlohmann;

namespace ECS
{
	inline string root = "data/";

	ofstream* open_file(string folders, string name, string ext)
	{
		path directory = root + folders;
		if (!exists(directory)) { create_directories(directory); }

		directory = root + folders + "/" + name + "." + ext;

		ofstream* outFile = new ofstream(directory);

		return outFile;
	}

	string file_2_string(string _path)
	{
		path filepath = root + _path;

		if (!exists(filepath)) { return ""; }

		ifstream inFile(filepath);
		if (!inFile.is_open()) { return ""; }

		stringstream buffer;
		buffer << inFile.rdbuf();
		return buffer.str();
	}

	template<typename T>
	string class_name(T* obj)
	{
		string name = typeid(*obj).name();

		size_t pos = name.rfind("::");
		if (pos != string::npos) { name = name.substr(pos + 2); }
		if (name.find("struct ") == 0) { name = name.substr(7); }

		return name;
	}

	json file_2_json(string _path) { return json::parse(file_2_string(_path + ".json")); }

	template<typename T>
	json TO_JSON(T obj) { return obj.JSON(); }

	template<typename T>
	json TO_JSON(T* obj) { return obj->JSON(); }

	template<typename T>
	json TO_JSON(const T* obj) { return obj->JSON(); }
}