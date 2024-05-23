#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include <map>
#include "searchserver.h"

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string>& quries_input){
    std::map<std::string, int> requests;

    for(auto request : quries_input){
        std::istringstream is_str(request);
        do{
            std::string word;
            is_str >> word;

            auto uniq_word = requests.find(word);

            if(uniq_word != requests.end()){
                uniq_word->second++;
            }
            else{
                requests.insert({word, 1});
            }
        }
        while(is_str);
    }

    
}