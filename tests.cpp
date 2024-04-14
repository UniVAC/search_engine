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

  std::vector<std::string> vec{"first next", "second back", "three up", "four down"};

  BOOST_TEST(file.GetTextDocument() == vec);
}
//
BOOST_AUTO_TEST_CASE(test_GetRequests)
{
  ConverterJSON file;

  std::vector<std::string> requests{"hello word", "some animals", "test two", "some words"};

  BOOST_TEST(file.GetRequests() == requests);
}
//
BOOST_AUTO_TEST_CASE(test_GetWordCount){
  InvertedIndex index;
  std::vector<std::string> docs = {
    "london is the capital of great britain",
    "big ben is the nickname for the Great bell of the striking clock"
  };
  index.GetDocs(docs);

  std::vector<std::vector<Entry>> expected = {{{0, 1}}, {{0, 1}, {1, 3}}};
  std::vector<std::vector<Entry>> ans;

  ans.push_back(index.GetWordCount("london"));
  ans.push_back(index.GetWordCount("the"));

  BOOST_TEST(ans == expected);
}

BOOST_AUTO_TEST_CASE(test_GetWordCount_2){
  InvertedIndex index;
  std::vector<std::string> docs = {
    "milk milk milk milk water water water",
    "milk water water",
    "milk milk milk milk milk water water water water water",
    "americano cappuchino"
  };
  index.GetDocs(docs);

  std::vector<std::vector<Entry>> expected = {
      {{0, 4}, {1, 1}, {2, 5}},
      {{0, 3}, {1, 2}, {2, 5}},
      {{3, 1}}
  };
  std::vector<std::vector<Entry>> ans;

  ans.push_back(index.GetWordCount("milk"));
  ans.push_back(index.GetWordCount("water"));
  ans.push_back(index.GetWordCount("cappuchino"));

  /*for(int i = 0; i < ans.size(); i++){
    for(int j = 0; j < ans[i].size(); j++){
      std::cout << ans[i][j].doc_id << " - " << ans[i][j].count << std::endl;
    }
    std::cout << "next" << std::endl;
  }*/

  BOOST_TEST(ans == expected);
}