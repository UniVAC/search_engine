#pragma once
#include <vector>
#include <string>
#include "invertedindex.h"

struct RelativeIndex{
    size_t doc_id;
    float rank;

    bool operator == (const RelativeIndex& other) const {
        return (doc_id == other.doc_id && rank == other.rank);
    }

    //for sort
    bool operator < (const Entry& other) const{
        return (doc_id < other.doc_id);
    }
};

class SearchServer{
public:
    /**
    * @param idx в конструктор класса передаётся ссылка на класс
    InvertedIndex,
    * чтобы SearchServer мог узнать частоту слов встречаемых в
    запросе
    */
    SearchServer(InvertedIndex& idx) : _index(idx) { };
    /**
    * Метод обработки поисковых запросов
    * @param queries_input поисковые запросы взятые из файла
    requests.json
    * @return возвращает отсортированный список релевантных ответов для
    заданных запросов
    */
    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& quries_input);

private:
    InvertedIndex _index;
};