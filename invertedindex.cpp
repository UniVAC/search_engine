#include "invertedindex.h"

void InvertedIndex::UpdateDocumentBase(std::vector<std::string> input_docs){
    InvertedIndex index;
    
};

std::vector<Entry> InvertedIndex::GetWordCount(const std::string &word){
    std::vector<Entry> q_word;

    for(int i = 0; i < docs.size(); i++){
        int count = 0;

        for (int j = 0; j < docs[i].length() - (word.length() - 1); j++){
            if (docs[i][j] == word[0]){
                for (int z = 1; z < word.length(); z++) {
                    if (docs[i][j + z] != word[z]) break;
                    if (z == word.length() - 1) count++;
                }
            }
        }

        if(count){
            Entry some_word = {(size_t)i, (size_t)count};
            q_word.push_back(some_word);
        }
    }

    return q_word;
};

//for test
void InvertedIndex::GetDocs(std::vector<std::string> other){
    docs = other;
}