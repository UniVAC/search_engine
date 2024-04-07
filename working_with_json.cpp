#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include "working_with_json.h"


std::vector<std::string> ConverterJSON::GetTextDocument(){
    
};

int ConverterJSON::GetResponsesLimit()
{
    std::ifstream file("../config.json");
    nlohmann::json conf_file;
    
    file >> conf_file;
    
    return  conf_file.at("config").at("max_responses");
};