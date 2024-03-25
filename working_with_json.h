#include <string>
#include <vector>

class ConverterJSON{
    ConverterJSON() = default;

    std::vector<std::string> GetTextDocument();

    int GetResponsesLimit();

    std::vector<std::string> GetRequests();

    void putAnswers(std::vector<std::vector<std::pair<int, float>>> answer);
};
