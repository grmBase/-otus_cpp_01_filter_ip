#include <iostream>
#include <string>
#include <vector>
#include <algorithm> //std::sort

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string& str, char d)
{
  std::vector<std::string> r;

  std::string::size_type start = 0;
  std::string::size_type stop = str.find_first_of(d);
  while (stop != std::string::npos)
  {
    r.push_back(str.substr(start, stop - start));

    start = stop + 1;
    stop = str.find_first_of(d, start);
  }

  r.push_back(str.substr(start));

  return r;
}




int main(int, char const* [])
{


  try
  {

    // Выбор контейнера можно менять? Или это по условию задачи?
    // В строках по идее жутко не оптимально...

    std::vector<std::vector<std::string> > ip_pool;

    for (std::string line; std::getline(std::cin, line);)
    {
      std::vector<std::string> v = split(line, '\t');
      ip_pool.push_back(split(v.at(0), '.'));
    }

    // TODO reverse lexicographically sort



    struct 
    {
      bool operator()(const std::vector<std::string>& a, const std::vector<std::string>& b) const 
      { 
      

        if (a.size() != b.size()) {
          throw std::runtime_error("size of elems not equal");
        }

        if(a.size() != 4) {
          throw std::runtime_error("size of vector is not equal to 4");
        }

        //std::cout << "fist: " << a[0] << "." << a[1] << "." << a[2] << "." << a[3] << 
        //  ", second: " << b[0] << "." << b[1] << "." << b[2] << "." << b[3] << std::endl;
        

        
        for (size_t i = 0; i < 4; ++i) {

          // Тут жутко не оптимально - см. вопрос про выбор контейнера хранения выше
          uint8_t una = atoi(a[i].c_str());
          uint8_t unb = atoi(b[i].c_str());
          if (una > unb) {
            return true;
          }

          if (una < unb) {
            return false;
          }
        }

        return false; 
      }
    } customLess;


    std::sort(ip_pool.begin(), ip_pool.end(), customLess);


    
    for (std::vector<std::vector<std::string> >::const_iterator ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
    {
      for (std::vector<std::string>::const_iterator ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
      {
        if (ip_part != ip->cbegin())
        {
          std::cout << ".";

        }
        std::cout << *ip_part;
      }
      std::cout << std::endl;
    }



    // 222.173.235.246
    // 222.130.177.64
    // 222.82.198.61
    // ...
    // 1.70.44.170
    // 1.29.168.152
    // 1.1.234.8



    // TODO filter by first byte and output
    // ip = filter(1)
    struct print_if_first_is_1
    {
      void operator()(const std::vector<std::string>& a) {

        // todo: проверка на что ест хотя бы один элемент
        if (a[0] == "1") {
          std::cout << a[0] << "." << a[1] << "." << a[2] << "." << a[3] << std::endl;
        }
      }
    };

    std::for_each(ip_pool.cbegin(), ip_pool.cend(), print_if_first_is_1());


    // 1.231.69.33
    // 1.87.203.225
    // 1.70.44.170
    // 1.29.168.152
    // 1.1.234.8

    // TODO filter by first and second bytes and output
    // ip = filter(46, 70)

    struct print_if_first_is_46_70
    {
      void operator()(const std::vector<std::string>& a) {

        // todo: проверка на что ест хотя бы один элемент
        if (a[0] == "46" && a[1] == "70") {
          std::cout << a[0] << "." << a[1] << "." << a[2] << "." << a[3] << std::endl;
        }
      }
    };

    std::for_each(ip_pool.cbegin(), ip_pool.cend(), print_if_first_is_46_70());



    // 46.70.225.39
    // 46.70.147.26
    // 46.70.113.73
    // 46.70.29.76

    // TODO filter by any byte and output
    // ip = filter_any(46)


    struct print_if_first_any_46
    {
      void operator()(const std::vector<std::string>& a) {

        // todo: проверка на что ест хотя бы один элемент
        
        if(std::find(a.begin(), a.end(), std::string("46")) != a.end()) {
          std::cout << a[0] << "." << a[1] << "." << a[2] << "." << a[3] << std::endl;
        }
      }
    };

    std::for_each(ip_pool.cbegin(), ip_pool.cend(), print_if_first_any_46());



    // 186.204.34.46
    // 186.46.222.194
    // 185.46.87.231
    // 185.46.86.132
    // 185.46.86.131
    // 185.46.86.131
    // 185.46.86.22
    // 185.46.85.204
    // 185.46.85.78
    // 68.46.218.208
    // 46.251.197.23
    // 46.223.254.56
    // 46.223.254.56
    // 46.182.19.219
    // 46.161.63.66
    // 46.161.61.51
    // 46.161.60.92
    // 46.161.60.35
    // 46.161.58.202
    // 46.161.56.241
    // 46.161.56.203
    // 46.161.56.174
    // 46.161.56.106
    // 46.161.56.106
    // 46.101.163.119
    // 46.101.127.145
    // 46.70.225.39
    // 46.70.147.26
    // 46.70.113.73
    // 46.70.29.76
    // 46.55.46.98
    // 46.49.43.85
    // 39.46.86.85
    // 5.189.203.46
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}

