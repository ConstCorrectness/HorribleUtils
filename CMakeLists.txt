cmake_minimum_required(VERSION 3.25)

project(HorribleUtils
    VERSION 1.0.0.0
    DESCRIPTION "Python/C++ utils libraries"
    LANGUAGES CXX 
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Default to RelWithDebInfo
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPE)
    set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Build type." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "minSizeRel" "RelWithDebInfo")
endif()

set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_INSTALL OFF CACHE BOOL "" FORCE)
# Prevent Benchmark from building its own tests using GoogleTest
set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "" FORCE)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/extern/googletest/CMakeLists.txt")
    add_subdirectory(extern/googletest)
endif()

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/extern/googlebenchmark/CMakeLists.txt")
    add_subdirectory(extern/googlebenchmark)
endif()

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/extern/nanobind/CMakeLists.txt")
    add_subdirectory(extern/nanobind)
endif()

set(nanobind_DIR ${CMAKE_SOURCE_DIR}/extern/nanobind/cmake)

find_package(Python COMPONENTS Interpreter Development.Module REQUIRED)
find_package(nanobind CONFIG REQUIRED)

add_library(horrible_core src/cpp/src/core.cc)
add_library(HorribleUtils::core ALIAS horrible_core)
target_include_directories(horrible_core PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/cpp/include>
    $<INSTALL_INTERFACE:include>
)

# 2. Define the Python Binding Module
# The module name must match the import name in Python (e.g., _core)
nanobind_add_module(_core src/horribleutils/_core.cc)
target_link_libraries(_core PRIVATE horrible_core)

# 3. Installation Rules
include(GNUInstallDirs)

# Install C++ headers and libs for C++ users
install(TARGETS horrible_core
    EXPORT HorribleUtilsTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(DIRECTORY src/cpp/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Install Python module
install(TARGETS _core LIBRARY DESTINATION horribleutils)

# Export Configuration for find_package(HorribleUtils) usage
install(EXPORT HorribleUtilsTargets
    FILE HorribleUtilsTargets.cmake
    NAMESPACE HorribleUtils::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/HorribleUtils
)

