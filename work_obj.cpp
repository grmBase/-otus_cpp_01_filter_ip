//---------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <vector>
#include <algorithm> //std::sort
//---------------------------------------------------------------------------
#include "work_obj.h"
//---------------------------------------------------------------------------



int split(const std::string& str, ip_filter::t_ip_addr& aResult)
{

  int nDummy1 = 0, nDummy2 = 0;

  //size_t scanned = std::sscanf(str.c_str(), "%uhhd.%uhhd.%uhhd.%uhhd\t%d\t%d",

  // tmp workaround due to unable to find format for uint8_t:
  short int tmp[ip_filter::c_nAddrSize] = {};
  size_t scanned = std::sscanf(str.c_str(), "%hd.%hd.%hd.%hd\t%d\t%d",
    &tmp[0], &tmp[1], &tmp[2], &tmp[3],
    &nDummy1, &nDummy2);
  if (scanned != (ip_filter::c_nAddrSize + 2)) {
    std::cout << "error in scanf()" << std::endl;
    return -33;
  }

  for (size_t i = 0; i < ip_filter::c_nAddrSize; ++i) {
    aResult.m_bAddress[i] = tmp[i];
  }

  return 0;
}
//---------------------------------------------------------------------------


int ip_filter::t_work_obj::mainFunc()
{
  /* micro debug
  {
    const std::string strTmp = "222.42.146.225\t2\t0";
    t_ip_addr ip_addr{};
    int nResult = split(strTmp, ip_addr);
  }*/


  std::vector<ip_filter::t_ip_addr> ip_pool;

  {
    ip_filter::t_ip_addr tmp = {};
    for(std::string line; std::getline(std::cin, line);)
    {
      int nResult = split(line, tmp);
      if (nResult) {
        std::cout << "some error in split()" << std::endl;
        return nResult;
      }

      ip_pool.push_back(tmp);
    }
  }



  int nResult = back_ord_sort(ip_pool);
  if (nResult) {
    std::cout << "error in back_ord_sort()" << std::endl;
    return nResult;
  }

  // print all
  std::for_each(ip_pool.cbegin(), ip_pool.cend(), 
     [](const ip_filter::t_ip_addr& aAddr) {aAddr.print();}
  );


  // print if first byte equal to 1
  std::for_each(ip_pool.cbegin(), ip_pool.cend(), 
    [](const ip_filter::t_ip_addr& aAddr) {
      if (aAddr.m_bAddress[0] == 1) {
        aAddr.print();
      }
    }
  );


  // Print if first byte == to 46 or second == 70
  std::for_each(ip_pool.cbegin(), ip_pool.cend(),
    [](const ip_filter::t_ip_addr& aAddr) {
      if (aAddr.m_bAddress[0] == 46 && aAddr.m_bAddress[1] == 70) {
        aAddr.print();
      }
    }
  );

  
  // print if any byte equal to 46:
  std::for_each(ip_pool.cbegin(), ip_pool.cend(),
    [](const ip_filter::t_ip_addr& aAddr) {
      if (std::find(aAddr.m_bAddress.begin(), aAddr.m_bAddress.end(), 46) != aAddr.m_bAddress.end()) {
        aAddr.print();
      }
    }
  );

  return 0;
}
//---------------------------------------------------------------------------


// вынес в функцию, чтобы было бы что тестировать в тестах
int ip_filter::t_work_obj::back_ord_sort(std::vector<ip_filter::t_ip_addr>& avecPool)
{
  std::sort(avecPool.begin(), avecPool.end(), std::less<ip_filter::t_ip_addr>());

  return 0;
}
//---------------------------------------------------------------------------