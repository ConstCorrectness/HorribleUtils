#include "horribleutils/core.hpp"

#include <algorithm>
#include <cctype>

namespace horrible::utils
{

int add(int a, int b) {
  return a + b;
}

std::string scream(std::string const& str) {
  std::string res = str;


  std::transform(res.begin(), res.end(), res.begin(), [](unsigned char c) {
    return std::toupper(c);
  });

  return res + "!";
}



}             // end namespace horrible::utils    