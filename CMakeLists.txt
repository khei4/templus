cmake_minimum_required(VERSION 3.16)
project(template-project CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_COLOR_DIAGNOSTICS ON)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
   add_compile_options (-fdiagnostics-color=always)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
   add_compile_options (-fcolor-diagnostics)
endif ()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -fsanitize=undefined,address")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

option(ENABLE_WERROR "Enable -Werror options" OFF)
if (ENABLE_WERROR)
  set(CMAKE_CXX_FLAGS "-Werror ${CMAKE_CXX_FLAGS}")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(include)
add_subdirectory(lib)
add_subdirectory(tools)



# Testing and Benchmarking
include(FetchContent)
if(${CMAKE_VERSION} VERSION_LESS "3.25")
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_Declare(googlebenchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG main
)
else()
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  DOWNLOAD_EXTRACT_TIMESTAMP true
)
FetchContent_Declare(googlebenchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG main
  DOWNLOAD_EXTRACT_TIMESTAMP true
)
endif()
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest googlebenchmark)

enable_testing()
set(ALL_TESTS CACHE PATH "" FORCE)
add_subdirectory(unittests)

include(ProcessorCount)
ProcessorCount(N)
# FIXME: work filter
add_custom_target(unittests
  COMMAND ctest --test-dir ./unittests/ --output-on-failure --timeout 5 -j ${N}
  DEPENDS ${ALL_TESTS}
)

# add_subdirectory(benchmarks)
# FIXME: include on subdirectory

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/benchmark)
add_executable(benchm benchmark/benchmark.cpp)
target_link_libraries(benchm benchmark::benchmark)

add_custom_target(bench
  COMMAND ${CMAKE_BINARY_DIR}/benchmark/benchm
  DEPENDS benchm benchmark::benchmark benchmark/benchmark.cpp
)