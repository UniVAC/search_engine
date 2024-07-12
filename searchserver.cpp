#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <map>
#include "searchserver.h"

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string>& quries_input){
    std::vector<std::vector<RelativeIndex>> result;

    for(auto request : quries_input){ //разбиение запроса на отдельные слова
        std::vector<std::string> uniqRequests;
        std::vector<int> countRequests;

        std::istringstream is_str(request); //строка запроса

        do{ //уникальные слова
            std::string word;
            bool succes = false;
            is_str >> word;

            for(int i = 0; i < uniqRequests.size(); i++){
                if(word == uniqRequests[i]) {
                    succes = true;
                    break;
                }
            }
            if(!succes){
                uniqRequests.push_back(word);
            }

        }
        while(is_str);

        //получение количества встречаемости слова
        for(auto word : uniqRequests){ 
            std::vector<Entry> entry = _index.GetWordCount(word);
            if(entry.empty()){
                countRequests.push_back(0);
            }
            else{
                int count = 0; 
                for(int i = 0; i < entry.size(); i++){
                    count += entry[i].count;
                }
                countRequests.push_back(count);
            }
        }

        //сортировка от редких до частых
        for(int i = 1; i < countRequests.size(); i++){
            int j = i - 1;
            while(j >= 0 && countRequests[j] > countRequests[j + 1]){
                std::swap(countRequests[j], countRequests[j + 1]);
                std::swap(uniqRequests[j], uniqRequests[j + 1]);
                j--;
            }
        }

        //нужно найти документы где встречаются слова
        for(auto word : uniqRequests){
            
        }
    }
}