#define BOOST_TEST_MODULE MyTest
#include <boost/test/included/unit_test.hpp>
#include "working_with_json.h"

BOOST_AUTO_TEST_CASE(first_test)
{
  ConverterJSON file;
  
  BOOST_TEST(file.GetResponsesLimit() == 5);
}