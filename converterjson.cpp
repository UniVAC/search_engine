#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include "converterjson.h"

//getting data from files
std::vector<std::string> ConverterJSON::GetTextDocument()
{
    std::vector<std::string> vec_files;

    std::ifstream file("../config.json");
    nlohmann::json conf_file;

    file >> conf_file;

    for(int i = 0; i < conf_file.at("files").size(); i++){
        std::string str = "";
        std::ifstream file_with_data(conf_file.at("files")[i]);

        getline(file_with_data, str);

        vec_files.push_back(str);
        file_with_data.close();
    }

    file.close();
    return vec_files;
};

//get max answers
int ConverterJSON::GetResponsesLimit()
{
    std::ifstream file("../config.json");
    nlohmann::json conf_file;
    
    file >> conf_file;
    
    file.close();
    return  conf_file.at("config").at("max_responses");
};

//receiving requests from a file
std::vector<std::string> ConverterJSON::GetRequests(){
    std::vector<std::string> requests;

    std::ifstream file("../requests.json");
    nlohmann::json requests_file;

    file >> requests_file;

    for(nlohmann::json::iterator it = requests_file.at("requests").begin(); it != requests_file.at("requests").end(); it++){
        requests.push_back(it.value());
    }

    return requests;
};