# build type
set(CMAKE_BUILD_TYPE
    Debug
    CACHE STRING "Choose a build type" FORCE)
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
                                             "MinSizeRel" "RelWithDebInfo")

option(USE_LLD "Use lld instead of ld for linking" OFF)
option(
  ENABLE_TESTING
  "Compile an unit test executable instead of the main executable. NOTE: use Debug release for debug info"
  OFF)
option(ENABLE_WARNING "Enable compiler warnings" ON)
option(WARNING_AS_ERROR "Change compiler warnings to errors" ON)
option(ENABLE_ASAN "Compile with AddressSanitizer" OFF)

if(USE_LLD)
  find_program(LLD lld REQUIRED)
  if(NOT LLD)
    message(
      FATAL_ERROR
        "Error, LLD not found, please either turn off option USE_LLD or add directory of LLD to PATH"
    )
  endif()
  set(CMAKE_LINKER lld)
endif()

if(ENABLE_TESTING)
  add_subdirectory(test)
endif()

if(ENABLE_WARNING)
  if(MSVC)
    target_compile_options(compile-opts INTERFACE "/W4")
  else(MSVC)
    target_compile_options(
      compiler-flags
      INTERFACE "-Wall;-Wextra;-Wformat=2;-Werror;-fdiagnostics-color=always")
  endif()
endif()

if(WARNING_AS_ERROR)
  if(MSVC)
    target_compile_options(compiler-flags INTERFACE "/WX")
  else(MSVC)
    target_compile_options(compiler-flags INTERFACE "-Werror")
  endif()
endif()

if(ENABLE_ASAN)
  if(MSVC)
    target_compile_options(compiler-flags INTERFACE "/fsanitize=address;/Oy")
  else(MSVC)
    target_compile_options(
      compiler-flags INTERFACE "-fsanitize=address;-fno-omit-frame-pointer")
  endif()
endif()
