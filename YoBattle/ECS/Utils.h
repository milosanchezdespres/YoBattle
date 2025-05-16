#pragma once

#include <iomanip>
#include <iostream>
#include <fstream>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;
using namespace fs;

#include <typeindex>

#include "NlohmanJson.hpp"
using namespace nlohmann;

#include "EntityFactory.h"

namespace ECS
{
	ofstream* to_file(string folders, string filename, string ext)
	{
		if (folders == "") { folders = "data"; }
		else { folders = "data/" + folders; }

		path directory = folders;
		if (!exists(directory)) { create_directories(directory); }

		ofstream* outFile = new ofstream(folders + "/" + filename + "." + ext);

		return outFile;
	}

	string file_2_string(string folders, string filename, string ext)
	{
		if (folders == "") { folders = "data"; }
		else { folders = "data/" + folders; }

		path filepath = folders + "/" + filename + "." + ext;

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

	template<typename T>
	json TO_JSON(T obj) { return obj.JSON(); }

	template<typename T>
	json TO_JSON(T* obj) { return obj->JSON(); }

	template<typename T>
	json TO_JSON(const T* obj) { return obj->JSON(); }
}