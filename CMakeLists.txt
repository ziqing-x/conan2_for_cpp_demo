cmake_minimum_required(VERSION 3.10)
project("mydemo" LANGUAGES C CXX)

set(TOP ${CMAKE_CURRENT_SOURCE_DIR})
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(FATAL_ERROR "请别在源码目录编译, 污染工程")
endif()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-std=c++17" COMPILER_SUPPORTS_CXX17)
check_cxx_compiler_flag("-std=c++14" COMPILER_SUPPORTS_CXX14)
check_cxx_compiler_flag("-std=c++11" COMPILER_SUPPORTS_CXX11)
if(COMPILER_SUPPORTS_CXX17)
  message("---- support cpp 17 ----")
elseif(COMPILER_SUPPORTS_CXX14)
  message("---- support cpp 14 ----")
elseif(COMPILER_SUPPORTS_CXX11)
  message("---- support cpp 11 ----")
else()
  message(
    FATAL_ERROR
      "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler."
  )
endif()

include(${TOP}/cmake/colors.cmake)
define_colors()
include(${TOP}/cmake/option.cmake)
include(${TOP}/cmake/git_hash.cmake)
include(${TOP}/cmake/static_check.cmake)
include(${TOP}/cmake/debug.cmake)
include(${TOP}/cmake/pack.cmake)

add_subdirectory(src)