#include <iostream>
#include <exception>
#include "../include/converterjson.h"
#include "../include/invertedindex.h"
#include "../include/searchserver.h"

int main() {
    try {
        ConverterJSON converterJson;
        InvertedIndex idx;

        std::cout << "Starting " << converterJson.GetNameEngine() << std::endl;

        const std::vector<std::string>& docs = converterJson.GetTextDocument();
        const std::vector<std::string>& requests = converterJson.GetRequests();

        idx.UpdateDocumentBase(docs);
        SearchServer searchServer(idx);

        auto result_search = searchServer.search(requests);

    std::vector<std::vector<std::pair<int, float>>> result;
    for(int i = 0; i < result_search.size(); ++i){
        std::vector<std::pair<int, float>> req;
        for(int j = 0; j < result_search[i].size(); ++j){
            req.push_back({result_search[i][j].doc_id, result_search[i][j].rank});
        }
        result.push_back(req);
    }

    converterJson.putAnswers(result);

    return 0;

    } catch (const char errorMsg) {
        std::cerr << "Error: " << errorMsg << std::endl;
        return 1;
    }catch (const std::exception& e) {
        std::cerr << "Exception: "  << e.what() << std::endl;
        return 1;
    } catch (...){
        std::cerr << "Unknow error" << std::endl;
        return 1;
    }
}
