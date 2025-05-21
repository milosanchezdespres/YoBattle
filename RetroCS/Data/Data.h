#pragma once

#include "../Tools/Externals.h"

#include "nlohman_json.h"
using json = nlohmann::json;

namespace RetroCS
{
    namespace DATA
    {
        struct DataObject
        {
            json __json_buffer;

            json to_json()
            {
                __json_buffer = {};

                OnJsonWrite();

                return __json_buffer;
            }

            void from_json(json _data)
            {
                __json_buffer = _data;

                OnJsonRead();
            }

            virtual void OnJsonWrite() {}
            virtual void OnJsonRead() {}
        };

        inline string file_content(string filename, string folder = "", string ext = "")
        {
            string path = filename;
            if(ext != "") { path += "." + ext; }
            if(folder != "") { path = folder + "/" + path; }

            ifstream file(path);

            if(!file) { throw runtime_error("Failed to open file for writing: " + path); }
            else
            {
                stringstream buffer;

                buffer << file.rdbuf();

                file.close();

                return buffer.str();
            }
        }

        inline void save_file_content(string content, string filename, string folder = "", string ext = "")
        {
            string path = filename;
            if(ext != "") { path += "." + ext; }
            if(folder != "") { path = folder + "/" + path; }

            fs::create_directories(folder);

            ofstream file(path, ios::trunc);

            if(!file) { throw runtime_error("Failed to open file for writing: " + path); }
            else
            {
                file << content;
                file.close();
            }
        }

        inline void save_to(DataObject* data_object, string filename, string _folder = "")
        {
            json _json = data_object->to_json();

            string folder = _folder;
            if(folder != "") folder = "/" + folder;
            folder = "Game/data" + folder;

            save_file_content(_json.dump(4), filename, folder, "json");
        }

        inline void load_from(DataObject* data_object, string filename, string _folder = "")
        {
            string folder = _folder;
            if(folder != "") folder = "/" + folder;
            folder = "Game/data" + folder;

            json _json = json::parse(file_content(filename, folder, "json"));

            data_object->from_json(_json);
        }
    }
}