cmake_minimum_required(VERSION 3.25)

project(HorribleUtils
    VERSION 1.0.0.0
    DESCRIPTION "Python/C++ utils libraries"
    LANGUAGES CXX 
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Python COMPONENTS Interpreter Development.Module REQUIRED)

# Default to RelWithDebInfo
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPE)
    set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Build type." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "minSizeRel" "RelWithDebInfo")
endif()





add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/extern/nanobind)


