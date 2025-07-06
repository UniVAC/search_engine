#pragma once
#include <map>
#include <vector>
#include <string>

struct Entry{
    size_t doc_id, count;

    //for tests
    bool operator == (const Entry& other) const {
        return (doc_id == other.doc_id && count == other.count);
    }

    //for sort
    bool operator < (const Entry& other) const{
        return (doc_id < other.doc_id);
    }
};

class InvertedIndex{
public:
    InvertedIndex() = default;

    void UpdateDocumentBase(std::vector<std::string> input_docs);

    /**
    * Метод определяет количество вхождений слова word в загруженной базе документов
    * @param word слово, частоту вхождений которого необходимо определить
    * @return возвращает подготовленный список с частотой слов
    */
    std::vector<Entry> GetWordCount (const std::string& word);

    void GetFreq();

private:
    std::vector<std::string> docs;  // список содержимого документов
    std::map<std::string, std::vector<Entry>> freq_dictionary;   // частотный словарь
};