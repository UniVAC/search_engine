#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include <map>
#include "searchserver.h"

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string>& quries_input){
    std::map<std::string, int> requests; //запросы
    std::vector<std::vector<RelativeIndex>> result;

    for(auto request : quries_input){ //разбиение запроса на отдельные слова
        std::istringstream is_str(request);
        do{
            std::string word;
            is_str >> word;

            auto uniq_word = requests.find(word);

            if(uniq_word == requests.end()){
                requests.insert({word, 0});
            }
        }
        while(is_str);
    }

    for(auto word : requests){ // подсчет количества встречаемости каждого слова
        auto search_word = _index.GetWordCount(word.first); 
        int count = 0;

        for(auto requst : search_word){
            count += requst.count;
        }

        
    }
    
}