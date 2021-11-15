//---------------------------------------------------------------------------
#pragma once
//---------------------------------------------------------------------------
#include <array>
//---------------------------------------------------------------------------

const size_t c_nAddrSize = 4;

class t_ip_addr
{

  public:

    // comparisons (used in unit tests)
    bool operator == (const t_ip_addr& aOther) const
    {
      return m_bAddress == aOther.m_bAddress;
    };


    void print() const
    {

      // for_each and similar doesn't give easy access to iter position I need here
      for(size_t i = 0; i < c_nAddrSize; i++)
      {
        std::cout << (int)m_bAddress[i];
        if (i != c_nAddrSize - 1) {
          std::cout << ".";
        }
      }
      std::cout << std::endl;
    };

  // да паблик для удобства
  //private:

    std::array<uint8_t, c_nAddrSize> m_bAddress = {};
};
//---------------------------------------------------------------------------
