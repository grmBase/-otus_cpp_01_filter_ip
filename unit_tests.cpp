
#define BOOST_TEST_MODULE unit_tests



#include <vector>
#include <boost/test/unit_test.hpp>

#include "work_obj.h"




BOOST_AUTO_TEST_SUITE(test_version)


int sort_test()
{
  std::vector<t_ip_addr> vecUnsorted = { 
    {0, 1, 2, 3} , {255, 255, 255, 255}, {0, 255, 0, 255}, {255, 0, 255, 0}, {255, 255, 255, 255}, {0,0,0,0} };

  int nResult = t_work_obj::back_ord_sort(vecUnsorted);
  if (nResult) {
    std::cout << "Error in back_ord_sort()" << std::endl;
    return nResult;
  }

  const std::vector<t_ip_addr> vecExpected = {
    {255, 255, 255, 255},
    {255, 255, 255, 255},
    {255, 0, 255, 0},
    {0, 255, 0, 255},
    {0, 1, 2, 3} ,
    {0,0,0,0} ,
  };

  return !(vecExpected == vecUnsorted);
}


BOOST_AUTO_TEST_CASE(test_valid_version)
{
  BOOST_CHECK(sort_test() == 0);
}

}


