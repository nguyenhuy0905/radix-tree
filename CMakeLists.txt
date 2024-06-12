cmake_minimum_required(VERSION 3.20)
project(radix-tree)

set(CMAKE_BUILD_TYPE Debug)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG f8d7d77)
FetchContent_MakeAvailable(googletest)

add_library(compiler-flags INTERFACE)
target_compile_features(compiler-flags INTERFACE cxx_std_23)
target_compile_options(compiler-flags INTERFACE -pedantic -Wall -Wextra)
add_subdirectory(src)
add_subdirectory(test)
