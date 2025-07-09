#pragma once
#include <string>
#include <vector>

class ConverterJSON{
public:
    ConverterJSON() = default;

    /**
    * Метод получения содержимого файлов
    * @return Возвращает список с содержимым файлов перечисленных
    *       в config.json
    */
    std::vector<std::string> GetTextDocument();

    /**
    * Метод считывает поле name для определения названия
    * @return возвращает имя
    */
    std::string GetNameEngine();

    /**
    * Метод считывает поле max_responses для определения предельного
    *  количества ответов на один запрос
    * @return
    */
    static int GetResponsesLimit();

    /**
    * Метод получения запросов из файла requests.json
    * @return возвращает список запросов из файла requests.json
    */
    std::vector<std::string> GetRequests();

    /**
     * Положить в файл answers.json результаты поисковых запросов
     */
    void putAnswers(std::vector<std::vector<std::pair<int, float>>> answer);
};