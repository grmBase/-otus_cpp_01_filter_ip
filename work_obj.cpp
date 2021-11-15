#include <iostream>
#include <string>
#include <vector>
#include <algorithm> //std::sort

#include "work_obj.h"



int split(const std::string& str, t_ip_addr& aResult)
{

  int nDummy1 = 0;
  int nDummy2 = 0;

  //size_t scanned = std::sscanf(str.c_str(), "%uhhd.%uhhd.%uhhd.%uhhd\t%d\t%d",

  // tmp array due to unable to find format for uint8_t
  uint16_t tmp[c_nAddrSize] = {};
  size_t scanned = std::sscanf(str.c_str(), "%hd.%hd.%hd.%hd\t%d\t%d",
    &tmp[0], &tmp[1], &tmp[2], &tmp[3],
    &nDummy1, &nDummy2);
  if (scanned != (c_nAddrSize + 2)) {
    std::cout << "error in scanf()" << std::endl;
    return -33;
  }

  for (size_t i = 0; i < c_nAddrSize; ++i) {
    aResult.m_bAddress[i] = tmp[i];
  }

  return 0;
}


int t_work_obj::mainFunc()
{
  /* micro debug
  {
    const std::string strTmp = "222.42.146.225\t2\t0";
    t_ip_addr ip_addr{};
    int nResult = split(strTmp, ip_addr);
  }*/

  std::vector<t_ip_addr> ip_pool;

  {
    t_ip_addr tmp;
    for (std::string line; std::getline(std::cin, line);)
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


  struct print_all
  {
    void operator()(const t_ip_addr& addr)
    {
      addr.print();
    }
  };
  std::for_each(ip_pool.cbegin(), ip_pool.cend(), print_all());


  struct print_if_first_is_1
  {
    void operator()(const t_ip_addr& addr) {

      if (addr.m_bAddress[0] == 1) {
        addr.print();
      }
    }
  };
  std::for_each(ip_pool.cbegin(), ip_pool.cend(), print_if_first_is_1());


  struct print_if_first_is_46_70
  {
    void operator()(const t_ip_addr& addr) {

      if (addr.m_bAddress[0] == 46 && addr.m_bAddress[1] == 70) {
        addr.print();
      }
    }
  };
  std::for_each(ip_pool.cbegin(), ip_pool.cend(), print_if_first_is_46_70());


  struct print_if_first_any_46
  {
    void operator()(const t_ip_addr& addr) {

      if (std::find(addr.m_bAddress.begin(), addr.m_bAddress.end(), 46) != addr.m_bAddress.end())
      {
        addr.print();
      }

    }
  };

  std::for_each(ip_pool.cbegin(), ip_pool.cend(), print_if_first_any_46());

  return 0;
};



// вынес в функцию, чтобы было бы что тестировать в тестах
int t_work_obj::back_ord_sort(std::vector<t_ip_addr>& avecPool)
{

  struct
  {

    bool operator()(t_ip_addr& a, t_ip_addr& b) const
    {
      for (size_t i = 0; i < c_nAddrSize; ++i) {

        if (a.m_bAddress[i] > b.m_bAddress[i]) {
          return true;
        }

        if (a.m_bAddress[i] < b.m_bAddress[i]) {
          return false;
        }
      }

      return false;
    }
  } customLess;


  std::sort(avecPool.begin(), avecPool.end(), customLess);

  return 0;
}
