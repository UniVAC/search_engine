#include <algorithm>
#include <thread>
#include <sstream>
#include <iostream>
#include <vector>
#include <mutex>
#include "../include/invertedindex.h"
#include "../include/converterjson.h"

void InvertedIndex::UpdateDocumentBase(std::vector<std::string> input_docs){
    ConverterJSON converterJSON;
    docs = input_docs;
    std::vector<std::thread> thread_index;

    for(int i = 0; i <  docs.size(); i++){
        int number_doc = i;

        thread_index.emplace_back([this, number_doc](std::string doc_str){
            std::mutex mut;
            std::istringstream is_str(doc_str);
            std::map<std::string, int> count_word;

            do {
              std::string word;
              is_str >> word;
              auto it = count_word.find(word);

              if(it != count_word.end()){
                  it->second++;
              }
              else{
                  count_word.emplace(word, 1);
              }
            }
            while(is_str);


            for(auto it = count_word.begin(); it != count_word.end(); it++){
              Entry entry;
              entry.count = it->second;
              entry.doc_id = number_doc;

              mut.lock();

              if(freq_dictionary.find(it->first) != freq_dictionary.end()){
                  freq_dictionary.find(it->first)->second.push_back(entry);
              }
              else{
                  freq_dictionary.emplace(it->first, std::vector<Entry> {entry});
              }

              mut.unlock();
            }

            },
            docs[i]);
    }

    for(int i = 0; i < thread_index.size(); i++){
        thread_index[i].join();
    }

    for(auto it = freq_dictionary.begin(); it != freq_dictionary.end(); it++){
        std::sort(it->second.begin(), it->second.end());
    }
};

std::vector<Entry> InvertedIndex::GetWordCount(const std::string &word){
    if(freq_dictionary.find(word) == freq_dictionary.end()){
        std::vector<Entry> result{};
        return result;
    }
    return freq_dictionary.find(word)->second;
};

void InvertedIndex::GetFreq(){
    for(auto it = freq_dictionary.begin(); it != freq_dictionary.end(); it++){
        std::cout << it->first << " = ";
        for(int i = 0; i < it->second.size(); i++){
            std::cout << "{" << it->second[i].doc_id << ", " << it->second[i].count << "},";
        }
        std::cout << std::endl;
    }
};