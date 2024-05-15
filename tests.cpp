#define BOOST_TEST_MODULE MyTest
#include <boost/test/included/unit_test.hpp>
#include "converterjson.h"
#include "invertedindex.h"
//
BOOST_AUTO_TEST_CASE(test_GetResponsesLimit)
{
  ConverterJSON file;
  
  BOOST_TEST(file.GetResponsesLimit() == 5);
}
//
BOOST_AUTO_TEST_CASE(test_GetTextDocument)
{
  ConverterJSON file;

  std::vector<std::string> vec{"london is the capital of great britain", "big ben is the nickname for the Great bell of the striking clock", "three the", "four down"};

  BOOST_TEST(file.GetTextDocument() == vec);
}
//
BOOST_AUTO_TEST_CASE(test_GetRequests)
{
  ConverterJSON file;

  std::vector<std::string> requests{"london the", "some animals", "test two", "some words"};

  BOOST_TEST(file.GetRequests() == requests);
}
//
BOOST_AUTO_TEST_CASE(test_GetWordCount){
  InvertedIndex idx;
  ConverterJSON conJSON;
  std::vector<std::vector<Entry>> result;
  std::vector<std::string> requests = {"london", "the", "clock"};

  idx.UpdateDocumentBase(conJSON.GetTextDocument());

  //idx.GetFreq();

  for(auto request : requests){
    std::vector<Entry> word_count = idx.GetWordCount(request);
    result.push_back(word_count);
  }

  /*for(int i = 0; i < result.size(); i++){
    for(int j = 0; j < result[i].size(); j++){
        std::cout << result[i][j].doc_id << " - " << result[i][j].count << std::endl;
    }
  }*/

  std::vector<std::vector<Entry>> expected = {
                                                {
                                                  {0, 1}
                                                }, {
                                                  {0, 1}, {1, 3}, {2, 1}
                                                },{
                                                  {1, 1}
                                                }
                                              };

  BOOST_TEST(result == expected);
}

/*BOOST_AUTO_TEST_CASE(test_GetWordCount_2){
  
}*/