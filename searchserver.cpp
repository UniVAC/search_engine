#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <map>
#include "searchserver.h"
#include "converterjson.h"

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string>& quries_input){
    std::vector<std::vector<RelativeIndex>> result;

    for(auto request : quries_input){ //разбиение запроса на отдельные слова
        std::vector<std::vector<Entry>> entry;
        std::vector<std::string> uniqRequests;

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
        for(auto word : uniqRequests) {
            if(word == " " || word == "") continue;
            entry.push_back(_index.GetWordCount(word));
        }

        std::map<int, float> req_docs;
        //получаем номера документов и кол-во встречаемости слов в них
        for(int i = 0; i < entry.size(); ++i){
            for(int j = 0; j < entry[i].size(); ++j){
                if(req_docs.find(entry[i][j].doc_id) == req_docs.end()){
                    req_docs.emplace(entry[i][j].doc_id, entry[i][j].count);
                }
                else{
                    req_docs[entry[i][j].doc_id] += entry[i][j].count;
                }
            }
        }

        //поиск максимальной абсолютной релевантности
        int max = 0;
        if(req_docs.empty()){
            result.push_back(std::vector<RelativeIndex> {});
            continue;
        }

        if(!req_docs.empty()){
            for(auto num : req_docs){
                if(num.second > max) max = num.second;
            }
        }

        //подсчет относительной релевантности
        std::vector<RelativeIndex> rel_ind;
        if(!req_docs.empty()){
            for(auto docs : req_docs){
                rel_ind.push_back( {(size_t)docs.first, docs.second / max});
            }

            //сортировка
            if(rel_ind.size() >= 2){
                for(int i = 0; i < rel_ind.size() - 1; ++i){
                    for(int j = 0; j < rel_ind.size() - 1; ++j)
                    if(rel_ind[j].rank < rel_ind[j + 1].rank){
                        std::swap(rel_ind[j], rel_ind[j + 1]);
                    }
                }
            }

            int count_request = (int)ConverterJSON::GetResponsesLimit();

            for(int i = rel_ind.size(); i > count_request; --i){
                rel_ind.pop_back();
            }
            result.push_back(rel_ind);
        }
    }

    return result;
}