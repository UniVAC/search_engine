#include <fstream>
#include <iostream>
#include "../include/converterjson.h"
#include "nlohmann/json.hpp"

//getting data from files
std::vector<std::string> ConverterJSON::GetTextDocument()
{
    std::vector<std::string> vec_files;

    std::ifstream file("config.json");
    if(!file.is_open()) {
        throw std::runtime_error ("config file is missing");
    }

    nlohmann::json conf_file;
    file >> conf_file;

    if(conf_file.find("config") == conf_file.end()){
        throw std::runtime_error ("config file is empty");
    }

    for(int i = 0; i < conf_file.at("files").size(); i++){
        std::string str;

        std::ifstream file_with_data(conf_file.at("files")[i]);

        if(!file_with_data.is_open()){
            throw std::runtime_error("file is not open!");
        }
        getline(file_with_data, str);

        vec_files.push_back(str);
        file_with_data.close();
    }

    file.close();

    return vec_files;
};

//get name
std::string ConverterJSON::GetNameEngine() {
    std::ifstream file("config.json");

    if(!file.is_open()) std::cout <<"yes";
    nlohmann::json conf_file;
    file >> conf_file;

    file.close();
    return  conf_file.at("config").at("name");
}

//get max answers
int ConverterJSON::GetResponsesLimit()
{
    std::ifstream file("config.json");
    nlohmann::json conf_file;

    file >> conf_file;

    file.close();
    return  conf_file.at("config").at("max_responses");
};

//receiving requests from a file
std::vector<std::string> ConverterJSON::GetRequests(){
    std::vector<std::string> requests;

    std::ifstream file("requests.json");
    nlohmann::json requests_file;

    file >> requests_file;

    for(nlohmann::json::iterator it = requests_file.at("requests").begin(); it != requests_file.at("requests").end(); it++){
        requests.push_back(it.value());
    }

    file.close();
    return requests;
};

void ConverterJSON::putAnswers(std::vector<std::vector<std::pair<int, float>>> answer) {
    nlohmann::json json_answers = {};
    json_answers["answers"] = nlohmann::json::object();

    for(size_t i = 0; i < answer.size(); ++i){
        std::string request_name = "request" +
                std::string(3 - std::to_string(i + 1).length(), '0') + std::to_string(i + 1);

        nlohmann::json request_data;

        if(answer[i].empty()) {
            request_data["result"] = false;
        }
        else{
            request_data["result"] = true;

            if (answer[i].size() > 1) {
                nlohmann::json relevance_array = nlohmann::json::array();
                for(const auto& [docid, rank] : answer[i]) {
                    relevance_array.push_back({
                                                      {"docid", docid},
                                                      {"rank", rank}
                    });
                }
                request_data["relevance"] = relevance_array;
            }
            else{
                request_data["docid"] = answer[i][0].first;
                request_data["rank"] = answer[i][0].second;
            }
        }

        json_answers["answer"][request_name] = request_data;
    }


    std::ofstream file("..\\answers.json");

    if(file.is_open()){
        file.clear();
        file << std::setw(4) << json_answers << std::endl;
    }
};

