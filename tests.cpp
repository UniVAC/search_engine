#define BOOST_TEST_MODULE MyTest
#include <boost/test/included/unit_test.hpp>
#include "working_with_json.h"

BOOST_AUTO_TEST_CASE(first_test)
{
  BOOST_TEST(1 == 1);
}