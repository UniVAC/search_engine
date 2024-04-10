#define BOOST_TEST_MODULE MyTest
#include <boost/test/included/unit_test.hpp>
#include "working_with_json.h"

BOOST_AUTO_TEST_CASE(test_GetResponsesLimit)
{
  ConverterJSON file;
  
  BOOST_TEST(file.GetResponsesLimit() == 5);
}

BOOST_AUTO_TEST_CASE(test_GetTextDocument)
{
  ConverterJSON file;

  std::vector<std::string> vec{"first next", "second back", "three up", "four down"};

  BOOST_TEST(file.GetTextDocument() == vec);
}