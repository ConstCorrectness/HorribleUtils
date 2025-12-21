#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>

#include "horribleutils/core.hpp"

namespace nb = nanobind;
using namespace nb::literals;


NB_MODULE(_core, m) {
  m.doc() = "HorribleUtils internal core module";


  m.def("add", &horrible::utils::add, "a"_a, "b"_a, "Adds two integers together efficiently.");
  m.def("scream", &horrible::utils::scream, "str"_a, "Converts input string to uppercase and appends exclamation marks.");
}