cmake_minimum_required(VERSION 3.20)
project(radix-tree)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(compiler-flags INTERFACE)
target_compile_features(compiler-flags INTERFACE cxx_std_23)
target_compile_options(compiler-flags INTERFACE -pedantic -Wall -Wextra)

include(Options.cmake)

add_subdirectory(src)
