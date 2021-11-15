#include <iostream>
#include <string>

#include "work_obj.h"



int main(int, char const* [])
{

  t_work_obj work_obj;

  try
  {
    int nResult = work_obj.mainFunc();
    if (nResult) {
      std::cout << "error in mainFunc()" << std::endl;
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << "some exception here. msg: " << e.what() << std::endl;
  }

  return 0;
}

